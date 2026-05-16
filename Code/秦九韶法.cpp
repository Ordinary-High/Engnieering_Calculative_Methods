#include <iostream>
#include <cmath>
#include <ctime>
using namespace std;
// 在这里修改 x 和 n
#define x 1.001
#define n 9999
// 在这里修改系数 a 的计算方式(如果是给定的数组，则建立一个数组，然后返回对应的值即可)
int a(int i)
{
    return i + 1;
}

void normal()
{
    clock_t start = clock();
    double f = 0;
    for(int i = 0; i <= n; i ++)
    {
        double tmp = 1.;
        for(int j = 0; j < n - i; j ++) tmp *= x;
        f += a(i) * tmp;
    }
    clock_t end = clock();
    double time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0;
    cout << "Method 1: n = " << n << " x = " << x << " f = " << f << " t = " << time << "ms" << endl;
}

void qinJiuShao()
{
    clock_t start = clock();
    double f = a(0);
    for(int i = 1; i <= n; i ++) f = f * x + a(i);
    clock_t end = clock();
    double time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0;
    cout << "Method 2: n = " << n << " x = " << x << " f = " << f << " t = " << time << "ms" << endl;
}

void usePow()
{
    clock_t start = clock();
    double f = 0;
    for(int i = 0; i <= n; i ++) f += a(i) * pow(x, n - i);
    clock_t end = clock();
    double time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0;
    cout << "Method 3: n = " << n << " x = " << x << " f = " << f << " t = " << time << "ms" << endl;
}

int main()
{
    normal();
    qinJiuShao();
    usePow();
}