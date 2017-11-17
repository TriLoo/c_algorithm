from mxnet import gluon
from mxnet import init
from mxnet import autograd
from mxnet import ndarray as nd

def get_net():
    net = gluon.nn.Sequential()
    with net.name_scope():
        net.add(gluon.nn.Dense(4, activation='relu'))
        net.add(gluon.nn.Dense(2))
    return net

net = get_net()
print("net.name = ", net.name)
print("net = ", net)

x = nd.random.normal(shape=(4, 20))

net.initialize()
net(x)
w = net[0].weight
b = net[0].bias

print("w = ", w)
print("b = ", b)

print('w data = ', w.data())
print('b data = ', b.data())

params = net.collect_params()
print('params = ', params)

params.initialize(init=init.Normal(sigma=0.02), force_reinit=True)
print(net[0].weight.data(), net[0].bias.data())

# parameters share
# net = gluon.nn.Sequential()

netNew = gluon.nn.Sequential()
with netNew.name_scope():
    netNew.add(gluon.nn.Dense(4, activation='relu'))        # 0 layer
    netNew.add(gluon.nn.Dense(4, activation='relu'))        # 1 layer
    netNew.add(gluon.nn.Dense(4, activation='relu', params=netNew[-1].params))    # 2 layer, but netNew[-1] is the 1-th layer fow now
    netNew.add(gluon.nn.Dense(2))                           # 3 layer, or -1 layer for now

netNew.initialize()
netNew(x)
print(netNew)
print(netNew[1].weight.data())
print(netNew[2].weight.data())
print(netNew[-1].weight.data())

# use custom initialization
class MyInit(init.Initializer):     # 继承自init.Initializer
    def __init__(self):
        super(MyInit, self).__init__()
        self._verbose = True

    def _init_weight(self, _, arr):    # 重载了基类的_init_weight函数，并且是 private 的
        print('init weight ', arr.shape)
        nd.random.uniform(low=5, high = 10, out = arr)

netOwn = get_net()
netOwn.initialize(MyInit())
#netOwn.initialize()
netOwn(x)
print(netOwn)
print(netOwn[0].weight.data())

w = netOwn[1].weight
w.set_data(nd.ones(w.shape))              # TODO: not work for now ... why ?
print('init to all 1:', net[1].weight.data())

