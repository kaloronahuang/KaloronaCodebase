// ARC093D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 17, MAX_M = 1 << MAX_N, mod = 1e9 + 7;

int n, m, ai[MAX_N], fac[MAX_M], fac_inv[MAX_M], dp[MAX_M];

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

int binomial(int n_, int k_) { return (n_ < k_) ? 0 : 1LL * fac[n_] * fac_inv[k_] % mod * fac_inv[n_ - k_] % mod; }

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
        scanf("%d", &ai[i]);
    for (int i = fac[0] = fac_inv[0] = 1; i < MAX_M; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    fac_inv[MAX_M - 1] = fpow(fac[MAX_M - 1], mod - 2);
    for (int i = MAX_M - 2; i >= 0; i--)
        fac_inv[i] = 1LL * fac_inv[i + 1] * (i + 1) % mod;
    sort(ai + 1, ai + 1 + m), dp[0] = 1, reverse(ai + 1, ai + 1 + m);
    for (int i = 1; i <= m; i++)
        for (int stat = (1 << n) - 1; stat >= 0; stat--)
            for (int j = 0; j < n; j++)
                if (stat & (1 << j))
                    dp[stat] = (0LL + dp[stat] + 1LL * dp[stat ^ (1 << j)] * binomial((1 << n) - ai[i] - (stat - (1 << j)), (1 << j) - 1) % mod * fac[1 << j] % mod) % mod;
    int ans = 0;
    for (int stat = 0; stat < (1 << n); stat++)
        if (__builtin_popcount(stat) & 1)
            ans = (0LL + ans + mod - 1LL * dp[stat] * fac[(1 << n) - stat - 1] % mod) % mod;
        else
            ans = (0LL + ans + 1LL * dp[stat] * fac[(1 << n) - stat - 1] % mod) % mod;
    printf("%lld\n", 1LL * ans * (1 << n) % mod);
    return 0;
}