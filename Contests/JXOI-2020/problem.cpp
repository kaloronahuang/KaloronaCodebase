// problem.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2020;

int n, x, mod, m, ai[MAX_N], bi[MAX_N], stirling[MAX_N][MAX_N];

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
    scanf("%d%d%d%d", &n, &x, &mod, &m);
    for (int i = 0; i <= m; i++)
        scanf("%d", &ai[i]);
    stirling[0][0] = 1;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= m; j++)
            stirling[i][j] = (0LL + stirling[i - 1][j - 1] + 1LL * j * stirling[i - 1][j] % mod) % mod;
    for (int i = 0; i <= m; i++)
        for (int j = 0; j <= m; j++)
            bi[j] = (0LL + bi[j] + 1LL * stirling[i][j] * ai[i] % mod) % mod;
    int ans = 0, fac = 1;
    for (int i = 0; i <= m; i++)
        ans = (0LL + ans + 1LL * bi[i] * fpow(x, i) % mod * fpow(1 + x, n - i) % mod * fac % mod) % mod, fac = 1LL * fac * (n - i) % mod;
    printf("%d\n", ans);
    return 0;
}