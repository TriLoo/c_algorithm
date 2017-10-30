from mxnet import ndarray as nd
import numpy as np
import os

x = nd.ones((3, 4))

y = nd.random_normal(0, 1, shape=(3, 4))

print(x.shape)
print(y.shape)
print(y.size)
#print(y)

print(x * y)


# boradcast
a = nd.arange(3).reshape((3, 1))
b = nd.arange(2).reshape((1, 2))
print('a:', a)
print('b:', b)
print('a + b: ', a + b)


x = np.ones((2, 3))
y = nd.array(x)   # numpy -> mxnet
z = y.asnumpy()

print([z, y])

x = nd.ones((3, 4))
y = nd.ones((3, 4))
before = id(y)
y = x + y
print(id(y) == before)

before = id(y)
y[:] = y + x
print(id(y) == before)

nd.elemwise_add(x, y, out = y)
print(id(y) == before)

