#include <bits/stdc++.h>
#define h 0.2
#define eps 1e-6
#define X0 1
#define Y0 1
using namespace std;
int N = (int)(0.4 / h) + 1;
vector<double> X(N);
vector<double> re(N);
vector<double> ans(N);
double f(double, double);
double y(double);

void Std();
void El();
void El2();
void TS();
void RK2();
void RK4();

int main()
{
	X[0] = X0;
	for(int i = 1; i < N; i++)
	{
		X[i] = X[i - 1] + h;
	}
	re[0] = Y0;
	ofstream file("Results3.csv");
	file << "x" << ",";
	for(int i = 0; i < N; i++)
		file << X[i] << ",";
	file << "\n";
//	Std();
//	file << "std" << ",";
//	for(int i = 0; i < N; i++)
//		file << ans[i] << ",";
//	file << "\n";
//	El();
//	file << "El" << ",";
//	for(int i = 0; i < N; i++)
//		file << re[i] << ",";
//	file << "\n";
	El2();
	file << "El2" << ",";
	for(int i = 0; i < N; i++)
		file << re[i] << ",";
	file << "\n";
//	TS();
//	file << "TS" << ",";
//	for(int i = 0; i < N; i++)
//		file << re[i] << ",";
//	file << "\n";
//	RK2();
//	file << "RK2" << ",";
//	for(int i = 0; i < N; i++)
//		file << re[i] << ",";
//	file << "\n";
//	RK4();
//	file << "RK4" << ",";
//	for(int i = 0; i < N; i++)
//		file << re[i] << ",";
//	file << "\n";
	return 0;
}
double f(double x, double y)
{
	return -y - y * y * sin(x);
}
//double y(double x)
//{
//	return x * x - x + 1 - exp(-x);
//}
//void Std()
//{
//	for(int i = 0; i < N; i++)
//	{
//		ans[i] = y(X[i]);
//	}
//	return;
//}
void El()
{
	for(int i = 1; i < N; i++)
	{
		re[i] = re[i - 1] + h * f(X[i - 1], re[i - 1]);
	}
	return;
}
void El2()
{
	for(int i = 1; i < N; i++)
	{
		double tmp = re[i - 1] + h * f(X[i - 1], re[i - 1]);
		re[i] = re[i - 1] + (h / 2) * (f(X[i - 1], re[i - 1]) + f(X[i], tmp));
	}
	return;
}
void TS()
{
	for(int i = 1; i < N; i++)
	{
		double tmp = re[i - 1] + h * f(X[i - 1], re[i - 1]);
		double tmp1 = -100;
		while(fabs(tmp1 - tmp) > eps)
		{
			tmp1 = tmp;
			tmp = re[i - 1] + (h / 2) * (f(X[i - 1], re[i - 1]) + f(X[i], tmp1)); 
		}
		re[i] = tmp;
	}
	return;
}
void RK2()
{
	double k1, k2;
	for(int i = 1; i < N; i++)
	{
		k1 = h * f(X[i - 1], re[i - 1]);
		k2 = h * f(X[i - 1] + 2.0 * h / 3, re[i - 1] + 2.0 * k1 / 3);
		re[i] = re[i - 1] + (k1 + k2 * 3) / 4;
	}
	return;
}
void RK4()
{
	double k1, k2, k3, k4;
	for(int i = 1; i < N; i++)
	{
		k1 = h * f(X[i - 1], re[i - 1]);
		k2 = h * f(X[i - 1] + 0.5 * h, re[i - 1] + 0.5 * k1);
		k3 = h * f(X[i - 1] + 0.5 * h, re[i - 1] + 0.5 * k2);
		k4 = h * f(X[i - 1] + h, re[i - 1] + k3);
		re[i] = re[i - 1] + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
	}
	return;
}