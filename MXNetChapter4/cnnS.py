from mxnet import nd
w = nd.arange(4).reshape((1, 1, 2, 2))

b = nd.array([1])

data = nd.arange(9).reshape((1, 1, 3, 3))
out = nd.Convolution(data, w, b, kernel=w.shape[2:], num_filter=w.shape[1])

print('input', data, '\n\n weight:', w, '\n\nbias:', b, '\n\nout', out)

