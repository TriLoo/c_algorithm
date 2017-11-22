from mxnet import gluon
from mxnet.gluon import nn
from mxnet import nd
from mxnet import init
import mxnet as mx

class Inception(nn.Block):
    def __init__(self, n1, n2_1, n2_2, n3_1, n3_2, n4, **kwargs):
        super(Inception, self).__init__(**kwargs)
        self.p1_conv_1 = nn.Conv2D(n1, kernel_size=1, activation='relu')
        self.p2_conv_1 = nn.Conv2D(n2_1, kernel_size=1, activation='relu')
        self.p2_conv_2 = nn.Conv2D(n2_2, kernel_size=3, padding=1, activation='relu')
        self.p3_conv_1 = nn.Conv2D(n3_1, kernel_size=1, activation='relu')
        self.p3_conv_2 = nn.Conv2D(n3_2, kernel_size=5, padding=2, activation='relu')
        self.p4_pool_1 = nn.MaxPool2D(pool_size=3, padding=1, strides=1)
        self.p4_conv_2 = nn.Conv2D(n4, kernel_size=1, activation='relu')

    def forward(self, x):
        p1 = self.p1_conv_1(x)
        p2 = self.p2_conv_2(self.p2_conv_1(x))
        p3 = self.p3_conv_2(self.p3_conv_1(x))
        p4 = self.p4_conv_2(self.p4_pool_1(x))
        return nd.Concat(p1, p2, p3, p4, dim=1)


incp = Inception(64, 96, 128, 16, 32, 32)
incp.initialize()

x = nd.random_uniform(shape=(32, 3, 64, 64))
print(incp(x).shape)

# define GoogLeNet
class GoogLeNet(nn.Block):
    def __init__(self, num_classes, verbose=False, **kwargs):
        super(GoogLeNet, self).__init__(**kwargs)
        self.verbose = verbose
        with self.name_scope():
            b1 = nn.Sequential()
            b1.add(nn.Conv2D(64, kernel_size=7, strides=2, padding=3, activation='relu'),
                   nn.MaxPool2D(pool_size=3, strides=2)
                   )
            # block 2
            b2 = nn.Sequential()
            b2.add(
                nn.Conv2D(64, kernel_size=1),
                nn.Conv2D(192, kernel_size=3, padding=1),
                nn.MaxPool2D(pool_size=3, strides=2)
            )
            # block 3
            b3 = nn.Sequential()
            b3.add(
                Inception(64, 96, 128, 16, 32, 32),
                Inception(128, 128, 192, 32, 96, 64),
                nn.MaxPool2D(pool_size=3, strides=2)
            )
            # block 4
            b4 = nn.Sequential()
            b4.add(
                Inception(192, 96, 208, 16, 48, 64),
                Inception(160, 112, 224, 24, 64, 64),
                Inception(128, 128, 256, 24, 64, 64),
                Inception(112, 114, 288, 32, 64, 64),
                Inception(256, 160, 320, 32, 128, 128),
                nn.MaxPool2D(pool_size=3, strides=2)
            )
            # block 5
            b5 = nn.Sequential()
            b5.add(
                Inception(256, 160, 320, 32, 128, 128),
                Inception(384, 192, 384, 48, 128, 128),
                nn.AvgPool2D(pool_size=2)
            )
            # block 6
            b6 = nn.Sequential()
            b6.add(
                nn.Flatten(),
                nn.Dense(num_classes)
            )

            # block 7: batch normal

            self.net = nn.Sequential()
            self.net.add(b1, b2, b3, b4, b5, b6)

    def forward(self, x):
        out = x
        for i, b in enumerate(self.net):
            out = b(out)
            if self.verbose:
                print('Block %d output: %s'%(i+1, out.shape))
        return out

net = GoogLeNet(10, True)
net.initialize()

x = nd.random_uniform(shape=(4, 3, 96, 96))
y = net(x)
print('y.shape = ', y.shape)

import utils
train_data, test_data = utils.load_data_fashion_mnist(batch_size=64, resize=96)

net = GoogLeNet(10)
loss = gluon.loss.SoftmaxCrossEntropyLoss()
net.initialize(init=init.Xavier())

trainer =  gluon.Trainer(net.collect_params(), 'sgd', {'learning_rate':0.01})

print('start training...')
utils.train(train_data, test_data, net, loss, trainer, mx.cpu(), num_epochs=1)

