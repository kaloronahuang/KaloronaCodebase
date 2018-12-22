// P3648.cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <deque>
#define ll long long
using namespace std;
const int MX_N = 100100;
ll n, k, arr[MX_N], prefixSum[MX_N], dp[2][MX_N], to[220][MX_N], q[MX_N << 1];
int now = 0, prv = 1;
ll pow2(ll num)
{
    return num * num;
}
long double slope(int j, int k)
{
    if (prefixSum[j] == prefixSum[k])
        return -1e18;
    long double res = (1.0 * (dp[prv][k] - pow2(prefixSum[k]) - dp[prv][j] + pow2(prefixSum[j]))) / (1.0 * (prefixSum[j] - prefixSum[k]));
    return res;
}
int main()
{
    scanf("%lld%lld", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &arr[i]), prefixSum[i] = prefixSum[i - 1] + arr[i];
    for (int i = 1; i <= k; i++)
    {
        int h = 0, t = 0;
        for (int j = 1; j <= n; j++)
        {
            while (h < t && slope(q[h], q[h + 1]) <= prefixSum[j])
                h++;
            ll ft = q[h];
            dp[now][j] = dp[prv][ft] + prefixSum[ft] * (prefixSum[j] - prefixSum[ft]);
            to[i][j] = ft;
            while (h < t && slope(q[t], j) <= slope(q[t - 1], q[t]))
                t--;
            q[++t] = j;
        }
        now ^= 1, prv ^= 1;
    }
    printf("%lld\n", dp[prv][n]);
    int q = to[k][n], p = k;
    while (p)
        printf("%lld ", q), q = to[--p][q];
    return 0;
}