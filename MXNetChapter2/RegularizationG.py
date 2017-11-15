from mxnet import ndarray as nd
from mxnet import autograd
from mxnet import gluon
import matplotlib as mpl
import matplotlib.pyplot as plt
#import random

mpl.rcParams['figure.dpi'] = 120


num_train = 20
num_test = 100
num_input = 200                       # feature number : 200
true_w = nd.ones((num_input, 1)) * 0.01
true_b = 0.05

# generate data
X = nd.random.normal(shape=(num_test + num_train, num_input))
y = nd.dot(X, true_w)
y += 0.01 * nd.random.normal(shape=y.shape)

X_train, X_test = X[:num_train, :], X[num_train:, :]
y_train, y_test = y[:num_train], y[num_train:]

batch_size = 1
dataset_train = gluon.data.ArrayDataset(X_train, y_train)
data_iter_train = gluon.data.DataLoader(dataset_train, batch_size, shuffle=True)

square_loss = gluon.loss.L2Loss()

def mytest(net, X, y):
    return square_loss(net(X), y).mean().asscalar()

def train(weight_decay):
    learning_rate = 0.005
    epoch = 10
    net = gluon.nn.Sequential()
    with net.name_scope():
        net.add(gluon.nn.Dense(1))
    net.initialize()

    trainer = gluon.Trainer(net.collect_params(), 'sgd', {'learning_rate':learning_rate, 'wd':weight_decay})

    train_loss = []
    test_loss = []

    for e in range(epoch):
        for data, label in data_iter_train:
            with autograd.record():
                output = net(data)
                loss = square_loss(output, label)
            loss.backward()
            trainer.step(batch_size)

        train_loss.append(mytest(net, X_train, y_train))
        test_loss.append(mytest(net, X_test, y_test))
    plt.plot(train_loss)
    plt.plot(test_loss)

    plt.legend(['train', 'test'])

    plt.show()

    return ('legend w[:10]', net[0].weight.data(), 'learned b:', net[0].bias.data())



# no regulation:
#train(0)

# with regulation:
print(train(5))


