// string.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, mod = 998244353;

int n, p, ans, f[MAX_N], g[MAX_N];

void fileIO()
{
    freopen("string.in", "r", stdin);
    freopen("string.out", "w", stdout);
}

int fpow(int bas, int tim)
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
    // fileIO();
    scanf("%d%d", &n, &p);
    for (int i = 1; i <= n; i++)
        if (i & 1)
            g[i] = f[i] = 1LL * i * fpow(p, (i >> 1) + 1) % mod;
        else
            g[i] = f[i] = (0LL + 1LL * (i >> 1) * fpow(p, i >> 1) % mod + 1LL * (i >> 1) * fpow(p, (i >> 1) + 1) % mod) % mod;
    for (int step = 1; step <= n; step++)
        for (int j = step << 1; j <= n; j += step)
            g[j] = (0LL + g[j] + mod - 1LL * (j / step) * g[step] % mod) % mod;
    int ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j+=i)
            ans = (0LL + ans + g[i]) % mod;
    printf("%d\n", ans);
    return 0;
}