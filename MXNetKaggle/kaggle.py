from mxnet import gluon
from mxnet import autograd
from mxnet import ndarray as nd
import matplotlib as mpl
mpl.rcParams['figure.dpi'] = 120
import matplotlib.pyplot as plt

import sys
sys.path.append("..")
import utils

# process data
import pandas as pd
import numpy as np

train = pd.read_csv('./datas/train.csv')
test = pd.read_csv('./datas/test.csv')

print('train.shape = ', train.shape)       # 比test data多一列价格
print('test.shape = ', test.shape)

all_X = pd.concat((train.loc[:, 'MSSubClass':'SaleCondition'], test.loc[:, 'MSSubClass':'SaleCondition']))    # 79 features
print('all_X shape = ', all_X.shape)

# pre-process the data, 标准化: 减去均值，然后除以方差
numeric_feats = all_X.dtypes[all_X.dtypes != 'object'].index
all_X[numeric_feats] = all_X[numeric_feats].apply(lambda x: (x - x.mean()) / (x.std()))
all_X = pd.get_dummies(all_X, dummy_na=True)

# 用本特征的平均估计填充缺失信息
all_X = all_X.fillna(all_X.mean())

num_train = train.shape[0]              # return 1046

X_train = all_X[:num_train].as_matrix()
X_test = all_X[num_train:].as_matrix()
y_train = train.SalePrice.as_matrix()

# 导入NDArray格式
X_train = nd.array(X_train)
y_train = nd.array(y_train)
y_train.reshape((num_train, 1))

X_test = nd.array(X_test)


square_loss = gluon.loss.L2Loss()

def get_rmse_log(net, X_train, y_train):
    num_train = X_train.shape[0]
    clipped_preds = nd.clip(net(X_train), 1, float('inf'))
    return np.sqrt(2 * nd.sum(square_loss(nd.log(clipped_preds), nd.log(y_train))).asscalar() / num_train)


#define model
def get_net():
    net = gluon.nn.Sequential()
    with net.name_scope():
        net.add(gluon.nn.Flatten())
        net.add(gluon.nn.Dense(256))
        net.add(gluon.nn.Dense(1))
    net.initialize()
    return net

def train(net, X_train, y_train, X_test, y_test, epochs,
          verbose_epoch, learning_rate, weight_decay):
    train_loss = []

    if X_test is not None:
        test_loss = []

    batch_size = 100
    dataset_train = gluon.data.ArrayDataset(X_train, y_train)
    data_iter_train = gluon.data.DataLoader(dataset_train, batch_size, shuffle=True)

    trainer = gluon.Trainer(net.collect_params(), 'adam', {'learning_rate':learning_rate, 'wd':weight_decay})
    net.collect_params().initialize(force_reinit=True)

    for epoch in range(epochs):
        for data, label in data_iter_train:
            with autograd.record():
                output = net(data)
                loss = square_loss(output, label)
            loss.backward()
            trainer.step(batch_size)

            cur_train_loss = get_rmse_log(net, X_train, y_train)
        if epoch > verbose_epoch:
            print("Epoch %d, train loss %f"%(epoch, cur_train_loss))
        train_loss.append(cur_train_loss)
        if X_test is not None:
            cur_test_loss = get_rmse_log(net, X_test, y_test)
            test_loss.append(cur_test_loss)

    plt.plot(train_loss)
    plt.legend(["train"])

    if X_test is not None:
        plt.plot(test_loss)
        plt.legend(['train', 'test'])

    plt.show()

    if X_test is not None:
        return cur_train_loss, cur_test_loss
    else:
        return cur_train_loss


# K 折交叉验证, 不需要输入专门的测试集了
def k_fold_cross_valid(k, epochs, verbose_epoch, X_train, y_train,
                       learning_rate, weight_decay):
    assert k > 1
    fold_size = X_train.shape[0] // k     # '//' 整除，结果向下取整至最接近的整数
    train_loss_sum = 0.
    test_loss_sum = 0.

    for test_i in range(k):    # range is a [0, k)
        X_val_test = X_train[test_i * fold_size:(test_i + 1) * fold_size, :]
        y_val_test = y_train[test_i * fold_size:(test_i + 1) * fold_size]

        val_train_defined = False
        for i in range(k):
            if i != test_i:
                X_cur_fold = X_train[i * fold_size:(i + 1) * fold_size, :]
                y_cur_fold = X_train[i * fold_size:(i + 1) * fold_size]

                if not val_train_defined:
                    X_val_train = X_cur_fold
                    y_val_train = y_cur_fold
                    val_train_defined = True
                else:
                    X_val_train = nd.concat(X_val_train, X_cur_fold, dim = 0)
                    y_val_train = nd.concat(y_val_train, y_cur_fold, dim = 0)
        net = get_net()
        train_loss, test_loss = train(net, X_val_train, y_val_train, X_val_test, y_val_test, epochs, verbose_epoch, learning_rate,
                                      weight_decay)

        train_loss_sum += train_loss
        print("Test loss : %f"%(test_loss))
        test_loss_sum += test_loss
    return train_loss_sum / k, test_loss_sum / k

k = 5
epochs = 200
verbose_epoch = 195
learning_rate = 6
weight_decay = 0.001

#train_loss, test_loss = k_fold_cross_valid(k, epochs, verbose_epoch, X_train, y_train, learning_rate, weight_decay)
#print("%d-fold validation: Avg train loss: %f, Avg test loss: %f"%(k, train_loss, test_loss))


def learn(epochs, verbos_epoch, X_train, y_train, test, learning_rate, weight_decay):
    net = get_net()
    train(net, X_train, y_train, None, None, epochs, verbose_epoch, learning_rate, weight_decay)

    preds = net(X_test).asnumpy()
    test['SalePrice'] = pd.Series(preds.reshape(1, -1)[0])
    submission = pd.concat([test['Id'], test['SalePrice']], axis=1)
    submission.to_csv('submission.csv', index=False)

learn(epochs, verbose_epoch, X_train, y_train, test, learning_rate, weight_decay)

