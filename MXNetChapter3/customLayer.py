from mxnet import nd
from mxnet import gluon
from mxnet.gluon import nn

class CentreredLayer(nn.Block):
    def __init__(self, **kwargs):
        super(CentreredLayer, self).__init__(**kwargs)

    def forward(self, x):
        return x - x.mean()

layer = CentreredLayer()
print(layer(nd.array([1, 2, 3, 4, 5])))     # print [-2, -1, 0, 1, 2]

net = nn.Sequential()
with net.name_scope():
    net.add(nn.Dense(128))
    net.add(nn.Dense(10))
    net.add(CentreredLayer())

net.initialize()
y = net(nd.random_uniform(shape=(4, 8)))
#y.mean()
print('y = ', y.mean())    # 近似 = 0

my_param = gluon.Parameter("exciting_parameter_yay", shape=(3, 3))
my_param.initialize()
print(my_param.data(), my_param.grad())

pd = gluon.ParameterDict(prefix='block1_')
pd.get('exciting_parameter_yay', shape=(3, 3))
print(pd)

class MyDense(nn.Block):
    def __init__(self, units, in_units, **kwargs):
        super(MyDense, self).__init__(**kwargs)
        with self.name_scope():
            self.weight = self.params.get('weight', shape=(in_units, units))   # in_units is the feature number
            self.bias = self.params.get('bias', shape=(units, ))

    def forward(self, x):
        linear = nd.dot(x, self.weight.data()) + self.bias.data()
        return nd.relu(linear)

dense = MyDense(5, in_units=10, prefix='o_my_dense_')   # 5 is dense output, 10 is feature number
print(dense.params)

dense.initialize()
print(dense(nd.random_uniform(shape=(2, 10))))




