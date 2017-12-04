import mxnet as mx
from mxnet import autograd
from mxnet import gluon
#from mxnet import random
from mxnet import ndarray as nd
import random
import numpy as np

mx.random.seed(1)
random.seed(1)

# prepare training datas
num_inputs = 2
num_examples = 1000
X = nd.random_normal(scale=1, shape=(num_examples, num_inputs))
true_w = [2, -3.4]
true_b = 4.2
y = true_w[0] * X[:, 0] + true_w[1] * X[:, 1] + true_b
y += 0.01 * nd.random_normal(scale=1, shape=y.shape)

dataset = gluon.data.ArrayDataset(X, y)


# define model
net = gluon.nn.Sequential()
net.add(gluon.nn.Dense(1))

# define loss function
square_loss = gluon.loss.L2Loss()

import matplotlib as mpl
mpl.rcParams['figure.dpi'] = 120
import matplotlib.pyplot as plt

# train
def train(batch_size, lr, epochs, period):
    assert  period >= batch_size and period % batch_size == 0
    # initialize parameters
    net.collect_params().initialize(mx.init.Normal(sigma=1), force_reinit=True)
    # define optimization function
    trainer = gluon.Trainer(net.collect_params(), 'sgd', {'learning_rate':lr})

    data_iter = gluon.data.DataLoader(dataset, batch_size, shuffle=True)
    total_loss = [np.mean(square_loss(net(X), y).asnumpy())]

    for epoch in range(1, 1 + epochs):
        if epoch > 2:
            lr *= .1

        for batch_i, (data, label) in enumerate(data_iter):
            with autograd.record():
                output = net(data)
                loss = square_loss(output, label)
            loss.backward()
            trainer.step(batch_size)

            if batch_i * batch_size % period == 0:
                total_loss.append(np.mean(square_loss(net(X), y).asnumpy()))

        print('Batch Size: %d. Learning_rate: %f, epoch %d, loss %.4e'%(batch_size, lr, epoch, total_loss[-1]))

    print('W:', np.reshape(net[0].weight.data().asnumpy(), (-1, 1)))
    print('b:', net[0].bias.data().asnumpy()[0], '\n')

    x_axis = np.linspace(0, epochs, len(total_loss), endpoint=True)
    plt.semilogy(x_axis, total_loss)
    plt.xlabel('epoch')
    plt.ylabel('loss')
    plt.show()


train(batch_size=10, lr=.2, epochs=3, period=10)

