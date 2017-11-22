from mxnet import gluon
from mxnet import autograd
from mxnet import ndarray as nd
import utils

# 加载数据
batch_size = 256
train_data, test_data = utils.load_data_fashion_mnist(batch_size)

# 定义模型
net = gluon.nn.Sequential()
with net.name_scope():
    net.add(gluon.nn.Conv2D(channels=20, kernel_size=(5, 5)))
    # add batch norm layer
    net.add(gluon.nn.BatchNorm(axis=1))
    # add activation layer
    net.add(gluon.nn.Activation(activation='relu'))
    # add pooling layer
    net.add(gluon.nn.MaxPool2D(pool_size=(2, 2), strides=(2, 2)))

    # add 2nd convolution layer
    net.add(gluon.nn.Conv2D(channels=50, kernel_size=(3, 3)))
    net.add(gluon.nn.BatchNorm(axis=1))
    net.add(gluon.nn.Activation(activation='relu'))
    net.add(gluon.nn.MaxPool2D(pool_size=(2, 2), strides=2))

    net.add(gluon.nn.Flatten())
    net.add(gluon.nn.Dense(128, activation='relu'))
    net.add(gluon.nn.Dense(10))

learning_rate = .2
net.initialize()

softmax_cross_entropy= gluon.loss.SoftmaxCrossEntropyLoss()
trainer = gluon.Trainer(net.collect_params(), 'sgd', {'learning_rate':learning_rate})


for epoch in range(5):
    train_loss = 0.
    train_acc = 0.
    for data, label in train_data:
        with autograd.record():
            output = net(data)
            loss = softmax_cross_entropy(output, label)
        loss.backward()
        trainer.step(batch_size)

    train_loss += nd.mean(loss).asscalar()
    train_acc += utils.accuracy(output, label)

    test_acc = utils.evaluate_accuracy(test_data, net)
    print("Epoch: %d. Loss: %f, Acc %f. Test Acc: %f"%(epoch, train_loss / len(train_data), train_acc / len(train_data), test_acc))



