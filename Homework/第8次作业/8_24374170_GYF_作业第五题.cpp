#include <bits/stdc++.h>
using namespace std;

double C[9][9] = {
    // n=0（未使用，占位）
    {0.0},
    // n=1 梯形公式
    {1.0/2, 1.0/2},
    // n=2 辛普森公式
    {1.0/6, 2.0/3, 1.0/6},
    // n=3 牛顿3/8公式
    {1.0/8, 3.0/8, 3.0/8, 1.0/8},
    // n=4 4阶科茨公式
    {7.0/90, 16.0/45, 2.0/15, 16.0/45, 7.0/90},
    // n=5 5阶科茨公式
    {19.0/288, 25.0/96, 25.0/144, 25.0/144, 25.0/96, 19.0/288},
    // n=6 6阶科茨公式
    {41.0/840, 9.0/35, 9.0/280, 34.0/105, 9.0/280, 9.0/35, 41.0/840},
    // n=7 7阶科茨公式
    {751.0/17280, 3577.0/17280, 1323.0/17280, 2989.0/17280, 
     2989.0/17280, 1323.0/17280, 3577.0/17280, 751.0/17280},
    // n=8 8阶科茨公式（注意负系数）
    {989.0/28350, 5888.0/28350, -928.0/28350, 10496.0/28350, -4540.0/28350,
     10496.0/28350, -928.0/28350, 5888.0/28350, 989.0/28350}
};
/* 节点数为n对应数组第n - 1行 */
double ans[5];

double f(double);
double result(double, double, int);

int main()
{
	int i;
	double rans = exp(0) - exp(-1);
	cout << "the true answer is " << rans << endl;
	for(i = 2; i <= 3; i++)
	{
		ans[i] = result(0, 1, i);
		cout << "the result of n = " << i << ": " << fixed << setprecision(15) << ans[i] << endl;
		cout << "erf: " << (ans[i] - rans) * 100 / rans << "%%" << endl;
	}
	
	return 0;
}

double f(double x)
{
	return exp(-x);
}

double result(double a, double b, int n)
{
	n--;
	double dh = (b - a) / n, x = a, ans = 0;
	for(int j = 0; j <= n; j++)
	{
		ans += C[n][j] * f(x);
		x += dh;
	}
	ans *= (b - a);
	return ans;
}