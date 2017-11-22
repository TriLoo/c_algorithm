from mxnet.gluon import nn
from mxnet import nd
from mxnet import gluon
from mxnet import init
import utils
import mxnet as mx

def vggBlock(num_convs, channel):
    out = nn.Sequential()
    for _ in range(num_convs):
        out.add(nn.Conv2D(channels=channel, kernel_size=3, padding=1, activation='relu'))

    out.add(nn.MaxPool2D(pool_size=2, strides=2))
    return out

blk = vggBlock(2, 128)
blk.initialize()

x = nd.random_uniform(shape=(2, 3, 16, 16))
y = blk(x)
print(y.shape)

# define VGG11
def vggStack(architecture):
    out = nn.Sequential()
    for (num_convs, channel) in architecture:
        out.add(vggBlock(num_convs, channel))
    return out

num_outputs = 10
architecture = ((1, 64), (1, 128), (2, 256), (2, 256), (2, 512))
net = nn.Sequential()
with net.name_scope():
    net.add(
        vggStack(architecture),
        nn.Flatten(),
        nn.Dense(4096, activation='relu'),
        nn.Dropout(.5),
        nn.Dense(4096, activation='relu'),
        nn.Dropout(.5),
        nn.Dense(num_outputs))

# train
train_data, test_data = utils.load_data_fashion_mnist(batch_size=64, resize=96)
net.initialize(init=init.Xavier())

softmax_cross_entropy = gluon.loss.SoftmaxCrossEntropyLoss()
trainer = gluon.Trainer(net.collect_params(), 'sgd', {'learning_rate':0.05})

utils.train(train_data, test_data, net, softmax_cross_entropy, trainer, mx.cpu(), num_epochs=1)


