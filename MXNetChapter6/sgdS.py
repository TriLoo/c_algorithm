def sgd(params, lr, batch_size):
    for param in params:
        param[:] = param - lr * param.grad / batch_size