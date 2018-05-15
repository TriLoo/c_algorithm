import numpy as np
import itertools
import scipy.optimize
import utils
import matplotlib.pyplot as plt
from matplotlib.legend_handler import  HandlerLine2D

#A = 1.
L = 1e-5
# Define object function
def objectFunction(theta, datas, labels):
    '''
    The object function to fit a curve.

    :param theta: including all parameters: a, b, c, Is1, Is2, Is3
    :param datas: input training datas
    :param labels: input training labels
    :return: the total errors between training labels and predictions
    '''

    A, a, b, c, Is1, Is2, Is3 = theta
    global L

    totalError = 0.0
    #for x, y in zip(datas, labels):     # OR
    for x, y in itertools.zip_longest(datas, labels):
        item1 = a / (1. + x / Is1)
        item2 = b * x / (1. + (x / Is2)**2)
        item3 = c * x**2 / (1. + (x / Is3)**3)
        #error = np.abs(y - A * np.exp(-(item1 + item2 + item3) * L))
        error = (y - A * np.exp(-(item1 + item2 + item3) * L))**2
        totalError = totalError + error

    return totalError

def predict(theta, x):
    A, a, b, c, Is1, Is2, Is3 = theta
    global L

    item1 = a / (1. + x / Is1)
    item2 = b * x / (1. + (x / Is2)**2)
    item3 = c * x**2 / (1. + (x / Is3)**3)

    y = A * np.exp(-(item1 + item2 + item3) * L)
    return y


def otherOptimization(func, theta0, datas, labels):
    result = scipy.optimize.minimize(func, theta0, (datas, labels), method='Powell', options={'maxiter':100})
    #result = scipy.optimize.minimize(func, theta0, (datas, labels), method='Nelder-Mead')
    return result

datas, labels = utils.readData('datas.xlsx')

datas = np.array(datas)
labels = np.array(labels)

#theta0 = (.2, 200., 3., 1., .01, 20., 500.0)
theta0 = (.2, 100000., 100., 1., 0.01, 20., 500.0)    # Try so many initializations, total bad

result = otherOptimization(objectFunction, theta0, datas, labels)
print(result)

minVal = np.min(datas)
maxVal = np.max(datas)

theta = [a for a in result.x]
print(theta)

testDatas = np.array(np.linspace(minVal, maxVal, 2000))
testOut = [predict(theta, x) for x in testDatas]

fig = plt.figure(1)
plotf, =  plt.plot(datas, labels, label='Origin')
plotfi, =  plt.plot(testDatas, testOut, label='Predicted')

plt.legend(handler_map={plotf:HandlerLine2D(numpoints=4)})
plt.scatter(datas.reshape((-1)), labels, marker='x', color='g')

plt.show()

