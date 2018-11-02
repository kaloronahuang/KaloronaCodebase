// P3802.cpp
#include <iostream>
#include <iomanip>

using namespace std;
const int maxn = 8;
int a[maxn];

int main()
{
    for (int i = 1; i <= 7; i++)
        cin >> a[i];
    double level7 = 1;
    double N = 0;
    for (int i = 1; i <= 7; i++)
        level7 *= i, N += a[i];
    double res = level7;
    for (int i = 1; i <= 6; i++)
        res *= (a[i]) / (N - i + 1);
    res *= a[7];
    cout << fixed << setprecision(3) << res;
    return 0;
}