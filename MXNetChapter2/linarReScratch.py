from mxnet import ndarray as nd
from mxnet import autograd
import random

num_inputs = 2
num_examples = 1000

true_w = [2, -3.14]
true_b = 4.2

X = nd.random_normal(shape=(num_examples, num_inputs))
y = true_w[0] * X[:, 0] + true_w[1] * X[:, 1] + true_b
y += 0.01 * nd.random_normal(shape = y.shape)

batch_size = 10
def data_iter():
    idx = list(range(num_examples))
    random.shuffle(idx)
    for i in range(0, num_examples, batch_size):
        j = nd.array(idx[i:min(i+batch_size, num_examples)])
        yield nd.take(X, j), nd.take(y, j)

# read a batch size data
for data, label in data_iter():
    print(data, label)
    break

w = nd.random_normal(shape = (num_inputs, 1))
b = nd.zeros((1,))

params = [w, b]   # a list

print('params = {}'.format(params))

for param in params:
    param.attach_grad()

# define a model
def net(x):
    #print('w.shape = ', w.shape)
    #print('in net, x.shape = ', x.shape)
    return nd.dot(x, w) + b

def square_loss(yhat, y):
    #print(yhat.shape)
    #print(y.shape)
    return (yhat - y.reshape(yhat.shape)) ** 2
print('After square loss')
# 优化
def SGD(params, lr):
    for param in params:
        param[:] = param - lr * param.grad

# training
epochs = 5
learning_rate = .001
for e in range(epochs):
    total_loss = 0
    for data, label in data_iter():
        with autograd.record():
            #print('Training...')
            #print(data.shape)
            output = net(data)
            #print(output.shape)
            #print(label.shape)
            loss = square_loss(output, label)
        loss.backward()
        SGD(params,learning_rate)

        total_loss += nd.sum(loss).asscalar()

    print("Epoch %d, average loss : %f"%(e, total_loss / num_examples))

print(true_w, w)
print(true_b, b)
