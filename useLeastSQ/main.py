'''
Least square method
'''
import numpy as np
from scipy.optimize import leastsq

import matplotlib.pyplot as plt

# samples
Xi = np.array([0, 1, 2, 3, -1, -2, -3])
Yi = np.array([-1.21, 1.9, 3.2, 10.3, 2.2, 3.71, 8.7])

def func(p, x):
    a, b, c = p
    return a*x**2 + b*x + c

def error(p, x, y, s):
    print (s)
    return func(p, x) - y    # Caution: input is a list, and return a list too

# test data
# initial P values
p0 = [5, 2, 10]
s = 'Test the number of iteration'

Para = leastsq(error, p0, args=(Xi, Yi, s))

a, b, c = Para[0]

print("a = ", a, '\n', "b - ", b, '\n', 'c = ', c)

plt.figure(figsize=(8, 6))
plt.scatter(Xi, Yi, color='red', label='Sample Point', linewidth=3)
x = np.linspace(-5, 5, 1000)
y = a*x**2 + b * x + c
plt.plot(x, y, color='orange', label='Fitting Curve', linewidth=2)
plt.legend()
plt.show()
