// FOJ4786.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, mod = 998244353, MAX_E = 5e5 + 200;

int dp[MAX_N], n, col[MAX_N], fac[MAX_E], fac_inv[MAX_E];

int quick_pow(int bas, int tim)
{
    int ans = 1;
    bas %= mod;
    while (tim)
    {
        if (tim & 1)
            ans = 1LL * ans * bas % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ans;
}

int main()
{
    for (int i = fac[0] = 1; i < MAX_E; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    fac_inv[MAX_E - 1] = quick_pow(fac[MAX_E - 1], mod - 2);
    for (int i = MAX_E - 2; i >= 0; i--)
        fac_inv[i] = 1LL * fac_inv[i + 1] * (i + 1) % mod;

    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &col[i]);

    dp[1] = 1;
    for (int i = 2, prefix = col[1]; i <= n; prefix += col[i++])
        dp[i] = 1LL * dp[i - 1] * fac[prefix + col[i] - 1] % mod * fac_inv[prefix] % mod * fac_inv[col[i] - 1] % mod;
    printf("%d", dp[n]);
    return 0;
}
