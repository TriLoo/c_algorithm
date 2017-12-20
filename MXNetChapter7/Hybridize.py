import mxnet as mx
from mxnet import gluon
from mxnet import autograd
from mxnet import random
from mxnet import ndarray as nd
import random
import numpy as np
from time import time
from mxnet import sym

import matplotlib as mlp
mlp.rcParams['figure.dpi'] = 120
import matplotlib.pyplot as plt

mx.random.seed(1)
random.seed(1)

def get_net():
    net = gluon.nn.HybridSequential()
    with net.name_scope():
        net.add(
            gluon.nn.Dense(256, activation='relu'),
            gluon.nn.Dense(128, activation='relu'),
            gluon.nn.Dense(2)
        )

    net.initialize()
    return net

x = nd.random.normal(shape=(1, 512))
net = get_net()
print(net(x))

net.hybridize()
print(net(x))

x = sym.var('data')
y = net(x)
print(y)

class HybridNet(gluon.nn.HybridBlock):
    def __init__(self, **kwargs):
        super(HybridNet, self).__init__(**kwargs)
        with self.name_scope():
            self.fc1 = gluon.nn.Dense(10)
            self.fc2 = gluon.nn.Dense(2)

    def hybrid_forward(self, F, x, *args, **kwargs):
        print(F)
        print(x)
        x = F.relu(self.fc1(x))
        print(x)
        return self.fc2(x)

net = HybridNet()
net.initialize()
x = nd.random.normal(shape=(1, 4))
y = net(x)
print(y)

net.hybridize()
y = net(x)
print(y)

print(net(x))      # output nothing, because no python program is running


