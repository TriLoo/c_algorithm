import mxnet as mx
from mxnet import gluon
from mxnet import ndarray as nd
from mxnet import init

x = nd.ones(3)
y = nd.zeros(4)

# save ndarray
filename = './data/test1.params'
nd.save(filename, [x, y])     # a list

# load ndarray
a, b, = nd.load(filename)
print(a == x)
print(b == y)

# other data type
mydict = {'x':x, 'y':y}
filename = './data/test2.params'
nd.save(filename, mydict)

c = nd.load(filename)
print(c)


# save & load gluon model parameters
def get_net():
    net = gluon.nn.Sequential()
    with net.name_scope():
        net.add(gluon.nn.Dense(10, activation='relu'))
        net.add(gluon.nn.Dense(2))
    return net

net = get_net()
net.initialize()
x = nd.random_uniform(shape=(2, 10))    # 10个feature, 2 个样本
#net(x)
print(net(x))
print(x.shape)
print(net[0].weight.shape)      # return 10 * 10

# save model
filename = './data/mpl.params'
net.save_params(filename)

# load model
net2 = get_net()
net2.load_params(filename, mx.cpu())
print(net2(x))    # same as net(x)


