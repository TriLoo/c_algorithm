from mxnet import gluon
from mxnet import ndarray as nd
import mxnet as mx

x = nd.array([1, 2, 3])
print(x.context)