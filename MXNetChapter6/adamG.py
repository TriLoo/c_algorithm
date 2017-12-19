from mxnet import gluon
import mxnet as mx
from mxnet import autograd
from mxnet import random
from mxnet import ndarray as nd
import random
import numpy as np

import matplotlib as mlp
mlp.rcParams['figure.dpi'] = 120
import matplotlib.pyplot as plt

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

# define loss function
square_loss = gluon.loss.L2Loss()

# begin train
def train(batch_size, lr, epochs, period):
    assert period >= batch_size and period % batch_size == 0
    # initialize model
    net.collect_params().initialize(init=mx.init.Normal(sigma=1), force_reinit=True)

    total_loss = [np.mean(square_loss(net(X), y).asnumpy())]
    # define train function
    trainer = gluon.Trainer(net.collect_params(), 'adam', {'learning_rate':lr})
    # define data iterator
    data_iter = gluon.data.DataLoader(dataset, batch_size, shuffle=True)

    for epoch in range(1, epochs + 1):
        for batch_i, (data, label) in enumerate(data_iter):
            with autograd.record():
                output = net(data)
                loss = square_loss(output, label)
            loss.backward()
            trainer.step(batch_size)

            if batch_i * batch_size % period == 0:
                total_loss.append(np.mean(square_loss(net(X), y).asnumpy()))
        print('batch size: %d, epoch %d, loss %.4e'%(batch_size, epoch, total_loss[-1]))

    print('W: ', net[0].weight.data(),
          'b: ', net[0].bias.data(), '\n')

    x_axis = np.linspace(0, epochs, len(total_loss), endpoint=True)
    plt.semilogy(x_axis, total_loss)
    plt.xlabel('epoch')
    plt.ylabel('loss')
    plt.show()
    #print(net[0].weight.data().grad.shape)
    print('weighted shape = ', net[0].weight.data())   # w is a 2 * 1 matrix
    print('grad shape = ', net[0].weight.grad())       # is also a 2 * 1 matrix

train(batch_size=10, lr=0.1, epochs=3, period=10)
