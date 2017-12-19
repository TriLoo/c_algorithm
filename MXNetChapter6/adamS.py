import mxnet as mx
from mxnet import gluon
from mxnet import autograd
from mxnet import random
from mxnet import ndarray as nd
import random
import numpy as np

import matplotlib as mlp
mlp.rcParams['figure.dpi'] = 120
import matplotlib.pyplot as plt

mx.random.seed(1)
random.seed(1)

# Adam: 定义了一阶矩 + 二阶矩进行自适应学习率
def adam(params, lr, vals, sqrs, iter, batch_size, beta1 = 0.9, beta2 = 0.999):
    eps_stable = 1e-8
    for param, val, sqr in zip(params, vals, sqrs):
        g = param.grad / batch_size
        val[:] = beta1 * val + ( 1 - beta1 ) * g
        sqr[:] = beta2 * sqr + ( 1 - beta2 ) * nd.square(g)
        #val_next = val / (1 - nd.power(beta1, iter))
        val_next = val / (1. - beta1 ** iter)
        #sqr_next = sqr / (1. - nd.power(beta2, iter))
        sqr_next = sqr / (1. - beta2 ** iter)
        g_next = lr * val_next / (nd.sqrt(sqr_next) + eps_stable)
        param[:] -= g_next

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
def net(X, w, b):
    return nd.dot(X, w) + 1

# define initialization function
def init_params():
    w = nd.random.normal(scale=1, shape=(num_inputs, 1))
    b = nd.zeros(shape=(1, ))
    vals = []
    sqrs = []
    params = [w, b]
    for param in params:
        param.attach_grad()
        vals.append(param.zeros_like())
        sqrs.append(param.zeros_like())
    return params, vals, sqrs

# define loss function
def square_loss(yhat, y):
    return (yhat - y.reshape(yhat.shape)) ** 2 / 2

# define data iterator
def data_iter(batch_size):
    idx = list(range(num_examples))
    random.shuffle(idx)
    for batch_i, i in enumerate(range(0, num_examples, batch_size)):
        j = nd.array(idx[i : min(i + batch_size, num_examples)])
        yield batch_i, X.take(j), y.take(j)

# begin train
def train(batch_size, lr, epochs, period, beta1 = 0.9, beta2 = 0.999 ):
    assert period >= batch_size and period % batch_size == 0
    # initialization parameters
    [w, b], vals, sqrs = init_params()
    total_loss = [np.mean(square_loss(net(X, w, b), y).asnumpy())]

    t = 0
    for epoch in range(1, epochs + 1):    # 因为索引为0的地方已经存有数据了，上面
        for batch_i, data, label in data_iter(batch_size):
            with autograd.record():
                output = net(data, w, b)
                loss = square_loss(output, label)
            loss.backward()
            t += 1
            adam([w, b], lr, vals, sqrs, t, batch_size)
            if(batch_i * batch_size % period == 0):
                total_loss.append(np.mean(square_loss(net(X, w, b), y).asnumpy()))

        print('Epoch %d, learing_rate: %.4e, Total loss: %.4e'%(epoch, lr, total_loss[-1]))

    print('w: ', w, 'b: ', b, '\n')

    # plot
    X_axis = np.linspace(0, num_examples, num=len(total_loss), endpoint=True)
    plt.semilogy(X_axis, total_loss)
    plt.xlabel('Epochs')
    plt.ylabel('Total loss')
    plt.show()

train(batch_size=10, lr=0.1, epochs=3, period=10)


