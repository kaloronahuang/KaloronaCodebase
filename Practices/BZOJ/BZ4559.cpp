// BZ4559.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110, mod = 1e9 + 7;

int n, m, K, ui[MAX_N], ri[MAX_N], fac[MAX_N], fac_inv[MAX_N], inv[MAX_N], dp[MAX_N][MAX_N];

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

int binomial(int n_, int k_) { return k_ > n_ ? 0 : 1LL * fac[n_] * fac_inv[k_] % mod * fac_inv[n_ - k_] % mod; }

void preprocess()
{
    for (int i = fac[0] = 1; i < MAX_N; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    inv[0] = inv[1] = 1;
    for (int i = 2; i < MAX_N; i++)
        inv[i] = 1LL * (mod - mod / i) * inv[mod % i] % mod;
    for (int i = fac_inv[0] = 1; i < MAX_N; i++)
        fac_inv[i] = 1LL * fac_inv[i - 1] * inv[i] % mod;
}

int polyY[MAX_N];

int interpolation(int x, int *yi)
{
    if (x <= n + 1)
        return yi[x];
    int ret = 0;
    for (int i = 1; i <= n + 1; i++)
    {
        int pans = 1;
        for (int j = 1; j <= n + 1; j++)
            if (i != j)
                pans = 1LL * pans * ((0LL + x + mod - j) % mod) % mod * fpow((0LL + i + mod - j) % mod, mod - 2) % mod;
        ret = (0LL + ret + 1LL * yi[i] * pans % mod) % mod;
    }
    return ret;
}

int main()
{
    scanf("%d%d%d", &n, &m, &K), preprocess();
    for (int i = 1; i <= m; i++)
        scanf("%d", &ui[i]);
    for (int i = 1; i <= m; i++)
        scanf("%d", &ri[i]);
    dp[0][n - 1] = 1;
    for (int i = 1; i <= m; i++)
        for (int k = 0; k <= n - 1; k++)
            for (int j = 0; j <= min(n - ri[i], k); j++)
                if (n - 1 - k >= n - ri[i] - j)
                    dp[i][j] = (0LL + dp[i][j] + 1LL * dp[i - 1][k] * binomial(k, j) % mod * binomial(n - k - 1, n - ri[i] - j) % mod) % mod;
    int ans = dp[m][K];
    cerr << ans << endl;
    for (int i = 1; i <= m; i++)
    {
        for (int x = 1; x <= n + 1; x++)
        {
            polyY[x] = 0;
            for (int j = 1; j <= x; j++)
                polyY[x] = (0LL + polyY[x] + 1LL * fpow(j, n - ri[i]) * fpow(ui[i] - j, ri[i] - 1) % mod) % mod;
        }
        ans = 1LL * ans * interpolation(ui[i], polyY) % mod;
    }
    printf("%d\n", ans);
    return 0;
}