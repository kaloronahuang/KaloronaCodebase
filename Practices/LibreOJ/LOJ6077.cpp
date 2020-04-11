// LOJ6077.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, mod = 1e9 + 7;

int n, k, fac[MAX_N], fac_inv[MAX_N], inv[MAX_N], dp[500][MAX_N];

int binomial(int n_, int k_) { return 1LL * fac[n_] * fac_inv[k_] % mod * fac_inv[n_ - k_] % mod; }

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = fac[0] = 1; i <= n + k; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    inv[0] = inv[1] = fac_inv[0] = fac_inv[1] = 1;
    for (int i = 2; i <= n + k; i++)
        inv[i] = 1LL * (mod - mod / i) * inv[mod % i] % mod, fac_inv[i] = 1LL * fac_inv[i - 1] * inv[i] % mod;
    dp[0][0] = 1;
    int ans = 0;
    for (int i = 1; i < 450; i++)
        for (int j = i; j <= k; j++)
            dp[i][j] = (0LL + dp[i - 1][j - i] + dp[i][j - i] + ((j > n) ? (mod - dp[i - 1][j - n - 1]) : 0)) % mod;
    for (int i = 0; i <= k; i++)
    {
        int pans = 0;
        for (int j = 0, opt = 1; j < 450; j++, opt = mod - opt)
            pans = (0LL + pans + 1LL * opt * dp[j][i] % mod) % mod;
        ans = (0LL + ans + 1LL * pans * binomial(n + k - 1 - i, n - 1) % mod) % mod;
    }
    printf("%d\n", ans);
    return 0;
}