from mxnet import gluon
from mxnet import ndarray as nd

# mlp based on gluon
net = gluon.nn.Sequential()
with net.name_scope():
    net.add(gluon.nn.Dense(256, activation='relu'))
    net.add(gluon.nn.Dense(10))

print(net)

# mpl based on nn.Block
class MLP(gluon.nn.Block):          # 继承自nn.Block
    def __init__(self, **keywords):
        super(MLP, self).__init__(**keywords)
        with self.name_scope():
            self.dense0 = gluon.nn.Dense(256)
            self.dense1 = gluon.nn.Dense(10)

    def forward(self, x):
        return self.dense1(nd.relu(self.dense0(x)))

net2 = MLP()
print(net2)

net2.initialize()
x = nd.random.uniform(shape=(4, 20))
y = net2(x)
print(y)

print(net2.dense0.name)

net3 = MLP(prefix='another_mpl_')
print(net3.dense0.name)


class FancyBlock(gluon.nn.Block):
    def __init__(self, **kwargs):
        super(FancyBlock, self).__init__(**kwargs)
        with self.name_scope():
            self.dense = gluon.nn.Dense(256)
            self.weight = nd.random_uniform(shape=(256, 20))

    def forward(self, x):
        x = nd.relu(self.dense(x))
        x = nd.relu(nd.dot(x, self.weight) + 1)
        x = nd.relu(self.dense(x))
        return x


fancy_mlp = FancyBlock()
fancy_mlp.initialize()
y = fancy_mlp(x)
print(fancy_mlp)
print(y.shape)

        