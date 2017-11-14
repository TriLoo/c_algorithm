from mxnet import gluon
from mxnet import ndarray as nd
import matplotlib.pyplot as plt
import sys
import utils
#from utils import SGD
from mxnet import autograd

def transform(data, label):
    return data.astype('float32') / 255, label.astype('float32')

mnist_train = gluon.data.vision.FashionMNIST(train=True, transform=transform)
mnist_test = gluon.data.vision.FashionMNIST(train=False, transform=transform)
#batch_size = 256

#mnist_train, mnist_test = utils.load_data_fashion_mnist(batch_size)

data, label = mnist_train[0]
print('data.shape = ', data.shape, '\n label = ', label)

def show_images(images):
    n = images.shape[0]
    _, figs = plt.subplot(1, n, figsize=(15, 15))   # a tuple
    for i in range(n):
        figs[i].imshow(images[i].reshape((28, 28)).asnumpy())
        figs[i].axes.get_xaxis().set_visible(False)
        figs[i].axes.get_yaxis().set_visible(False)
    plt.show()

def get_text_labels(label):
    text_labels = ['t-shirt', 'trouser', 'pullover', 'dress', 'coat',
                   'sandal', 'shirt', 'sneaker', 'bag', 'ankle boot']   # alist

    return [text_labels[int(i)] for i in label]

data, label = mnist_train[0:9]    # returned labels is number
show_images(data)
print(get_text_labels(label))

# data fetch
batch_size = 256
train_data = gluon.data.DataLoader(mnist_train, batch_size, shuffle=True)
test_data = gluon.data.DataLoader(mnist_test, batch_size, shuffle=True)

# initialize model parameters
num_inputs = 784          # 784 = 28 * 28
num_outputs = 10          # ten classes
W = nd.random_normal(shape=(num_inputs, num_outputs))
b = nd.random_normal(shape=(num_outputs, 1))

params = [W, b]        # a list

# attach gradient to the parameters
for param in params:
    param.attach_grad()

# define the model
def softmax(X):
    exp = nd.exp(X);
    partition = exp.sum(axis = 1, keepdims = True)
    return exp / partition

def net(X):
    return softmax(nd.dot(X.reshape((-1, num_inputs)), W) + b)

# cross - entropy loss function
def cross_entropy(yhat, y):
    return -nd.pick(nd.log(yhat), y)

# calculation precision
def accuracy(output, label):
    return nd.mean(output.argmax(axis=1) == label).asscale()

def evaluate_accuracy(data_iterator, net):
    acc = 0.
    for data, label in data_iterator:
        output = net(data)
        acc += accuracy(output, label)
    return acc / len(data_iterator)

# train
def SGD(params, lr):
    for param in params:
        param[:] = param - lr * param.grad

learning_rate = .1
for epoch  in range(5):
    train_loss = 0.
    train_acc = 0.
    for data, label in train_data:
        with autograd.record():
            output = net(data)
            loss = cross_entropy(output, label)
        loss.backword()
        SGD(params, learning_rate / batch_size)

        train_loss += nd.mean(loss).asscale()
        train_acc += accuracy(output, label)
    test_acc = evaluate_accuracy(test_data, net)   # evaluate the accuracy on test data, not train data
    print("Epoch %d. Loss: %f, Train acc %f, Test acc %f"%(epoch, train_loss / len(train_data), train_acc / len(train_data), test_acc))

