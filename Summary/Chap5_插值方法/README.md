本章内容对应的[PPT1](../../PPT/第5章%20插值方法与计算实验-第一次课.pdf) , [PPT2](../../PPT/第5章%20插值方法与计算实验-第二次课-带计算实验.pdf)

## 知识点总结

快速索引
- [知识点总结](#知识点总结)
- [Lagrange插值](#lagrange插值)
  - [差值公式](#差值公式)
  - [差值余项](#差值余项)
- [Newton插值](#newton插值)
  - [差商](#差商)
  - [Newton法插值](#newton法插值)
- [等距节点插值](#等距节点插值)
  - [差分](#差分)

先弄清楚插值法是干什么

对 $y = f(x)$ 已知在 $a \leq x_0 < x_1 \dots < x_n \leq b$ 上的值为 $y_0, y_1,\dots,y_n$。插值法就是要找函数 $\phi(x)$ 来逼近 $f(x)$ 。要求 $\phi(x_i)=y_i , (i=0,1,2,\dots,n)$成立。

## Lagrange插值
### 差值公式
多项式来拟合函数，目标

$$P_n(x)=l_0(x)y_0+l_1(x)y_1+\dots+l_n(x)y_n=\sum_{k=0}^nl_k(x)y_k$$

其中 $l_i(x),(i=0,1,2,\dots,n)$ 应满足如下良好性质

$$l_i(x_j)=\delta_{ij}=\begin{cases}
    1 & i = j \\
    0 & i \neq j
\end{cases} (i,j = 0,1,2,\dots,n)$$

故我们找到的 Lagrange 差值公式为

$$P_n(x)=\sum_{i=0}^n\left(\prod_{j=0,j\neq i}^n\dfrac{x-x_j}{x_i-x_j}\right)y_i$$

代码[插值方法.cpp](../../Code/插值方法.cpp)中的 `Lagrange` 函数实现了 Lagrange 插值法。已知的插值节点定义为全局变量、输入 `double x` 为需要拟合的节点

```cpp
double Lagrange(double x)
{
    double res = 0;
    for(int i = 0; i <= N; i ++)
    {
        double tmp = Y[i];
        for(int j = 0; j <= N; j ++)
        {
            if(j == i) continue;
            tmp *= (x - X[j]) / (X[i] - X[j]);
        }
        res += tmp;
    }
    return res;
}
```

### 差值余项

直接记结论， $f(x)$ 的差值函数 $P_n(x)$ 在区间 $[a,b]$ 上的误差函数

$$R_n(x)=\dfrac{1}{(n+1)!}f^{(n=1)}(\xi)(x-x_0)(x-x_1)(x-x_2)\dots(x-x_n)$$

其中 $\xi\in[a,b]$ 且依赖于 $x$。

~~证明如下~~

对于固定的 $x$ 有

$$\begin{aligned}
    \phi(x) & = f(x)-P_n(x)-R_n(x)\\
    & =f(x)-P_n(x)-k(x)\prod_{i=0}^{n}(x-x_i)\\
    &=0
\end{aligned}$$

在 $[a,b]$ 上 $\phi(x)=0,\phi(x_i)=0(i=0,1,2,\dots,n)$ ， $\phi(x)$ 有 $n+2$ 个零点，则 $\phi^{(n+1)}(x)$ 在 $[a,b]$ 上至少有 $1$ 个零点 $\xi$ ，故

$$\phi^{(n+1)}(\xi)=f^{(n+1)}(\xi)-(n+1)!k(x)=0$$

$$k(x)=\dfrac{1}{(n+1)!}f^{(n=1)}(\xi)$$

最终得 

$$R_n(x)=\dfrac{1}{(n+1)!}f^{(n=1)}(\xi)(x-x_0)(x-x_1)(x-x_2)\dots(x-x_n)$$

## Newton插值

为了有承袭性我们取Newton差值多项式为

$$P_n(x)=a_0+a_1(x-x_0)+a_2(x-x_0)(x-x_1)+\dots+a_n(x-x_0)(x-x_1)\dots(x-x_{n-1})$$

即 

$$\begin{cases}
    p_n(x) = p_{n-1}(x)+a_n(x-x_0)(x-x_1)\dots(x-x_{n-1})\\
    p_n(x_i) = f(x_i)
\end{cases}$$

这样我们就相当于先找 $l_i(x)$ 再找其系数

### 差商
~~作者觉得这东西会用来算系数就行，没啥纠结的，定义什么的不重要~~

| $x_i$ | $f(x_i)$ | 0阶差商 | 1阶差商 | 2阶差商 | 3阶差商 | 4阶差商 |
|---|---|---|---|---|---|---|
| $x_0$ | $f[x_0] = y_0$ | $y_0$ |||||
| $x_1$ | $f[x_1]=y_1$ | $y_1$ | $f[x_1, x_0] = \frac{y_1-y_0}{x_1-x_0}$ ||||
| $x_2$ | $f[x_2]=y_2$ | $y_2$ | $f[x_2, x_1]=\frac{y_2-y_1}{x_2-x_1}$ | $f[x_2,x_0]=\frac{f[x_2,x_1]-f[x_1,x_0]}{x_2-x_0}$ |||
| $x_3$ | $f[x_3]=y_3$ | $y_3$ | $f[x_3,x_2]=\frac{y_3-y_2}{x_3-x_2}$ | $f[x_3,x_1]=\frac{f[x_3,x_3]-f[x_2,x_1]}{x_3-x_1}$ | $f[x_3,x_0]=\frac{f[x_3,x_1]-f[x_2,x_0]}{x_3-x_0}$ ||
| $x_4$ | $f[x_4]=y_4$ | $y_4$ | $f[x_3,x_2]=\frac{y_3-y_2}{x_3-x_2}$ | $f[x_4,x_2]=\frac{f[x_4,x_3]-f[x_3,x_2]}{x_4-x_2}$ | $f[x_4,x_1]=\frac{f[x_4,x_2]-f[x_3,x_1]}{x_4-x_1}$ | $f[x_4,x_0]=\frac{f[x_4,x_1]-f[x_3,x_0]}{x_4-x_0}$ |

代码[插值方法.cpp](../../Code/插值方法.cpp)中的 `cal_cs()` 函数实现了计算差商表的功能。其中的插值节点定义为全局变量，返回一个存有差商表的二维容器。

```cpp
vector<vector<double>> cul_cs()
{
    vector<vector<double>> c(N + 1, vector<double> (N + 1, NAN));
    for(int i = 0; i <= N; i ++)
    {
        for(int j = i; j <= N; j ++)
        {
            if(i == 0) c[i][j] = Y[j];
            else c[i][j] = (c[i - 1][j] - c[i - 1][j - 1]) / (X[i] - X[i - j]);
        }
    }
    return c;
}
```

### Newton法插值
如上递归计算即可，并且可以得到 Newton 法的系数即为上表对角线上的系数

$$a_i = f[x_0,x_1,\dots,x_i]\enspace(i=0,1,\dots,n)$$

而[插值方法.cpp](../../Code/插值方法.cpp)中的 `newton()` 函数则实现了Newton插值法，输入 `double x` 为需要拟合的节点。

```cpp
double Newton(double x)
{
    vector<vector<double>> c = cul_cs();
    double res = 0;
    for(int i = 0; i <= N; i ++)
    {
        double tmp = c[i][i];
        for(int j = 0; j < i; j ++) tmp *= (x - X[j]);
        res += tmp;
    }
    return res;
}
```

## 等距节点插值
Newton法的特例， $x_k=x_0+kh,(k \in \N)$ ，可据此改进Newton插值。

### 差分
定义：
- 向前差分：$\Delta y_k=y_{k+1}-y_k$ 为 $x_k$ 一阶向前差分，再次基础上可以递推出 $\Delta^m y_k=\Delta^{m-1} y_{k+1}-\Delta^{m-1} y_k$ 为 $x_k$ 的 $m$ 阶向前差分。
- 向后差分：$\nabla y_k=y_k-y_{k-1}$ 为 $x_k$ 的一阶向后差分，在此基础上可以递推出 $\nabla^m y_k=\nabla^{m-1}y_k-\nabla^{m-1}y_{k-1}$ 为 $x_k$ 的 $m$ 阶向后差分。

查分表应该能帮助更好的理解，实际编程我们也是维护一个差分表。

向前差分表
| $x_i$ | $y_i$ | $1$阶差分 | $2$阶差分 | $3$阶差分 | $4$阶差分 |
|---|---|---|---|---|---|
| $x_0$ | $y_0$ | $\Delta y_0=y1-y0$ | $\Delta^2y_0 = \Delta y_1-\Delta y_0$ | $\Delta^3 y_0=\Delta^2y_1-\Delta^2y_0$ | $\Delta^4y_0=\Delta^3y_1-\Delta^3y_0$ |
| $x_1$ | $y_1$ | $\Delta y_1=y2-y1$ | $\Delta^2y_1 = \Delta y_2-\Delta y_1$ | $\Delta^3 y_1=\Delta^2y_2-\Delta^2y_1$ ||
| $x_2$ | $y_2$ | $\Delta y_2=y3-y2$ | $\Delta^2y_2 = \Delta y_3-\Delta y_2$ |||
| $x_3$ | $y_3$ | $\Delta y_3=y4-y3$ ||||
| $x_4$ | $y_4$ |||||

向后差分表
| $x_i$ | $y_i$ | $1$阶差分 | $2$阶差分 | $3$阶差分 | $4$阶差分 |
|---|---|---|---|---|---|
| $x_0$ | $y_0$ |||||
| $x_1$ | $y_1$ | $\nabla y_1=y_1-y_0$ ||||
| $x_2$ | $y_2$ | $\nabla y_2=y_2-y_1$ | $\nabla^2y_2=\nabla y_2-\nabla y_1$ |||
| $x_3$ | $y_3$ | $\nabla y_3=y_3-y_2$ | $\nabla^2y_3=\nabla y_3-\nabla y_2$ | $\nabla^3y_3=\nabla^2y_3-\nabla^2y_2$ ||
| $x_4$ | $y_4$ | $\nabla y_4=y_4-y_3$ | $\nabla^2y_4=\nabla y_4-\nabla y_3$ | $\nabla^3y_4=\nabla^2y_4-\nabla^2y_3$ | $\nabla^4y_4=\nabla^3y_4-\nabla^3y_3$ |