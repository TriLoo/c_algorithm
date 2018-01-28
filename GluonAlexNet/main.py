import mxnet as mx
from mxnet import gluon
from mxnet import autograd
from mxnet import ndarray as nd
import os
import utils
from mxnet import image

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

# define Train Function
def train(train_data, test_data, net, batch_size, lr, mom, epochs, period):
    assert period >= batch_size and period % batch_size == 0
    net.collect_params().initialize(mx.init.Normal(sigma=0.01), force_reinit=True)

# define training target
net = AlexNet()

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

def transformTest(data, label, augs_):
    data = data.astype('float32')
    for aug in augs_:
        data = aug(data)
    data = nd.transpose(data, (2, 0, 1))
    return data, nd.array([label]).asscalar().astype('float32')

batch_size = 32     # set 8 to test
augs = [
    image.HorizontalFlipAug(.5),
    image.CenterCropAug((224, 224))
    #image.RandomCropAug((224, 224))
]

#train_set = gluon.data.vision.ImageFolderDataset(root='~/.mxnet/datasets/oxford102/train_datas', transform=get_transform(augs))
#train_set = gluon.data.vision.ImageFolderDataset(root='../data/hotdog/train', transform=get_transform(augs))
train_set = gluon.data.vision.ImageFolderDataset(root='~/.mxnet/datasets/oxford102/train_datas', transform=lambda X, y: transformTest(X, y, augs))
test_set = gluon.data.vision.ImageFolderDataset(root='~/.mxnet/datasets/oxford102/test_datas', transform=get_transform(augs))

train_data = gluon.data.DataLoader(train_set, batch_size=batch_size, shuffle=True)
test_data = gluon.data.DataLoader(test_set, batch_size=batch_size)

for X,label in train_data:
    X = X.transpose((0, 2, 3, 1)).clip(0, 255)/255
    #X = X.transpose((0, 2, 3, 1)).clip(0, 255)/255
    utils.show_images(X, 4, 8)
    print(label)
    break



# Load parameters  OR  Train
if os.path.exists('./AlexNet.params'):
    net.collect_params().load('AlexNet.params', allow_missing=False)
else:
    net.initialize(init=mx.init.Xavier())
    # Train
    # train()
    # save parameters
    # net.collect_params().save('AlexNet.params')

# Test

