import mxnet as mx
from mxnet import gluon
from mxnet import autograd
from mxnet import ndarray as nd
import os
import utils
from mxnet import image
import numpy as np

import matplotlib as mpl
mpl.rcParams['figure.dpi'] = 120
from matplotlib import pyplot as plt

# Define the model
class AlexNet(gluon.nn.Block):
    def __init__(self, **kwargs):
        super(AlexNet, self).__init__(**kwargs)
        self.net = gluon.nn.Sequential()
        with self.name_scope():
            self.net.add(gluon.nn.Conv2D(channels=96, kernel_size=(11, 11), strides=4, activation='relu'),   # first convolution layer
                         gluon.nn.MaxPool2D(pool_size=(3, 3), strides=2),
                         # TODO: Add Local Response Normalization
                         # Second convolution layer
                         gluon.nn.Conv2D(channels=256, kernel_size=(5, 5), padding=2, activation='relu'),
                         gluon.nn.MaxPool2D(pool_size=(3, 3), strides=2),
                         # TODO: Add Local Response Normalization here
                         # Third Convolution layer
                         gluon.nn.Conv2D(channels=384, kernel_size=(3, 3), padding=2, activation='relu'),
                         # Fourth Convoluton layer
                         gluon.nn.Conv2D(channels=384, kernel_size=(3, 3), padding=2, activation='relu'),
                         # Fifth Convolution layer
                         gluon.nn.Conv2D(channels=256, kernel_size=(3, 3), padding=2, activation='relu'),
                         gluon.nn.MaxPool2D(pool_size=(3, 3), strides=2),
                         # Flatten, First Full Connection layer
                         gluon.nn.Flatten(),
                         gluon.nn.Dense(units=4096, activation='relu'),
                         gluon.nn.Dropout(rate=0.5),
                         # Second Full Connection layer
                         gluon.nn.Dense(units=4096, activation='relu'),
                         gluon.nn.Dropout(rate=0.5),
                         # The output layer
                         gluon.nn.Dense(units=10, activation='relu')    # Only 10 classes
                         )

    def forward(self, x):
        return nd.softmax(self.net(x))

# Get the data
def transformTest(data, label, augs_):
    data = data.astype('float32')
    for aug in augs_:
        data = aug(data)
    data = nd.transpose(data, (2, 0, 1))
    return data, nd.array([label]).asscalar().astype('float32')

#batch_size = 128     # set 8 to test
batch_size = 1     # set 8 to test
augs = [
    image.HorizontalFlipAug(.5),
    image.CenterCropAug((224, 224))
    #image.RandomCropAug((224, 224))
]
train_set = gluon.data.vision.ImageFolderDataset(root='~/.mxnet/datasets/oxford102/train_datas', transform=lambda X, y: transformTest(X, y, augs))
test_set = gluon.data.vision.ImageFolderDataset(root='~/.mxnet/datasets/oxford102/test_datas', transform=lambda X, y: transformTest(X, y, augs))
# define loss function
softLoss = gluon.loss.SoftmaxCrossEntropyLoss()


# define Train Function
def train(train_set, test_set, net, batch_size, lr, mom, epochs, period):
    assert period >= batch_size and period % batch_size == 0
    net.collect_params().initialize(mx.init.Normal(sigma=0.01), force_reinit=True)
    # momenta approach
    trainer = gluon.Trainer(net.collect_params(), 'sgd', {'learning_rate':lr, 'momentum':mom})

    total_loss = [100]

    train_data = gluon.data.DataLoader(train_set, batch_size=batch_size, shuffle=True)
    test_data = gluon.data.DataLoader(test_set, batch_size=batch_size)

    for epoch in range(epochs):
        for batch_i, (data, label) in enumerate(train_data):
            with autograd.record():
                output = net(data)
                loss = softLoss(output, label)
            loss.backward()
            trainer.step(batch_size)

            if batch_i * batch_size % period == 0:
                total_loss.append(np.mean(softLoss(net(data), label).asnumpy()))
        print('Batch Size: %d, Learning rate: %f, Epoch: %d, loss %.4e'%(batch_size, lr, epoch, total_loss[-1]))

    x_axis = np.linspace(0, epochs, len(total_loss), endpoint=True)
    plt.semilogx(x_axis, total_loss)
    plt.xlabel('epoch')
    plt.ylabel('loss')
    plt.show()

# define training target
net = AlexNet()

# Load parameters  OR  Train
if os.path.exists('./AlexNet.params'):
    #net.collect_params().load('AlexNet.params', allow_missing=False)
    net.collect_params().load('AlexNet.params', ctx=mx.cpu(0), allow_missing=False)
    print("Weight file exists.")
else:
    # net.initialize(init=mx.init.Xavier())
    # Train
    train(train_set, test_set, net, batch_size=batch_size, lr=0.01, mom=0.9, epochs=2, period=1)
    # save parameters
    net.collect_params().save('AlexNet.params')

# Test
test_augs = [
    image.CenterCropAug((224, 224))
]
def testClassify(net, fname):
    with open(fname, 'rb') as f:
        img = image.imdecode(f.read())
    data, _ = transformTest(img, -1, test_augs)
    plt.imshow(data.transpose((1, 2, 0)).asnumpy() / 255)
    data = data.expand_dims(axis=0)
    out = net(data)
    out = nd.SoftmaxActivation(out)
    pred = int(nd.argmax(out, axis=1).asscalar())
    prob = out[0][pred].asscalar()
    label = train_set.synsets
    return ('With prob=%f, %s'%(prob, label[pred]))

print(testClassify(net, '/home/smher/.mxnet/datasets/oxford102/test_datas/0_data/image_06736.jpg'))

'''
# Prepare the trainning data
def apply_aug_lists(img, augs):
    for aug in augs:
        img = aug(img)
    return img

def get_transform(augs):
    def transform(data, label):
        data = data.astype('float32')
        if augs is not None:
            data = nd.stack(*[apply_aug_lists(d, augs) for d in data])
        data = nd.transpose(data, (0, 3, 1, 2))
        return data, label.astype('float32')
    return transform

#train_set = gluon.data.vision.ImageFolderDataset(root='~/.mxnet/datasets/oxford102/train_datas', transform=get_transform(augs))
#train_set = gluon.data.vision.ImageFolderDataset(root='../data/hotdog/train', transform=get_transform(augs))


for X,label in train_data:
    X = X.transpose((0, 2, 3, 1)).clip(0, 255)/255
    #X = X.transpose((0, 2, 3, 1)).clip(0, 255)/255
    utils.show_images(X, 8, 16)
    print(label)
    break
'''
