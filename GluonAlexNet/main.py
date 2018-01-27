import mxnet as mx
from mxnet import gluon
from mxnet import autograd
from mxnet import ndarray as nd
import os

# Define the model
class AlexNet(gluon.nn.Block):
    def __init__(self, **kwargs):
        super(AlexNet, self).__init__(**kwargs)
        self.net = gluon.nn.Sequential()
        with self.name_scope():
            self.net.add(gluon.nn.Conv2D(channels=96, kernel_size=(11, 11), strides=4, activation='relu'),   # first convolution layer
                         gluon.nn.MaxPool2D(pool_size=(3, 3), strides=2),
                         # TODO: Add Local Response Normalization
                         # Second convolution layer
                         gluon.nn.Conv2D(channels=256, kernel_size=(5, 5), padding=2, activation='relu'),
                         gluon.nn.MaxPool2D(pool_size=(3, 3), strides=2),
                         # TODO: Add Local Response Normalization here
                         # Third Convolution layer
                         gluon.nn.Conv2D(channels=384, kernel_size=(3, 3), padding=2, activation='relu'),
                         # Fourth Convoluton layer
                         gluon.nn.Conv2D(channels=384, kernel_size=(3, 3), padding=2, activation='relu'),
                         # Fifth Convolution layer
                         gluon.nn.Conv2D(channels=256, kernel_size=(3, 3), padding=2, activation='relu'),
                         gluon.nn.MaxPool2D(pool_size=(3, 3), strides=2),
                         # Flatten, First Full Connection layer
                         gluon.nn.Flatten(),
                         gluon.nn.Dense(units=4096, activation='relu'),
                         gluon.nn.Dropout(rate=0.5),
                         # Second Full Connection layer
                         gluon.nn.Dense(units=4096, activation='relu'),
                         gluon.nn.Dropout(rate=0.5),
                         # The output layer
                         gluon.nn.Dense(units=10, activation='relu')    # Only 10 classes
                         )

    def forward(self, x):
        return nd.softmax(self.net(x))


# define Train Function
def train():
    print('Training ...')

# define training target
net = AlexNet()

# load data  OR  Train
if os.path.exists('./AlexNet.params'):
    net.load_params('AlexNet.params', allow_missing=False)
else:
    # Train
    train()
    # save parameters
    net.save_params('AlexNet.params')

# Test

