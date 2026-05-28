## 知识点总结
本章内容对应的[PPT1](../../PPT/第7章%20数值积分-第一次课-2026.pdf),[PPT2](../../PPT/第7章%20数值积分-第二次课-2026.pdf)，对应的[代码](../../Code/数值积分方法.cpp)

快速索引
- [知识点总结](#知识点总结)
- [Newton-Cotes公式](#newton-cotes公式)
  - [代数精度](#代数精度)
  - [余项分析](#余项分析)
- [复化求积公式](#复化求积公式)
  - [复化梯形公式](#复化梯形公式)
  - [Romberg求积方法](#romberg求积方法)

数值积分要干什么
一句话——对函数取点然后按照积分定义以面积代积分。

**插值型求积公式**
以Lagrange差值多项式代替原函数进行积分

$$L_n(x)=\sum_{i=0}^nl_i(x)f(x_i)$$

于是有

$$\int_a^bf(x)\mathrm{d}x=\sum_{j=0}^n\left[\int_a^b\sum_{i=0}^nl_i(x)\mathrm{d}x\right]f(x_i)+\int_a^bR(x)\mathrm{d}x$$

取

$$f(x)\approx\sum_{j=0}^n\left[\int_a^b\sum_{i=0}^nl_i(x)\mathrm{d}x\right]f(x_i)=\sum_{i=0}^nA_if(x_i)$$

称为插值型求积公式

## Newton-Cotes公式
和Newton-Cotes法一样，取等距节点 $x_i=a+ih,h=\dfrac{b-a}{n},i=0,1,2,\dots,n$

则此时的求积系数为

$$A_i=\int_a^b\prod_{j=0,j\neq i}^n\dfrac{x-x_j}{x_i-x_j}\mathrm{d}x=h\left(\prod_{j=0,j\neq i}^n\dfrac{1}{k-j}\right)\int_a^b\prod_{j=0,j\neq i}^n(t-j)\mathrm{d}t=\dfrac{(b-a)(-1)^{n-j}}{nj!(n-j)!}\int_a^b\prod_{j=0,j\neq i}^n(t-j)\mathrm{d}t$$

定义Cotes系数

$$C_i^{(n)}=\dfrac{(-1)^{n-i}}{ni!(n-i)!}\int_a^b\prod_{j=0,j\neq i}^n(t-j)\mathrm{d}t,\enspace i=0,1,2,\dots,n$$

则求积公式变为

$$\int_a^bf(x)\mathrm{d}x\approx(b-a)\sum_{j=0}^nC_j^{(n)}f(x_j)$$

称为 $n$ 阶闭型Newton-Cotes求积公式

实际上我们常用的 $n$ 只有 $1,2,3,4$

|公式名称| $n$ | $C^{(n)}_0$ | $C^{(n)}_1$ | $C^{(n)}_2$ | $C^{(n)}_3$ | $C^{(n)}_4$ |
|---|---|---|---|---|---|---|
|梯形公式| $1$ | $\dfrac{1}{2}$ | $\dfrac{1}{2}$ ||||
|Simpson公式| $2$ | $\dfrac{1}{6}$ | $\dfrac{4}{6}$ | $\dfrac{1}{6}$ |||
|Newton公式| $3$ | $\dfrac{1}{8}$ | $\dfrac{3}{8}$ | $\dfrac{3}{8}$ | $\dfrac{1}{8}$ ||
|Cotes公式| $4$ | $\dfrac{7}{90}$ | $\dfrac{32}{90}$ | $\dfrac{12}{90}$ | $\dfrac{32}{90}$ | $\dfrac{7}{90}$ |

代码[数值积分方法.cpp](../../Code/数值积分方法.cpp)中已经给出了常用的Cotes系数（工程上 $n$ 一般不会超过 $8$ ），其中 `C[i][j]` 对应于 $C^{(i)}_j$

```cpp
const vector<vector<double>> C = {
    {},
    {1./2, 1./2},
    {1./6, 4./6, 1./6},
    {1./8, 3./8, 3./8, 1./8},
    {7./90, 32./90, 12./90, 32./90, 7./90},
    {19./288, 75./288, 50./288, 50./288, 75./288, 19./288},
    {41./840, 216./840, 27./840, 272./840, 27./840, 216./840, 41./840},
    {751./17280, 3577./17280, 1323./17280, 2989./17280, 2989./17280, 1323./17280, 3577./17280, 751./17280},
    {989./28350, 5888./28350, -928./28350, 10496./28350, -4540./28350, 10496./28350, -928./28350, 5888./28350, 989./28350}
};
```

此外，代码[数值积分方法.cpp](../../Code/数值积分方法.cpp)中的`Newton_Cotes()`函数还实现了一般情况下的Newton-Cotes公式，其中参数 `double n` 为Cotes公式的阶数。

```cpp
double Newton_Cotes(double (*f)(double), double a, double b, double n)
{
    double res = 0, h = (b - a) / n;
    for(int i = 0; i <= n; i ++) res += C[n][i] * f(a + i * h);
    res *= (b - a);
    return res;
}
```

### 代数精度
定义：对于一个数值求积公式，如果对于 $m$ 阶多项式精确成立；对于 $m+1$ 阶多项式不精确成立，则这个求积公式具有 $m$ 阶代数精度。

**Newton-Cotes公式代数精度定理：**

### 余项分析
由Lagrange差值公式的余项

$$R_n(x)=\dfrac{1}{(n+1)!}f^{(n+1)}(\xi)\prod_{i=0}^n(x-x_i)$$

可以得

$$R(f)=\dfrac{h^{n+2}}{(n+1)!}\int_0^nf^{(n+1)}(\xi)\left[\prod_{j=0}^n(t-j)\right]\mathrm{d}t$$

直接记结论
| $n=1$ 时（梯形公式）| $n=2$ 时（Simpson公式）| $n=4$ （Cotes公式）|
|---|---|---|
| $R(f)=-\dfrac{(b-a)^3}{12}f^{(2)}(\xi),\space\xi\in(a,b)$ | $R(f)=-\dfrac{(b-a)^5}{2880}f^{(4)}(\xi),\space\xi\in(a,b)$ | $R(f)=-\dfrac{(b-a)^7}{1935360}f^{(6)}(\xi),\space\xi\in(a,b)$ |

## 复化求积公式
**核心思想：** 细分区间减小误差

### 复化梯形公式
对每个小区间使用梯形公式，得

$$\int_a^bf(x)\mathrm{d}x\approx\dfrac{h}{2}\left[f(a)+2\sum_{i=1}^{n-1}f(x_i)+f(b)\right]=T_n,\enspace h = \dfrac{b - a}{n}$$

余项

$$R(f)=-\dfrac{h^2}{12}(b-a)f^{''}(\xi),\space\xi\in(a,b)$$

实际上，我们没有必要记这个公式，直接对每个区间使用Simpson公式和Cotes公式再求和，即可得到复化Simpson公式和复化Cotes公式。

### Romberg求积方法
从复化梯形公式可以看出来，当我们希望增加节点时，不必一个一个增加，直接在相邻两个节点中间增加一个新的节点即可。

即，插入前

$$T_n=\sum_{k=0}^{n-1}h\dfrac{f(x_k)+f(x_{k+1})}{2}$$

插入后

$$T_{2n}=\sum_{k=0}^{n-1}\dfrac{h}{2}\left[\dfrac{f(x_k)+f(x_{k+\frac{1}{2}})}{2}+\dfrac{f(x_{k+\frac{1}{2}})+f(x_{k+1})}{2}\right]=\dfrac{T_n}{2}+\dfrac{h}{2}\sum_{k=0}^{n-1}f(x_{k+\frac{1}{2}})$$

这样就可以通过迭代法计算复化梯形公式。代码[数值积分方法.cpp](../../Code/数值积分方法.cpp)中的`comp_ti`函数实现了复化梯形求积公式。

```cpp
double comp_ti(double (*f)(double), double a, double b)
{
    double Tk, Tkk, e = 1, h = b - a;
    Tk = h / 2 * (f(a) + f(b));
    int k = 2;
    while (e > EPS)
    {
        Tkk = Tk / 2;
        h /= 2;
        for(int i = 1; i <= k / 2; i ++) Tkk += h * f(a + (2 * i - 1) * h);
        e = fabs(Tkk - Tk);
        cout << "k=" <<  k << " Tk=" << Tk << " e=" << e << endl;
        Tk = Tkk;
        k *= 2;
    }
    return Tk;
}
```

然后再通过复化梯形积分 $\lbrace T_1, T_2, T_4, T_8, \dots\rbrace$ 计算复化Simpson积分

$$S_{n} = \dfrac{4}{4-1}T_{2n}-\dfrac{1}{4-1}T_n$$

再计算复化Cotes公式

$$C_{n} = \dfrac{4^2}{4^2-1}S_{2n}-\dfrac{1}{4^2-1}S_n$$

再计算复化Romberg公式

$$R_{n} = \dfrac{4^3}{4^3-1}C_{2n}-\dfrac{1}{4^3-1}C_n$$

这样做有什么用呢，当然会在比较少的迭代次数内达到比较高的精度。

代码[数值积分方法.cpp](../../Code/数值积分方法.cpp)中的`Romberg`函数实现了Romnerg方法，其中的参数 `int r` 为需要计算到的 $R_{2^r}$。
```cpp
void Romberg(double (*f)(double), double a, double b, int r)
{
    vector<vector<double>> tscr;
    int k = r + 5;
    tscr.push_back(vector<double> (k, 0));
    double h = b - a;
    tscr[0][1] = h / 2 * (f(a) + f(b));
    for(int i = 2; i < k; i ++)
    {
        h /= 2;
        tscr[0][i] = tscr[0][i - 1] / 2;
        for(int j = 1; j <= ((1 << (i - 1)) / 2); j ++) tscr[0][i] += h * f(a + h * (2 * j - 1));
    }

    for(int i = 1; i < 4; i ++)
    {
        k -= 1;
        tscr.push_back(vector<double> (k, 0));
        for(int j = 1; j < k; j ++) tscr[i][j] = (tscr[i - 1][j + 1] * pow(4, i) - tscr[i - 1][j]) / (pow(4, i) - 1);
    }

    vector<char> name = {'T', 'S', 'C', 'R'};
    for(int i = 0; i < 4; i ++)
    {
        int tmp = r + 3 - i;
        for(int j = 1; j <= tmp; j ++) printf("%c%d=%lf ", name[i], 1 << j, tscr[i][j]);
        cout << endl;
    }
    return;
}
```
