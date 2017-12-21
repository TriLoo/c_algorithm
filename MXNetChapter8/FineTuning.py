import mxnet as mx
from mxnet import autograd
from mxnet import gluon

import zipfile

data_dir = '../data/'
fname = 'hotdog.zip'
'''
with zipfile.ZipFile(data_dir+fname, 'r') as f:
    f.extractall(data_dir)
'''

from mxnet import nd
from mxnet import image

train_augs = [
    image.HorizontalFlipAug(.5),
    image.RandomCropAug((224, 224))
]

test_augs = [
    image.CenterCropAug((224, 224))
]

def transform(data, label, augs):
    data = data.astype('float32')
    for aug in augs:
        data = aug(data)
    data = nd.transpose(data, (2, 0, 1))
    return data, nd.array([label]).asscalar().astype('float32')

import utils
train_imgs = gluon.data.vision.ImageFolderDataset(data_dir + '/hotdog/train', transform=lambda X, y : transform(X, y, train_augs))
test_imgs = gluon.data.vision.ImageFolderDataset(data_dir + '/hotdog/test', transform=lambda X, y:transform(X, y, test_augs))

data = gluon.data.DataLoader(train_imgs, 32, shuffle=True)
for X, _ in data:
    X = X.transpose((0, 2, 3, 1)).clip(0, 255) / 255
    utils.show_images(X, 4, 8)
    break

from mxnet.gluon.model_zoo import vision as models
#pretrained_net = models.resnet18_v2(pretrained = True)
pretrained_net = models.resnet18_v2()
pretrained_net.load_params('resnet18_v2-8aacf80f.params', ctx=mx.cpu())

print(pretrained_net.classifier)
print(pretrained_net.features)

from mxnet import init
finetune_net = models.resnet18_v2(classes=2)
finetune_net.features = pretrained_net.features
finetune_net.classifier.initialize(init.Xavier())

#finetune_net.collect_params().save('test.params')

def train(net, ctx, batch_size=64, epochs=3, learning_rate=.01, wd = .001):
    train_data = gluon.data.DataLoader(train_imgs, batch_size, shuffle=True)
    test_data = gluon.data.DataLoader(test_imgs, batch_size)

    net.collect_params().reset_ctx(ctx)
    net.hybridize()
    loss = gluon.loss.SoftmaxCrossEntropyLoss()

    trainer = gluon.Trainer(net.collect_params(), 'sgd', {'learning_rate':learning_rate, 'wd':wd})
    utils.train(train_data, test_data, net, loss, trainer, ctx, epochs)

ctx = mx.cpu(0)
#train(finetune_net, ctx)

finetune_net.collect_params().load('finetune-hotdog.params', ctx=mx.cpu())
try:
    finetune_net.collect_params().save('finetune-hotdogT.params')
except ValueError:
    print('Parameters save failed ...')
else:
    print('Parameters have been saved in "finetune-hotdogT.params" ')

# load trained parameters
# finetune_net.collect_params().load('finetune-hotdog.params')

import matplotlib.pyplot as plt

def classify_hotdog(net, fname):
    with open(fname, 'rb') as f:
        img = image.imdecode(f.read())
    data, _ = transform(img, -1, test_augs)
    plt.imshow(data.transpose((1, 2, 0)).asnumpy() / 255)
    data = data.expand_dims(axis=0)
    out = net(data.as_in_context(ctx))
    out = nd.SoftmaxActivation(out)
    pred = int(nd.argmax(out, axis = 1).asscalar())
    prob = out[0][pred].asscalar
    label = train_imgs.synsets
    #print('With pred = ', pred, label[pred])
    print('With prob = ', prob, label[pred])
    #print('With prob = %f'%(prob))
    #print('With prob = %f, %s'%(prob, label[pred]))
    #return 'With prob = %f, %s'%(prob, label[pred])

classify_hotdog(finetune_net, '../data/hotdog/test/hotdog/1000.png')
classify_hotdog(finetune_net, '../data/hotdog/test/not-hotdog/1000.png')


