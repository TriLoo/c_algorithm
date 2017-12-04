def sgd(params, lr, batch_size):
    for param in params:
        param[:] = param - lr * param.grad / batch_size


import mxnet as mx
from mxnet import autograd
from mxnet import ndarray as nd
from mxnet import gluon
import random

mx.random.seed(1)
random.seed(1)

num_inputs = 2
num_examples = 1000

X = nd.random_normal(scale=1, shape=(num_examples, num_inputs))
true_w = [2, -3.4]
true_b = 4.2
#y = X * true_w + true_b
y = true_w[0] * X[:, 0] + true_w[1] * X[:, 1] + true_b
y += 0.01 * nd.random_normal(scale=1, shape=y.shape)

dateset = gluon.data.ArrayDataset(X, y)

# define interator
def data_iter(batch_size):
    idx = list(range(num_examples))
    random.shuffle(idx)
    for batch_i, i in enumerate(range(0, num_examples, batch_size)):   # batch_i: the i-th batch update
        j = nd.array(idx[i:min(num_examples, i+batch_size)])
        yield batch_i, X.take(j), y.take(j)


mybatch = data_iter(5)
print(mybatch)

def init_params():
    w = nd.random_normal(scale=1, shape=(num_inputs, 1))
    b = nd.zeros(shape=(1,))
    params = [w, b]
    for param in params:
        param.attach_grad()
    return params

def net(X, w, b):
    return nd.dot(X, w) + b

def square_loss(yhat, y):
    return (yhat - y.reshape(yhat.shape)) ** 2 / 2

import matplotlib as mpl
mpl.rcParams['figure.dpi'] = 120
import matplotlib.pyplot as plt
import numpy as np

def train(batch_size, lr, epochs, period):
    assert period >= batch_size and period % batch_size == 0
    w, b = init_params()
    total_loss = [np.mean(square_loss(net(X, w, b), y).asnumpy())]

    for epoch in range(1, epochs+1):
        if epoch > 2:
            lr *= 0.1
        for batch_i, data, label in data_iter(batch_size):
            with autograd.record():
                output = net(data, w, b)
                loss = square_loss(output, label)
            loss.backward()
            sgd([w, b], lr, batch_size)
            if (batch_i * batch_size) % period == 0:
                total_loss.append(np.mean(square_loss(net(X, w, b), y).asnumpy()))
        #print(total_loss[-1])
        print('batch_size %d, learning rate %f, Epoch %d, loss %.4e'%(batch_size, lr, epoch, total_loss[-1]))

    print('W: {}'.format(np.reshape(w.asnumpy(), (1, -1))))
    print('b: {}'.format(b.asnumpy()[0]))

    x_axis = np.linspace(0, epochs, len(total_loss), endpoint=True)
    plt.semilogy(x_axis, total_loss)
    plt.xlabel('epoch')
    plt.ylabel('loss')
    plt.show()

train(10, lr=.2, epochs=3, period=10)




