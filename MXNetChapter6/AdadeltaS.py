import mxnet as mx
from mxnet import gluon
from mxnet import autograd
from mxnet import random
import random
from mxnet import ndarray as nd
import numpy as np

import matplotlib as mpl
mpl.rcParams['figure.dpi'] = 120
import matplotlib.pyplot as plt

mx.random.seed(1)
random.seed(1)

def adadelta(params, sqrs, deltas, roh, batch_size):
    eps_stable = 1e-5
    for param, sqr, delta in zip(params, sqrs, deltas):
        g = param.grad / batch_size
        sqr[:] = roh * sqr + (1. - roh) * nd.square(g)
        g_next = nd.sqrt(delta + eps_stable) / nd.sqrt(sqr + eps_stable) * g
        delta[:] = roh * delta + (1. - roh) * g_next * g_next
        param[:] -= g_next

num_inputs = 2
num_examples = 1000
true_w = [2, -3.4]
true_b = 4.2
X = nd.random.normal(scale=1, shape=(num_examples, num_inputs))
y = true_w[0] * X[:, 0] + true_w[1] * X[:, 1] + true_b
y += 0.01 * nd.random.normal(scale=1, shape=y.shape)

dataset = gluon.data.ArrayDataset(X, y)

def data_iter(batch_size):
    idx = list(range(num_examples))
    random.shuffle(idx)
    for batch_i, i in enumerate(range(0, num_examples, batch_size)):
        j = nd.array(idx[i:min(i+batch_size, num_examples)])
        yield batch_i, X.take(j), y.take(j)


def init_params():
    w = nd.random.normal(scale=1, shape=(num_inputs, 1))
    b = nd.zeros(shape=(1,))
    params = [w, b]
    sqrs = []
    delta = []
    for param in params:
        param.attach_grad()
        sqrs.append(param.zeros_like())
        delta.append(param.zeros_like())
    return params, sqrs, delta

def net(X, w, b):
    return nd.dot(X, w) + b

def square_loss(yhat, y):
    return (yhat - y.reshape(yhat.shape)) ** 2 / 2
    #return nd.square(yhat - y.reshape(yhat.shape)) / 2

def train(batch_size, rho, epochs, period):
    assert period >= batch_size and batch_size % period == 0
    [w, b], sqrs, deltas = init_params()
    total_loss = [np.mean(square_loss(net(X, w, b), y).asnumpy())]

    for epoch in range(1, epochs + 1):
        for batch_i, data, label in data_iter(batch_size):
            with autograd.record():
                output = net(data, w, b)
                loss = square_loss(output, label)
            loss.backward()
            adadelta([w, b], sqrs, deltas, rho, batch_size)
            if batch_i * batch_size % period == 0:
                total_loss.append(np.mean(square_loss(net(X, w, b), y).asnumpy()))
        print('batch size: %d, epoch %d, loss %.4e'%(batch_size, epoch, total_loss[-1]))

    x_axis = np.linspace(0, epochs, len(total_loss), endpoint=True)
    plt.semilogy(x_axis, total_loss)
    plt.xlabel('epoch')
    plt.ylabel('loss')
    plt.show()

train(batch_size=10, rho=0.999, epochs=3, period=10)
