from numpy import *
import numpy as np
import random

a = np.arange(15).reshape(3, 5)

print(a)
print(a.shape)
print(a.ndim)
print(a.size)
print(a.dtype)
print(a.itemsize)
print(a.data)      # print the address of 'a'

# Create Array

a = array([1, 2, 3])     # create from list
print(a.dtype)

b = array([[1, 2], [3, 4]], dtype=complex)
print(b)

c = linspace(0, 2, 9)     # spilt 0-2 into 9 parts
print(c)

d = c ** 2
print(d)

e = sin(c)
print(e)

print(a < 10)

A = array([[1, 1],
           [0, 1]])
B = array([[2, 0],
           [3, 4]])

print(A * B)
print(A.dot(B))

#a = random.random((2, 3))
print(a.sum())
print(a.min())
print(a.max())

def f(x, y):
    return 10 * x + y

b = fromfunction(f, (5, 4), dtype=int)
print(b[-1])

for row in b:
    print(row)
for val in b.flat:
    print(val)

print(b.ravel())
print(b.transpose())

a = 2
b = array([[1, 2],
           [3, 4]])

print(a+b)
