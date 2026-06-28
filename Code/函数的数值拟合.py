from math import log, cos, exp
import numpy as np

# 在这里修改已知的节点
X = [0.24, 0.65, 0.95, 1.24, 1.73, 2.01, 2.23, 2.52, 2.77, 2.99]
Y = [0.23, -0.26, -1.10, -0.45, 0.27, 0.10, -0.29, 0.24, 0.56, 1.00]

# 在这里设置基函数
Phi = [lambda x: log(x), lambda x: cos(x), lambda x: exp(x)]

m = len(X)
n = len(Phi)

Phi_vals = np.array([[phi(x) for x in X] for phi in Phi])

G = np.array([[np.dot(Phi_vals[k], Phi_vals[j]) for j in range(n)] for k in range(n)])
b = np.array([np.dot(Y, Phi_vals[k]) for k in range(n)])

a = np.linalg.solve(G, b)

print("G ="); print(G)
print("b ="); print(b)
print("a ="); print(a)
