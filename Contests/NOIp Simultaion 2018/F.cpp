// F.cpp
#include <iostream>
#include <iomanip>
using namespace std;
int n;
double F[10020000];
double E[1002000];
double last = 1;

double *GET(int idx)
{
    if (idx < 10020000)
        return &F[idx];
    return &E[idx - 10020000];
}

int main()
{
    cin >> n;
    double ans = 0;
    F[1] = 0;
    F[2] = 2;
    last = F[2];
    for (int i = 3; i <= n; i++)
    {
        double sum = last + i;
        *GET(i) = sum / (i - 1);
        last += *GET(i);
    }
    cout << fixed << setprecision(5) << *GET(n);
    return 0;
}