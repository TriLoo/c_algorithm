from mxnet import ndarray as nd
from mxnet import autograd
from mxnet import gluon
import matplotlib as mpl
import matplotlib.pyplot as plt
import random

mpl.rcParams['figure.dpi'] = 120


num_train = 20
num_test = 100
num_input = 200                       # feature number : 200
true_w = nd.ones((num_input, 1)) * 0.01
true_b = .05

# generate data
X = nd.random.normal(shape=(num_test + num_train, num_input))
y = nd.dot(X, true_w)
y += 0.01 * nd.random.normal(shape=y.shape)

X_train, X_test = X[:num_train, :], X[num_train:, :]
y_train, y_test = y[:num_train], y[num_train:]

# generate data
batch_size = 1
def data_iter(num_examples):     # num_examples : the number of samples
    idx = list(range(num_examples))
    random.shuffle(idx)
    for i in range(0, num_examples, batch_size):
        j = nd.array(idx[i:min(i+batch_size, num_examples)])
        yield X.take(j), y.take(j)

# initialize model parameters
def get_params():
    w = nd.random.normal(shape=(num_input, 1)) * 0.01
    b = nd.zeros((1,))
    for param in (w, b):
        param.attach_grad()
    return (w, b)

# define regulation : L^2
def L2_penalty(w, b):
    return (w **2).sum() + b**2     # can remove the penalty of b^2

# define train & test

def net(X, lambd, w, b):
    return nd.dot(X, w) + b

def square_loss(yhat, y):
    return (yhat - y.reshape(yhat.shape)) ** 2

def SGD(params, lr):
    for param in params:
        param[:] = param - lr * param.grad

# cannot use test for the func name !!
def mytest(params, X, y):
    return square_loss(net(X, 0, *params), y).mean().asscalar()    # * means some variable parameters (tuple)

#def test(params, X, y):
def train(lambd):
    epoch = 10
    learning_rate = 0.002
    params = get_params()
    train_loss = []
    test_loss = []

    for e in range(epoch):
        for data, label in data_iter(num_train):
            with autograd.record():
                output = net(data, lambd, *params)
                loss = square_loss(output, label) + lambd * L2_penalty(*params)

            loss.backward()
            SGD(params, learning_rate)

        train_loss.append(mytest(params, X_train, y_train))
        test_loss.append(mytest(params, X_test, y_test))

    plt.plot(train_loss)
    plt.plot(test_loss)
    plt.legend(['train', 'test'])
    plt.show()

    return ('legend w[:10]', params[0][:10], 'learned b:', params[1])

# no regularization
#train(0)

# use regularization
train(2)





