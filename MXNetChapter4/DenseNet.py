from mxnet import gluon
from mxnet import nd
from mxnet.gluon import nn
import utils
from mxnet import init
import mxnet as mx


def conv_block(channels):
    out = nn.Sequential()
    out.add(
        nn.BatchNorm(),
        nn.Activation('relu'),
        nn.Conv2D(channels, kernel_size=3, padding=1)
    )
    return out

class DenseBlock(nn.Block):
    def __init__(self, layers, growth_rate, **kwargs):
        super(DenseBlock, self).__init__(**kwargs)
        self.net = nn.Sequential()
        for i in range(layers):
            self.net.add(conv_block(growth_rate))

    def forward(self, x):
        for layers in self.net:
            out = layers(x)
            x = nd.concat(x, out, dim = 1)
        return x

dblk = DenseBlock(2, 10)
dblk.initialize()

x = nd.random_uniform(shape=(4, 3, 8, 8))
print(dblk(x).shape)


# Transition Block
def transition_block(channels):
    out = nn.Sequential()
    out.add(
        nn.BatchNorm(),
        nn.Activation('relu'),
        nn.Conv2D(channels, kernel_size=1),
        nn.AvgPool2D(pool_size=2, strides=2)
    )

    return out


tblk = transition_block(10)
tblk.initialize()

print(tblk(x).shape)

# define DenseNet
init_channels = 64
growth_rate = 32
block_layers = [6, 12, 24, 16]
num_classes = 10

def dense_net():
    net = nn.Sequential()
    with net.name_scope():
        net.add(
            nn.Conv2D(init_channels, kernel_size=7, strides=2, padding=3),
            nn.BatchNorm(),
            nn.Activation('relu'),
            nn.MaxPool2D(pool_size=3, strides=2, padding=1)
        )

        # dense block
        channels = init_channels
        for i, layer in enumerate(block_layers):
            net.add(DenseBlock(layer, growth_rate))
            channels +=  layer * growth_rate
            if i != len(block_layers) - 1:
                net.add(transition_block(channels // 2))

        # last block
        net.add(
            nn.BatchNorm(),
            nn.Activation('relu'),
            nn.AvgPool2D(pool_size=1),
            nn.Flatten(),
            nn.Dense(num_classes)
        )
        return net

train_data, test_data = utils.load_data_fashion_mnist(batch_size=64, resize=32)

net = dense_net()
net.initialize(init=init.Xavier())

loss = gluon.loss.SoftmaxCrossEntropyLoss()
trainer = gluon.Trainer(net.collect_params(), 'sgd', {'learning_rate':0.1})

print("start training...")
utils.train(train_data, test_data, net, loss, trainer, ctx=mx.cpu(), num_epochs = 1)
