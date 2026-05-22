## 知识点总结

快速索引
- [知识点总结](#知识点总结)
- [基本定义](#基本定义)
  - [数字特征](#数字特征)
  - [常用分布](#常用分布)
    - [正态分布（Gauss分布）⭐️⭐️⭐️](#正态分布gauss分布️️️)

## 基本定义
### 数字特征
**期望**
- 离散型随机变量

$$E(x)=\sum_i^{\infty}x_ip(x_i)$$

- 连续型随机变量

$$E(X)=\int_{-\infty}^{+\infty}xf(x)\mathrm{d}x$$

**方差**

定义：$D(x)=E\left\lbrace\left[x-E(X)\right]^2\right\rbrace=E\left(X^2\right)-\left[E(x)\right]^2$

计算期望即可

### 常用分布
#### 正态分布（Gauss分布）⭐️⭐️⭐️
$$f(x)=\dfrac{1}{\sqrt{2\pi}}e^{-\dfrac{(x-\mu)^2}{2\sigma^2}}$$

**标准正态分布**

$x\sim N(0,1)$ 为标准正态分布

密度函数 $\phi(x)=\frac{1}{\sqrt{2\pi}}e^{-\frac{x^2}{2}}$

分布函数 $\Phi(x)=\frac{1}{\sqrt{2\pi}}\int_{-\infty}^x e^{-\frac{x^2}{2}} \mathrm{d}x$

代码 [正态分布.cpp](../../Code/正态分布.cpp) 中给出了利用梯形公式计算标准正态分布密度函数和分布函数的实现方法。

`phi` 函数直接计算 $\phi(x)=\frac{1}{\sqrt{2\pi}}e^{-\frac{x^2}{2}}$

```cpp
double phi(double x)
{
    return exp(-x * x / 2.) / (sqrt(2 * M_PI));
}
```

`Phi` 函数利用梯形公式计算了 $\Phi(x)=\frac{1}{\sqrt{2\pi}}\int_{-\infty}^x e^{-\frac{x^2}{2}} \mathrm{d}x$ ，由于负无穷在计算机中无法到达，故将公式作出调整 
$$\begin{aligned}
  \Phi(x) & =\frac{1}{\sqrt{2\pi}}\int_{-\infty}^x e^{-\frac{x^2}{2}} \mathrm{d}x \\
  & =\frac{1}{\sqrt{2\pi}}\int_{-\infty}^0 e^{-\frac{x^2}{2}} \mathrm{d}x + \frac{1}{\sqrt{2\pi}}\int_0^x e^{-\frac{x^2}{2}} \mathrm{d}x \\
  & =0.5 + \frac{1}{\sqrt{2\pi}}\int_0^x e^{-\frac{x^2}{2}} \mathrm{d}x
\end{aligned}$$

实际是从 $0$ 开始积分
```cpp
double Phi(double x)
{
    const double step = STEP;
    if(x == 0.) return 0.5;
    else if(x > 0)
    {
        double res = 0.5;
        for(int i = 0; i < x / step; i ++) res += phi((i + 0.5) * step) * step;
        return res;
    }
    else
    {
        double res = 0.5;
        for(int i = 0; i < -x / step; i ++) res -= phi(-(i + 0.5) * step) * step;
        return res;
    }
}
```