// P3195.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#define ll long long
using namespace std;
const int MX_N = 50100;
ll f[MX_N], n, L, number, dp[MX_N], q[MX_N];
double slope(ll k, ll j) { return (double)(dp[j] - dp[k] + (f[j] + L) * (f[j] + L) - (f[k] + L) * (f[k] + L)) / (2.0 * (f[j] - f[k])); }
int main()
{
    scanf("%lld%lld", &n, &L);
    L++;
    for (int i = 1; i <= n; i++)
        scanf("%lld", &number), f[i] = f[i - 1] + number + 1;
    int h = 0, t = 0;
    for (int i = 1; i <= n; i++)
    {
        while (h < t && slope(q[h], q[h + 1]) <= f[i])
            h++;
        int k = q[h];
        dp[i] = dp[k] + (f[i] - f[k] - L) * (f[i] - f[k] - L);
        while (h < t && slope(q[t], i) < slope(q[t - 1], q[t]))
            t--;
        q[++t] = i;
    }
    printf("%lld", dp[n]);
    return 0;
}