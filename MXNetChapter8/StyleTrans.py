from mxnet import gluon
import mxnet as mx
from mxnet import autograd
from mxnet import nd
from mxnet import random
from mxnet import image
import utils

import random

import matplotlib as mpl
mpl.rcParams['figure.dpi'] = 120
import matplotlib.pyplot as plt

style_img = image.imread('../img/autumn_oak.jpg')
content_img = image.imread('../img/pine-tree.jpg')

plt.imshow(style_img.asnumpy())
plt.show()
plt.imshow(content_img.asnumpy())
plt.show()

rgb_mean = nd.array([0.485, 0.456, 0.406])
rgb_std = nd.array([0.229, 0.224, 0.225])

def preprocess(img, image_shape):
    img = image.imresize(img, *image_shape)
    img = (img.astype('float32') / 255 - rgb_mean) / rgb_std
    return (img.transpose((2, 0, 1)) * rgb_std + rgb_mean).clip(0, 1)

def postprocess(img, image_shape):
    img = img.resize(image_shape)
    return (img.transpose((1, 2, 0)) * rgb_std + rgb_mean).clip(0, 1)

from mxnet.gluon.model_zoo import vision as models
pretrained_net = models.vgg19(pretraind=True)
print(pretrained_net)

# 用每一个块中的第一个卷积层输出作为样式匹配层
# 用第四个块中的最后一个卷积层匹配内容
style_layers = [0, 5, 10, 19, 28]
content_layers = [25]

from mxnet.gluon import nn
def get_net(pretrained_net, content_layers, style_layers):
    net = nn.Sequential()
    for i in range(max(content_layers + style_layers) + 1):
        net.add(pretrained_net.features[i])
    return net

net = get_net(pretrained_net, content_layers, style_layers)

def extract_features(x, content_layers, style_layers):
    contents = []
    styles = []
    for i in range(len(net)):
        x = net(x)
        if i in style_layers:
            styles.append(x)
        if i in content_layers:
            contents.append(x)

    return contents, styles

# define loss function
# content loss function
def content_loss(yhat, y):
    return (yhat - y).square().mean()

# Style  loss function
def gram(x):
    c = x.shape[1]
    n = x.size / x.shape[1]
    y = x.reshape((c, int[n]))
    return nd.dot(y, y.T) / n

def style_loss(yhat, gram_y):
    return (gram(yhat) - gram_y).square().mean()

def tv_loss(yhat):
    return 0.5 * ((yhat[:, :, 1:, :] - yhat[:, :, :-1, :]).abs().mean() +
                  (yhat[:, :, :, 1:] - yhat[:, :, :, :-1]).abs().mean())

channels = [net[l].weight.shape[0] for l in style_layers]
style_weights = [1e4/n**2 for n in channels]
content_weights = [1]
tv_weight = 10

def sum_loss(loss, preds, truths, weights):
    return nd.add_n(*[w*loss(yhat, y) for w, yhat, y in zip(weights, preds, truths)])

ctx = mx.cpu(0)
# begin train
def get_contents(image_shape):
    content_x = preprocess(content_img, image_shape).copyto(ctx)
    content_y, _ = extract_features(content_x, content_layers, style_layers)
    return content_x, content_y

def get_styles(image_shape):
    style_x = preprocess(style_img, image_shape).copyto(ctx)
    _, style_y = extract_features(style_x, content_layers, style_layers)
    style_y = [gram(y) for y in style_y]
    return style_x, style_y

# define train function
from time import time
def train(x, max_epochs, lr, lr_decay_epoch=200):
    tic = time()
    for i in range(max_epochs):
        with autograd.record():
            content_py, style_py = extract_features(x, content_layers, style_layers)
            content_L = sum_loss(content_loss, content_py, content_y, content_weights)
            style_L = sum_loss(style_loss, style_py, style_y, style_weights)
            tv_L = tv_weight * tv_loss(x)
            loss = style_L + content_L + tv_L
        loss.backward()
        x.grad[:] /= x.grad.abs().mean() + 1e-8
        x[:] -= lr * x.grad
        nd.waitall()

        if i and i % 20 == 0:
            print('Epoch %d, content %.2f, style %.2f, TV %.2f, time %.1f sec'%(i, content_L.asscalar(),
                                                                                style_L.asscalar(),
                                                                                tv_L.asscalar(), time()-tic))
            tic = time()
        if i and i % lr_decay_epoch == 0:
            lr *= 0.1
            print('change lr to ', lr)

    plt.imshow(postprocess(x).asnumpy())
    plt.show()
    return x

image_shape = (300, 200)

net.collect_params().reset_ctx(ctx)
content_x, content_y = get_contents(image_shape)
style_x, style_y = get_styles(image_shape)

x = content_x.copyto(ctx)
x.attach_grad()

y = train(x, 500, 0.1)

plt.imsave('result.png', postprocess(y).asnumpy())

