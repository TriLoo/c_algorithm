import matplotlib.pyplot as plt
from mxnet import image
import mxnet as mx

img = image.imdecode(open('./Barbara.jpg', 'rb').read())
plt.imshow(img.asnumpy())
plt.show()

from mxnet import nd
import utils

def apply(img, aug, n = 3):
    X = [aug(img.astype('float32')) for _ in range(n * n)]
    Y = nd.stack(*X).clip(0, 255) / 255
    utils.show_images(Y, n, n, figsize=(256, 256))

# 水平翻转
aug = image.HorizontalFlipAug(.5)
apply(img, aug)

# 随机裁剪一个块, 256 * 256
aug = image.RandomCropAug([256, 256])
apply(img, aug)


# 颜色变化
# 随机将亮度增加或减少一个量
aug = image.BrightnessJitterAug(.5)
apply(img, aug)

# 随机色调变化
aug = image.HueJitterAug(.5)
apply(img, aug)

def apply_aug_list(img, augs):
    for aug in augs:
        img = aug(img)
    return img

train_augs = [
    image.HorizontalFlipAug(.5),
    image.RandomCropAug((28, 28))
]

test_augs = [
    image.CenterCropAug((28, 28))
]

from mxnet import gluon
def get_transform(augs):
    def transform(data, label):
        data = data.astype('float32')
        if augs is not None:
            data = nd.stack(*[apply_aug_list(d, augs) for d in data])
        data = nd.transpose(data, (0, 3, 1, 2))
        return data, label.astype('float32')
    return transform

def get_data(batch_size, train_augs, test_augs=None):
    cifar10_train = gluon.data.vision.CIFAR10(train=True, transform=get_transform(train_augs))
    cifar10_test = gluon.data.vision.CIFAR10(train=False, transform=get_transform(test_augs))
    train_data = utils.DataLoader(cifar10_train, batch_size, shuffle=True)
    test_data = utils.DataLoader(cifar10_test, batch_size, shuffle=True)
    return (train_data, test_data)


train_data, _ = get_data(36, train_augs)
for imgs, _ in train_data:
    break
utils.show_images(imgs.transpose((0, 2, 3, 1)), 6, 6)

from mxnet import init
def train(train_augs, test_augs, learning_rate = .1):
    batch_size = 128
    num_epochs = 10
    ctx = mx.cpu()
    loss = gluon.loss.SoftmaxCrossEntropyLoss()
    train_data, test_data = get_data(batch_size, train_augs, test_augs)
    net = utils.resnet18(10)
    net.initialize(init=init.Xavier())
    net.hybridize()
    trainer = gluon.Trainer(net.collect_params(), 'sgd', {'learning_rate':learning_rate})

    utils.train(train_data, test_data, net, loss, trainer, mx.cpu(), num_epochs)

train(train_augs, test_augs)

