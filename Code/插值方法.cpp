#include <stdio.h>
#include <iostream>
#include <cmath>
using namespace std;
#define N 4

const vector<double> X = {0, 0.5, 1.0, 1.5, 2.0};
const vector<double> Y = {-1.0, 0.5, 2.0, 1.5, 0.0};

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

int main()
{
    cout << Lagrange(1.7) << endl;
    cout << Newton(1.7) << endl;
    return 0;
}