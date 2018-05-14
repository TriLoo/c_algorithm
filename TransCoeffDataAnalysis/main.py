import numpy as np
import scipy.optimize

L = 1.
# Define object function
def objectFunction(theta, datas, labels):
    '''
    The object function to fit a curve.

    :param theta: including all parameters: a, b, c, Is1, Is2, Is3
    :param datas: input training datas
    :param labels: input training labels
    :return: the total errors between training labels and predictions
    '''

    a, b, c, Is1, Is2, Is3 = theta
    global L

    totalError = 0.0
    for x, y in zip(datas, labels):
        item1 = a / (1. + x / Is1)
        item2 = b * x / (1. + (x / Is2)**2)
        item3 = c * x**2 / (1. + (x / Is3)**3)
        error = y - np.exp(-(item1 + item2 + item3) * L)
        totalError = totalError + error

    return totalError

def otherOptimization(func, theta0, datas, labels):
    result = scipy.optimize.minimize(func, thetah0, (datas, labels), method='Powell')
    return result

a = [1, 2, 3, 4]
b = [9, 8, 7, 6]

for x, y in zip(a, b):
    print('a = ', x)
    print('b = ', y)
