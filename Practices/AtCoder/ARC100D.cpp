// ARC100D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 30010, MAX_K = 440, mod = 1e9 + 7;

int n, k, m, ai[MAX_N], inv[MAX_N], fac[MAX_N], fac_inv[MAX_N], last[MAX_K], f[MAX_N][MAX_K], g[MAX_N][MAX_K];

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
    scanf("%d%d%d", &n, &k, &m);
    for (int i = 1; i <= m; i++)
        scanf("%d", &ai[i]);
    for (int i = fac[0] = 1; i <= n; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    inv[0] = inv[1] = fac_inv[0] = fac_inv[1] = 1;
    for (int i = 2; i <= n; i++)
        inv[i] = 1LL * (mod - mod / i) * inv[mod % i] % mod, fac_inv[i] = 1LL * fac_inv[i - 1] * inv[i] % mod;
    int ans = 1LL * (n - m + 1) * fpow(k, n - m) % mod, max_seq = 0, curt = 0;
    for (int i = 1; i <= m; i++)
        max_seq = max(max_seq, curt = min(curt + 1, i - last[ai[i]])), last[ai[i]] = i;
    if (max_seq == k)
        printf("%d\n", ans), exit(0);
    else if (max_seq == m)
    {
        f[0][0] = 1;
        for (int i = 1; i <= n; i++)
        {
            int sum_f = 0, sum_g = 0;
            for (int j = k - 1; j >= 1; j--)
            {
                sum_f = (0LL + sum_f + f[i - 1][j]) % mod;
                sum_g = (0LL + sum_g + g[i - 1][j]) % mod;
                f[i][j] = (0LL + f[i][j] + 1LL * (k - j + 1) * f[i - 1][j - 1] % mod + sum_f) % mod;
                g[i][j] = (0LL + g[i][j] + 1LL * (k - j + 1) * g[i - 1][j - 1] % mod + sum_g) % mod;
                if (j >= m)
                    g[i][j] = (0LL + g[i][j] + f[i][j]) % mod;
            }
        }
        int minusPart = 0;
        for (int i = 1; i <= k; i++)
            minusPart = (0LL + minusPart + g[n][i]) % mod;
        minusPart = 1LL * minusPart * (k >= m ? fac[k - m] : 1) % mod * fac_inv[k] % mod;
        printf("%lld\n", (0LL + ans + mod - minusPart) % mod);
    }
    else
    {
        int lft = 0, rig = 0;
        memset(last, 0, sizeof(last));
        for (int i = 1; i <= m; i++)
            if (last[ai[i]] == 0)
                lft++, last[ai[i]] = 1;
            else
                break;
        memset(last, 0, sizeof(last));
        for (int i = m; i >= 1; i--)
            if (last[ai[i]] == 0)
                rig++, last[ai[i]] = 1;
            else
                break;
        f[0][lft] = g[0][rig] = 1;
        for (int i = 1; i <= n; i++)
        {
            int sum_f = 0, sum_g = 0;
            for (int j = k - 1; j >= 1; j--)
            {
                sum_f = (0LL + sum_f + f[i - 1][j]) % mod;
                sum_g = (0LL + sum_g + g[i - 1][j]) % mod;
                f[i][j] = (0LL + f[i][j] + 1LL * (k - j + 1) * f[i - 1][j - 1] % mod + sum_f) % mod;
                g[i][j] = (0LL + g[i][j] + 1LL * (k - j + 1) * g[i - 1][j - 1] % mod + sum_g) % mod;
            }
        }
        for (int i = 0; i + m <= n; i++)
        {
            int sum_f = 0, sum_g = 0;
            for (int j = 1; j < k; j++)
                sum_f = (0LL + sum_f + f[i][j]) % mod, sum_g = (0LL + sum_g + g[n - m - i][j]) % mod;
            ans = (0LL + ans + mod - 1LL * sum_f * sum_g % mod) % mod;
        }
        printf("%d\n", ans);
    }

    return 0;
}