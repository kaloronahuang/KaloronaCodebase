// CF1172C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 2000, MAX_M = 3030, mod = 998244353;

int n, m, ai[MAX_N], wi[MAX_N], sum[3], inv[MAX_M << 1], f[MAX_M][MAX_M], g[MAX_M][MAX_M];

int quick_pow(int bas, int tim)
{
    int ret = 1;
    while (tim)
    {
        if (tim & 1)
            ret = 1LL * ret * bas % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ret;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &wi[i]), sum[ai[i]] += wi[i], sum[2] += wi[i];
    for (int i = m; i >= 0; i--)
    {
        f[i][m - i] = g[i][m - i] = 1;
        for (int j = min(m - i - 1, sum[0]); j >= 0; j--)
        {
            f[i][j] = (1LL * (sum[1] + i + 1) * f[i + 1][j] % mod + 1LL * (sum[0] - j) * f[i][j + 1] % mod) % mod * quick_pow(sum[2] + i - j, mod - 2) % mod;
            g[i][j] = (1LL * (sum[1] + i) * g[i + 1][j] % mod + 1LL * (sum[0] - j - 1) * g[i][j + 1] % mod) % mod * quick_pow(sum[2] + i - j, mod - 2) % mod;
        }
    }
    for (int i = 1; i <= n; i++)
        printf("%lld\n", (1LL * wi[i] * (ai[i] ? f[0][0] : g[0][0]) % mod));
    return 0;
}