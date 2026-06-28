from math import exp
import numpy as np
EPS = 1e-9 # 在这里修改你的误差限
X0 = [1, 1, 1] # 在这里定义你的初始值

# 定义f(x) 注意下标从 0 开始
def f(x):
    return [3 * x[0] - x[1] ** 3 - 0.5 * x[0] * x[2],
            x[0] ** 2 - (x[1] + 0.1) ** 2 + 2 * x[2] + 0.9,
            exp(-x[0]) + 1 / x[1] + 1.5 * x[2] + 2]

# 求解 Jacobi 矩阵 注意下标从 0 开始
def df(x):
    return [[3 - 0.5 * x[2], -3 * x[1] ** 2, -0.5 * x[0]],
            [2 * x[0], -2 * (x[1] + 0.1), 2],
            [-exp(-x[0]), -1 / x[1] ** 2, 1.5]]


def newton_solve(f, df, x0, eps=EPS, max_iter=100, verbose=True):
    print("牛顿法解非线形方程组")
    xk = np.array(x0, dtype=float)
    if verbose:
        print(f"x0 = {xk}")

    for k in range(1, max_iter + 1):
        Fk = np.array(f(xk))
        Jk = np.array(df(xk))

        dx = np.linalg.solve(Jk, -Fk)
        xk = xk + dx

        e = sum([abs(i) for i in f(xk)])
        if verbose:
            print(f"x{k} = {np.round(xk, 8)}, e = {e:.6e}")

        if e < eps:
            break
    else:
        print(f"警告: 超过最大迭代次数 {max_iter}，可能不收敛")

    if verbose:
        print(f"\nx = {xk}")
        print(f"F(x) = {np.array(f(xk))}")

    return xk, k


def steepest_descent_solve(f, df, x0, eps=EPS, max_iter=100, verbose=True):
    print("最速下降法解非线性方程组")
    xk = np.array(x0, dtype=float)
    if verbose:
        print(f"x0 = {xk}")

    for k in range(1, max_iter + 1):
        Fk = np.array(f(xk))
        Jk = np.array(df(xk))

        p = -Fk.T @ Jk                       # p = -F(x)ᵀ ∇F(x)
        phi = 0.5 * Fk @ Fk                  # φ(x) = (1/2) F(x)ᵀ F(x)
        alpha = phi / (p.T @ p)              # α_k = φ / (pᵀp)
        xk = xk + alpha * p                  # x_{k+1} = x_k + α_k p

        e = sum([abs(i) for i in f(xk)])
        if verbose:
            print(f"x{k} = {np.round(xk, 8)}, e = {e:.6e}")

        if e < eps:
            break
    else:
        print(f"警告: 超过最大迭代次数 {max_iter}，可能不收敛")

    if verbose:
        print(f"\nx = {xk}")
        print(f"F(x) = {np.array(f(xk))}")

    return xk, k


if __name__ == '__main__':
    x0 = X0
    print("=" * 50)
    sol, iters = newton_solve(f, df, x0, eps=EPS, max_iter=100)
    print("=" * 50)
    sol, iters = steepest_descent_solve(f, df, x0, eps=EPS, max_iter=100)