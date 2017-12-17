import mxnet as mx
from mxnet import gluon
from mxnet import ndarray as nd
import numpy as np
from mxnet import random
from mxnet import autograd

import matplotlib as mlp
mlp.rcParams['figure.dpi'] = 120
import matplotlib.pyplot as plt

import random
mx.random.seed(1)
random.seed(1)

# prepare data
num_inputs = 2
num_examples = 1000
true_w = [2, -3.4]
true_b = 4.2
X = nd.random.normal(scale=1, shape=(num_examples, num_inputs))
y = true_w[0] * X[:, 0] + true_w[1] * X[:, 1] + true_b
y += 0.01 * nd.random.normal(scale=1, shape=y.shape)
dataset = gluon.data.ArrayDataset(X, y)

# define model
net = gluon.nn.Sequential()
net.add(gluon.nn.Dense(1))

# initialize model
net.initialize()

# define loss func.
square_loss = gluon.loss.L2Loss()

# train
def train(batch_size, lr, gamma, epochs, period):
    assert period >= batch_size and batch_size % period == 0
    net.collect_params().initialize(init=mx.init.Normal(sigma=1), force_reinit=True)

    # define trainer
    trainer = gluon.Trainer(net.collect_params(), 'rmsprop', {'learning_rate':lr, 'gamma1':gamma})

    # define data iterator
    data_iter = gluon.data.DataLoader(dataset, batch_size, shuffle=True)
    total_loss = [np.mean(square_loss(net(X), y).asnumpy())]

    for epoch in range(1, 1 + epochs):
        for batch_i, (data, label) in enumerate(data_iter):
            with autograd.record():
                output = net(data)
                loss = square_loss(output, label)
            loss.backward()
            trainer.step(batch_size)

            if batch_i * batch_size % period == 0:
                total_loss.append(np.mean(square_loss(net(X), y).asnumpy()))

        print('batch size: %d, learning rate: %f, epoch %d, loss %.4e'%(batch_size, trainer.learning_rate, epoch, total_loss[-1]))

    print('w:', np.reshape(net[0].weight.data().asnumpy(), (-1, 1)),
          'b:', net[0].bias.data().asnumpy()[0], '\n')
    x_axis = np.linspace(0, epochs, len(total_loss), endpoint=True)
    plt.semilogy(x_axis, total_loss)
    plt.xlabel('epoch')
    plt.ylabel('loss')
    plt.show()

train(batch_size=10, lr=0.03, gamma=0.9, epochs=3, period=10)

