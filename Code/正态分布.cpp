#include <iostream>
#include <stdio.h>
#include <cmath>
using namespace std;
#define STEP 1e-6 // 步长

double phi(double x)
{
    return exp(-x * x / 2.) / (sqrt(2 * M_PI));
}

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

double alpha(double x)
{
    const double step = STEP, tar = 1. - x;
    if(tar == 0.5) return 0;
    else if(tar > 0.5) 
    {
        double p = 0.5, res = 0;
        while(p < tar)
        {
            res += step;
            p += phi(res) * step;
            // cout << res << " " <<  p << endl;
        }
        return res;
    }
    else
    {
        double p = 0.5, res = 0;
        while(p > tar)
        {
            res -= step;
            p -= phi(res) * step;
            // cout << res << " " <<  p << endl;
        }
        return res;
    }
}

int main()
{
    double x = alpha(0.05);
    cout << x << endl;
    cout << Phi(x) << endl;
    return 0;
}