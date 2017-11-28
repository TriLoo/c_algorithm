with open("./timemachine.txt") as f:
    time_machine = f.read()
print(time_machine[0:500])

time_machine = time_machine.lower().replace('\n', ' ').replace('\r', ' ')

character_list = list(set(time_machine))
character_dict = dict([(char, i) for i, char in enumerate(character_list)])

vocab_size = len(character_dict)
#print('character = \n', character_dict)
#print('size of vocab = ', vocab_size)

time_numerical = [character_dict[char] for char in time_machine]
#sample = time_numerical[:40]

#print('length of characters = ', len(time_numerical))
#print('sample = ', sample)

import random
from mxnet import nd

def data_iter(batch_size, seq_len):
    num_examples = (len(time_numerical) - 1) // seq_len
    num_batches =num_examples // batch_size
    idx = list(range(num_examples))

    random.shuffle(idx)
    def _data(pos):
        return time_numerical[pos:pos+seq_len]
    for i in range(num_batches):
        i = i * batch_size
        examples = idx[i:i+batch_size]
        data = nd.array([_data(j * seq_len) for j in examples])
        label = nd.array([_data(j * seq_len + 1) for j in examples])  # label is a shift backward characters list
        yield data, label

'''
for data, label in data_iter(batch_size=3, seq_len=8):
    print('data: ', data, '\n label: ', label)
    break
'''

def get_inputs(data):
    return [nd.one_hot(X, vocab_size) for X in data.T]
'''
for data, label in data_iter(batch_size=3, seq_len=8):
    inputs = get_inputs(data)
    #print('input shape = ', inputs)
    print('input shape = ', len(inputs))
    break
'''

import mxnet as mx
import utils

num_hidden = 256
weighted_scale = 0.1

# hidden layers
Wxh = nd.random_normal(shape=(vocab_size, num_hidden)) * weighted_scale
Whh = nd.random_normal(shape=(num_hidden, num_hidden)) * weighted_scale
bh = nd.zeros(shape=num_hidden)

# output layer
Why = nd.random_normal(shape=(num_hidden, vocab_size)) * weighted_scale
by = nd.zeros(vocab_size)

params = [Wxh, Whh,bh, Why, by]

for param in params:
    param.attach_grad()

# define a model
def rnn(inputs, H):
    # inputs: seq_len : batch_size * vocab_size矩阵, 因为data取了转置，在 data_iter中
    # outputs: seq_len batch_size * vocab_size matrix
    # H : batch_size * num_hidden matrix, hidden layer of last time
    outputs = []
    #print('input shape = ', inputs[0].shape)
    #print('hidden layer shape = ', H.shape)
    for X in inputs:
        H = nd.tanh(nd.dot(X, Wxh) + nd.dot(H, Whh) + bh)
        Y = nd.dot(H, Why) + by
        outputs.append(Y)
    return (outputs, H)
'''
for data, label in data_iter(batch_size=3, seq_len=8):
    state = nd.zeros(shape = (data.shape[0], num_hidden))
    outputs, state_new = rnn(get_inputs(data), state)
    print('output length = ', len(outputs)) # should be seq_len
    print('output[0] shape: ', outputs[0].shape) # should be batch_size * vocab_size
    print('state shape: ', state_new.shape)      # should be batch_size * num_hidden
    break
'''

# predict model
def predict(prefix, num_chars):
    # 预测以prefix开始，接下来的num_chars个字符
    prefix = prefix.lower()
    state = nd.zeros(shape=(1, num_hidden))
    output = [character_dict[prefix[0]]]
    for i in range(num_chars + len(prefix)):
        X = nd.array([output[-1]])
        Y, state = rnn(get_inputs(X), state)
        if i < len(prefix) - 1:
            next_inputs = character_dict[prefix[i+1]]
        else:
            next_inputs = int(Y[0].argmax(axis=1).asscalar())
        output.append(next_inputs)
    return ''.join([character_list[i] for i in output])


# 梯度裁剪
def grad_clipping(prarams, theta):
    norm = nd.array([0.0])
    for p in params:
        norm += nd.sum(p.grad ** 2)
    norm = nd.sqrt(norm).asscalar()
    if norm > theta:
        for p in params:
            p.grad[:] *= theta / norm

# 训练模型
from mxnet import autograd
from mxnet import gluon
from math import exp

epochs = 200
seq_len = 35
learning_rate = .1
batch_size = 32

softmax_cross_entropy = gluon.loss.SoftmaxCrossEntropyLoss()

for e in range(epochs + 1):
    train_loss, num_examples = 0, 0
    state = nd.zeros(shape=(batch_size, num_hidden))
    for data, label in data_iter(batch_size, seq_len):
        with autograd.record():
            outputs, state = rnn(get_inputs(data), state)
            label = label.T.reshape((-1,))
            outputs = nd.concat(*outputs, dim=0)
            loss = softmax_cross_entropy(outputs, label)
        loss.backward()

        grad_clipping(params, 5)
        utils.SGD(params, learning_rate)
        train_loss += nd.mean(loss).asscalar()
        num_examples += loss.size

    if e % 20 ==0:
        print('num_examples = ', num_examples)
        print('Epoch %d. PPL %f'%(e, exp(train_loss / num_examples)))
        print(' - :', predict('the time ma', 100))
        print(' - :', predict('The Medical Man ros, came to the lamp,', 100), '\n')

