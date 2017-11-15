from mxnet import gluon
from mxnet import ndarray as nd
from mxnet import autograd
import utils

drop_prob1 = 0.2
drop_prob2 = 0.8

batch_size = 256
train_data, test_data = utils.load_data_fashion_mnist(batch_size)


net = gluon.nn.Sequential()
with net.name_scope():
    net.add(gluon.nn.Flatten())
    net.add(gluon.nn.Dense(256, activation='relu'))
    net.add(gluon.nn.Dropout(drop_prob1))
    net.add(gluon.nn.Dense(256, activation='relu'))
    net.add(gluon.nn.Dropout(drop_prob2))
    net.add(gluon.nn.Dense(10))

net.initialize()

softmax_corss_entropy = gluon.loss.SoftmaxCrossEntropyLoss()

trainer = gluon.Trainer(net.collect_params(), 'sgd', {'learning_rate':0.5})

for epoch in range(5):
    train_loss = 0.
    train_acc = 0.
    for data, label in train_data:
        with autograd.record():
            output = net(data)
            loss = softmax_corss_entropy(output, label)
        loss.backward()
        trainer.step(batch_size)
        train_loss += nd.mean(loss).asscalar()
        train_acc += utils.accuracy(output, label)

    test_acc = utils.evaluate_accuracy(test_data, net)
    print('Epoch %d. Loss: %f, Train acc %f, Test acc %f'%(epoch, train_loss / len(train_data), train_acc/len(train_data), test_acc))

