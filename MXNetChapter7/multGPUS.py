from mxnet import nd
from mxnet import gluon
from mxnet import autograd

scale = .01
W1 = nd.random.normal(shape=(20, 1, 3, 3)) * scale
b1 = nd.zeros(shape=20)
W2 = nd.random.normal(shape=(50, 20, 5, 5)) * scale
b2 = nd.zeros(shape=50)
W3 = nd.random.normal(shape=(800, 128)) * scale
b3 = nd.zeros(shape=800)
W4 = nd.random.normal(shape=(128, 10)) * scale
b4 = nd.zeros(shape=128)

params = [W1, b1, W2, b2, W3, b3, W4, b4]

# network and loss
def lenet(X, params):
    h1_conv = nd.Convolution(X, weight=params[0], bias=params[1], kernel=(3, 3), num_filter=20)
    h1_activation = nd.Activation(h1_conv, act_type='relu')
    h1 = nd.Pooling(data=h1_activation, pool_type='avg', kernel=(2, 2), stride=(2, 2))

    h2_conv = nd.Convolution(h1, weight=params[2], bias=params[3], kernel=(5, 5), num_filter=50)
    h2_activation = nd.relu(h2_conv)
    h2 = nd.Pooling(data=h2_activation, pool_type='avg', kernel=(2, 2), stride=(2, 2))

    h2 = nd.flatten(h2)
    h3_linear = nd.dot(h2, params[4]) + params[5]
    h3 = nd.relu(h3_linear)

    yhat = nd.dot(h3, params[6]) + params[7]
    return yhat

loss = gluon.loss.SoftmaxCrossEntropyLoss()

from mxnet import gpu
def get_params(params, ctx):
    new_params = [p.copyto(ctx) for p in params]
    for p in new_params:
        p.attatch_grad()
    return new_params

# copy param to GPU(0)
new_params = get_params(params, gpu(0))
print('b1 weight = ', new_params[1])
print('b1 grad = ', new_params[1].grad)

# collect & reduce
def allreduce(data):
    for i in range(1, len(data)):
        data[0][:] += data[i].copyto(data[0].context)
    for i in range(1, len(data)):
        data[0].copyto(data[i])
        #data[i][:] = data[0].copyto(data[i].context)

data = [nd.ones((1, 2), ctx=gpu(i)) * (i + 1) for i in range(2)]
print('before', data)
allreduce(data)
print('after', data)


def split_and_load(data, ctx):
    n, k = data.shape[0], len(ctx)
    m = n // k
    assert m * k  == n
    return [data[i * m : (i + 1) * m].as_in_context(ctx[i]) for i in range(k)]

batch = nd.arange(16).reshape((4, 4))
ctx = [gpu(0), gpu(1)]
splitted = split_and_load(batch, ctx)

print('input', batch)
print('load into', ctx)
print('Output:', splitted)

import sys
import utils
# 训练一个批量
def train_batch(data, label, params, ctx, lr):
    data_list = split_and_load(data, ctx)
    label_list = split_and_load(label, ctx)

    with autograd.record():
        losses = [loss(lenet(X, W), Y) for X, W, Y in zip(data_list, params, label_list)]

    for l in losses:
        l.backward()
    for i in range(len(params[0])):
        allreduce(params[c][i].grad for c in range(len(ctx)))
    for p in params:
        utils.SGD(p, lr / data.shape[0])


from time import time
# whole train
def train(num_gpus, batch_size, lr):
    train_data, test_data = utils.load_data_fashion_mnist(batch_size)

    ctx = [gpu[i] for i in range(num_gpus)]
    print('running on', ctx)

    dev_params = [get_params(params, c) for c in ctx]

    for epoch in range(5):
        start = time()
        for data, label in train_data:
            train_batch(data, label, dev_params, ctx, lr)
        nd.waitall()
        print('Epoch: %d, training time = %.1f sec'%(epoch, time() - start))

        # valiting on GPU 0
        net = lambda data : lenet(data, dev_params[0])
        test_acc = utils.evaluate_accuracy(test_data, net, ctx[0])
        print('Validataion Accuracy = %.4f'%(test_acc))

train(2, 256, 0.8)





