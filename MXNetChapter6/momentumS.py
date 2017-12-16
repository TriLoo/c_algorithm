import mxnet as mx
from mxnet import autograd
from mxnet import ndarray as nd
from mxnet import gluon
import random
import matplotlib as mpl
mpl.rcParams['figure.dpi'] = 120
import matplotlib.pyplot as plt
import numpy as np


def sgd_momentum(params, vs, lr, mom, batch_size):
    for param, v in zip(params, vs):
        v[:] = mom * v + lr * param.grad / batch_size
        param[:] -= v


mx.random.seed(1)
random.seed(1)

num_inputs = 2
num_examples = 1000
true_w = [2, -3.4]
true_b = 4.2

X = nd.random.normal(scale=1, shape=(num_examples, num_inputs))
y = true_w[0] * X[:, 0] + true_w[1] * X[:, 1] + true_b
y += nd.random_normal(scale=1, shape=y.shape)

dataset = gluon.data.ArrayDataset(X, y)

# get the data iterator
def data_iter(batch_size):
    idx = list(range(num_examples))
    random.shuffle(idx)
    for batch_i, i in enumerate(range(0, num_examples, batch_size)):
        j = nd.array(idx[i:min(i+batch_size, num_examples)])
        yield batch_i, X.take(j), y.take(j)

# initialize model parameters
def init_params():
    w = nd.random_normal(scale=1, shape=(num_inputs, 1))
    b = nd.zeros(shape=(1,))

    params = [w, b]
    vs = []       # 存储速度的list
    for param in params:
        param.attach_grad()
        # 把速度项初始化为和参数形状相同的零向量
        vs.append(param.zeros_like())
    return params, vs

# define model
def net(X, w, b):
    return nd.dot(X, w) + b

# define loss function
def square_loss(yhat, y):
    return (yhat - y.reshape(yhat.shape)) ** 2 / 2

# begin train model
def train(batch_size, lr, mom, epochs, period):
    assert period >= batch_size and period % batch_size == 0
    [w, b], vs = init_params()
    total_loss = [np.mean(square_loss(net(X, w, b), y).asnumpy())]

    for epoch in range(1, 1+epochs):
        if(epoch > 2):
            lr *= .1
        for batch_i, data, label in data_iter(batch_size):
            with autograd.record():
                output = net(data, w, b)
                loss = square_loss(output, label)
            loss.backward()
            sgd_momentum([w, b], vs, lr, mom, batch_size)
            if batch_i * batch_size % period == 0:
                total_loss.append(np.mean(square_loss(net(X, w, b), y).asnumpy()))
        print('batch size %d, learning rate: %f, epoch %d, loss %.4e'%(batch_size, lr, epoch, total_loss[-1]))

    print('w:', np.reshape(w.asnumpy(), (1, -1)), ' b:', b.asnumpy()[0], '\n')
    x_axis = np.linspace(0, epochs, len(total_loss), endpoint=True)
    plt.semilogy(x_axis, total_loss)
    plt.xlabel('epoch')
    plt.ylabel('loss')
    plt.show()

train(batch_size=10, lr=.2, mom=0.9, epochs=3, period=10)

