// AGC002F.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2020, mod = 1e9 + 7;

int n, k, dp[MAX_N][MAX_N], fac[MAX_N * MAX_N], fac_inv[MAX_N * MAX_N], fac_tot;

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

int comb(int upper, int lower) { return 1LL * fac[upper] * fac_inv[lower] % mod * fac_inv[upper - lower] % mod; }

int main()
{
    scanf("%d%d", &n, &k), fac_tot = n * k;
    if (k == 1)
        puts("1"), exit(0);
    for (int i = fac[0] = 1; i <= fac_tot; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    fac_inv[fac_tot] = quick_pow(fac[fac_tot], mod - 2);
    for (int i = fac_tot - 1; i >= 0; i--)
        fac_inv[i] = 1LL * fac_inv[i + 1] * (i + 1) % mod;
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= i; j++)
        {
            dp[i][j] = dp[i - 1][j];
            if (j > 0)
                dp[i][j] = (1LL * dp[i][j] + 1LL * comb(n - i + (n - j + 1) * (k - 1) - 1, k - 2) * dp[i][j - 1] % mod * (n - j + 1) % mod) % mod;
        }
    printf("%d\n", dp[n][n]);
    return 0;
}