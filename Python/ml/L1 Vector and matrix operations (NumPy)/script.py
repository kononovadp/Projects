import math
from matplotlib import cm
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import matplotlib.pyplot as plt
from sklearn.preprocessing import PolynomialFeatures
def sigmoid(x):
    return 1/(1+np.exp(-x))
x = np.linspace(-5, 5, 100)
y = sigmoid(x)
plt.plot(x, y)
plt.ylim(0, 1)
plt.savefig("Task 1 sigmoid.jpg")
plt.close()
#################### TASK 2 ####################
v=np.array([0,1])# ([i for i in range(100)])
alpha=np.pi/2
M=np.array([[np.cos(alpha),-np.sin(alpha)],[np.sin(alpha),np.cos(alpha)]])
vs=[v]
for i in range(100):
	v=np.dot(v,M)*0.99
	vs.append(v)
vs=np.array(vs)
plt.figure(figsize=(6,6))
plt.xlim(-1,1)
plt.ylim(-1,1)
plt.plot(*vs.T)
plt.savefig("Task 2.jpg")
plt.close()
#################### TASK 3 ####################
x = np.linspace(-2.2, 2.2, 1000)[:, np.newaxis]
print(f'Shape of x: {x.shape}')
X_p = np.zeros((1000,6))
for i in range(1000):	
	for j in range(6):
		X_p[i][j]=pow(x[i],j)
X_p = np.concatenate((pow(x,0),pow(x,1),pow(x,2),pow(x,3),pow(x,4),pow(x,5)),1)
for i in range(len(x)):
	for j in range(6):
		X_p[i][j]=pow(x[i],j)
print(f"Shape of X_p {X_p.shape}")
assert X_p.shape == (1000, 6)
plt.plot(
    x[..., 0],
    X_p @ np.array([[0, 4, 0, -5, 0, 1]]).T
)
plt.savefig("Task 3.jpg")
plt.close()
#################### TASK 4 ####################
def rastrigin2d(x, y):
	# return [20+(x**2-10*np.cos(2*math.pi*x))+(y**2-10*np.cos(2*math.pi*y)) for i in x]
	return 20+(x**2-10*np.cos(2*np.pi*x))+(y**2-10*np.cos(2*np.pi*y))
x = np.linspace(-5, 5, 500)
y = np.linspace(-5, 5, 500)
x,y=np.meshgrid(x,y)
plt.figure(figsize=(10, 10))
plt.contourf(rastrigin2d(x,y), levels=10)
plt.savefig("Task 4 Rastrigin 2d.jpg")
plt.close()
def rastrigin3d(*X, **kwargs):
    A = kwargs.get('A', 10)
    return A + sum([(x**2 - A * np.cos(2 * math.pi * x)) for x in X])
X = np.linspace(-4, 4, 500)    
Y = np.linspace(-4, 4, 500)
X, Y = np.meshgrid(X, Y)
Z = rastrigin3d(X, Y)
fig = plt.figure(figsize=(10, 10))
ax = fig.add_subplot(projection = '3d')
ax.plot_surface(X, Y, Z, rstride=1, cstride=1, cmap=cm.plasma, linewidth=0, antialiased=False)
plt.savefig('Task 4 Rastrigin 3d.jpg')