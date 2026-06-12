#include <stdio.h>
#include <iostream>
#include <cmath>
using namespace std;
// 这修改 n
#define N 4

// 差值节点的 x 和 y，注意下标从 0 开始的
const vector<double> X = {0, 0.5, 1.0, 1.5, 2.0};
const vector<double> Y = {-1.0, 0.5, 2.0, 1.5, 0.0};

const double h = X[1] - X[0];

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

vector<vector<double>> cul_cs()
{
    vector<vector<double>> c(N + 1, vector<double> (N + 1, NAN));
    for(int i = 0; i <= N; i ++) c[i][0] = Y[i];
    for(int j = 1; j <= N; j ++)
    {
        for(int i = j; i <= N; i ++) c[i][j] = (c[i][j - 1] - c[i - 1][j - 1]) / (X[i] - X[i - 1]);
    }
    return c;
}

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

double insert_ahead(double t)
{
    vector<vector<double>> qc(N + 1, vector<double>(N + 1, 0));
    for(int i = 0; i <= N; i ++) qc[i][0] = Y[i];
    for(int j = 1; j <= N; j ++)
    {
        for(int i = 0; i <= N - j; i ++) qc[i][j] = qc[i + 1][j - 1] - qc[i][j - 1];
    }

    double res = Y[0], fac = 1.;
    for(int i = 1; i <= N; i ++)
    {
        fac *= i;
        double tmp = 1;
        for(int j = 0; j < i; j ++) tmp *= (t - j);
        res += qc[0][i] * tmp / fac;
    }
    return res;
}

double inster_last(double t)
{
    vector<vector<double>> hc(N + 1, vector<double>(N + 1, 0));
    for(int i = 0; i <= N; i ++) hc[i][0] = Y[i];
    for(int j = 1; j <= N; j ++)
    {
        for(int i = j; i <= N; i ++) hc[i][j] = hc[i][j - 1] - hc[i - 1][j - 1];
    }

    double res = Y[N], fac = 1.;
    for(int i = 1; i <= N; i ++)
    {
        fac *= i;
        double tmp = 1;
        for(int j = 0; j < i; j ++) tmp *= t + j;
        res += hc[N][i] * tmp / fac;
    }
    return res;
}

int main()
{
    double x = 1.7;
    cout << Lagrange(x) << endl;
    cout << Newton(x) << endl;
    double t = (x - X[0]) / h;
    cout << insert_ahead(t) << endl;
    t = (x - X[N]) / h;
    cout << inster_last(t) << endl;
    return 0;
}