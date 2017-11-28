import numpy as np
import matplotlib.pyplot as plt

def f(x):
    return x * np.cos(x * np.pi)

x = np.arange(-1.0, 2.0, 0.1)

fig = plt.figure()
subplt = fig.add_subplot(111)
subplt.annotate('local minimum', xy=(-0.3, -0.2), xytext=(-0.8, -1.0), arrowprops=dict(facecolor='black', shrink=0.01))
subplt.annotate('global minimum', xy=(1.1, -0.9), xytext=(0.7, 0.1), arrowprops=dict(facecolor='black', shrink=0.05))

plt.plot(x, f(x))
plt.xlabel('x')
plt.ylabel('f(x)')
plt.show()


from mpl_toolkits.mplot3d import Axes3D
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
x, y = np.mgrid[-1:1:31j, -1:1:31j]
z = x ** 2 - y ** 2
ax.plot_surface(x, y, z, **{'rstride':1, 'cstride':1, 'cmap': 'Greens_r'});
ax.plot([0], [0], [0], 'ro')
ax.view_init(azim=-60, elev=20)
plt.xticks([-1, -0.5, 0, 0.5, 1])
plt.yticks([-1, -0.5, 0, 0.5, 1])
ax.set_zticks([-1, -0.5, 0, 0.5, 1])
plt.xlabel('x')
plt.ylabel('y')
plt.show()
