#include <iostream>
#include <vector>
using namespace std;
#define EPS 1e-4
#define alpha 0.618
#define MAXN 50
#define A 0.
#define B 1.

double func(double x) {return 8 * x * x * x - 2 * x * x - 7 * x + 3;}

double gsm(double (*f)(double), double a, double b)
{
    vector<double> lam = {a + (1 - alpha) * (b - a), a}, mu = {a + alpha * (b - a), b};
    int cnt = 0;
    while(b - a > EPS)
    {
        int k = cnt % 2, kk = (cnt + 1) % 2;
        if(f(lam[k]) > f(mu[k]))
        {
            a = lam[k], lam[kk] = mu[k];
            mu[kk] = a + alpha * (b - a);
        }
        else
        {
            b = mu[k], mu[kk] = lam[k];
            lam[kk] = a + (1 - alpha) * (b - a);
        }
        cnt += 1;
        cout <<cnt << " a=" << a << " b=" << b << endl;
    }
    return a + alpha * (b - a);
}

double fibonacci(double (*f)(double), double a, double b)
{
    vector<double> fib(50);
    fib[0] = 1, fib[1] = 1;
    for(int i = 2; i < MAXN; i ++) fib[i] = fib[i - 1] + fib[i - 2];

    double lam, mu;
    int cnt = 1, n;
    for(n = 1; fib[n] <= (b - a) / EPS; n ++){}
    cout << n << endl;
    while (b - a > EPS && cnt < n)
    {
        lam = a + fib[n - cnt - 1] / fib[n - cnt + 1] * (b - a);
        mu = a + fib[n - cnt] / fib[n - cnt + 1] * (b - a);
        if(f(lam) > f(mu)) a = lam;
        else b = mu;
        cout <<cnt << " a=" << a << " b=" << b << endl;
        cnt += 1;
    }
    return a + alpha * (b - a);
}

int main()
{
    cout << "黄金分割法\n" << gsm(func, A, B) << endl;
    cout << "Fibonacci 法\n" << fibonacci(func, A, B) << endl;
    return 0;
}