// POJ2018.cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 100200;
double seq[maxn], sum[maxn], tmp[maxn];
int N, F;
bool check(double mid)
{
    sum[0] = 0;
    for (int i = 1; i <= N; i++)
        tmp[i] = seq[i] - mid, sum[i] = sum[i - 1] + tmp[i];
    double min_val = 1e10;
    double ans = -1e10;
    for (int i = F; i <= N; i++)
        min_val = min(min_val, sum[i - F]), ans = max(ans, sum[i] - min_val);
    if (ans >= 0)
        return true;
    return false;
}

int main()
{
    scanf("%d%d", &N, &F);
    for (int i = 1; i <= N; i++)
        scanf("%lf", &seq[i]);
    double l = -1e6, r = 1e6, eps = 1e-6;
    while (r - l > eps)
    {
        double mid = (l + r) / 2;
        if (check(mid))
            l = mid;
        else
            r = mid;
    }
    cout << (int)(r * 1000) << endl;
    return 0;
}