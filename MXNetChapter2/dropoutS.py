from mxnet import nd
from mxnet import gluon
from mxnet import autograd
import utils
batch_size = 256


def dropout(X, drop_probability):
    keep_probability = 1 - drop_probability
    assert 0 <= keep_probability <= 1
    #print('keep_probability = %f'%(keep_probability))

    if keep_probability == 1:
        X.zeros_like()

    mask = nd.random.uniform(0, 1.0, X.shape, ctx=X.context) < keep_probability
    #print(mask)       # for test

    scale = 1 / keep_probability

    return mask * X * scale

'''
A = nd.arange(20).reshape((5, 4))
#print(dropout(A, 0.0))
print(dropout(A, 0.5))
'''

train_data, test_data = utils.load_data_fashion_mnist(batch_size)
print('data len = %d'%(len(train_data)))

num_input = 28 * 28
num_output = 10

num_hidden1 = 256
num_hidden2 = 256
weight_scale = 0.01

w1 = nd.random_normal(shape=(num_input, num_hidden1), scale=weight_scale)
b1 = nd.zeros(num_hidden1)

w2 = nd.random_normal(shape=(num_hidden1, num_hidden2), scale=weight_scale)
b2 = nd.zeros(num_hidden2)

w3 = nd.random_normal(shape=(num_hidden2, num_output), scale=weight_scale)
b3 = nd.zeros(num_output)

params = [w1, w2, w3, b1, b2, b3]
for param in params:
    param.attach_grad()

#define model
# add dropout layer after active layer
drop_prob1 = 0.2
drop_prob2 = 0.5

def net(X):
    X = X.reshape((-1, num_input))
    h1 = nd.relu(nd.dot(X, w1) + b1)
    h1 = dropout(h1, drop_prob1)
    h2 = nd.relu(nd.dot(h1, w2) + b2)
    h2 = dropout(h2, drop_prob2)
    return nd.dot(h2, w3) + b3

# train :
softmax_corss_entropy = gluon.loss.SoftmaxCrossEntropyLoss()

learning_rate = .5
for epoch in range(5):
    train_loss = 0.
    train_acc = 0.

    for data, label in  train_data:
        with autograd.record():
            output = net(data)
            loss = softmax_corss_entropy(output, label)

        loss.backward()
        utils.SGD(params, learning_rate)

        train_loss += nd.mean(loss).asscalar()
        train_acc += utils.accuracy(output, label)

    test_acc = utils.evaluate_accuracy(test_data, net)
    print("Epoch: %d. Loss: %f, Train acc %f, Test acc %f"%(epoch, train_loss / len(train_data), train_acc / len(train_data), test_acc))


