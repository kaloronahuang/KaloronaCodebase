// E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4e5 + 200, mod = 998244353;

int n, m, k, ai[MAX_N], bucket[MAX_N], cd[MAX_N], fac[MAX_N];
int fac_inv[MAX_N], ans[MAX_N], answer[MAX_N];

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

int C(int n_, int k_) { return 1LL * fac[n_] * fac_inv[n_ - k_] % mod * fac_inv[k_] % mod; }

int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), bucket[ai[i]]++;
    for (int i = fac[0] = fac_inv[0] = 1; i <= max(n, m); i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    fac_inv[max(n, m)] = quick_pow(fac[max(n, m)], mod - 2);
    for (int i = max(n, m) - 1; i >= 0; i--)
        fac_inv[i] = 1LL * fac_inv[i + 1] * (i + 1) % mod;
    for (int d = 1; d <= m; d++)
        for (int i = d; i <= m; i += d)
            cd[d] += bucket[i];

    for (int d = 1; d <= m; d++)
    {
        int c_d = cd[d], pow_bas = (m / d) - 1, pow_res1 = quick_pow(m / d, n - c_d), pow_res2 = quick_pow(pow_bas, max(k - (n - c_d), 0));
        for (int i = max(k - (n - c_d), 0); i <= c_d; i++)
            ans[d] = (1LL * ans[d] + 1LL * C(c_d, i) * pow_res1 % mod * pow_res2 % mod) % mod, pow_res2 = 1LL * pow_res2 * pow_bas % mod;
    }
    for (int i = m; i >= 1; i--)
        for (int j = (i << 1); j <= m; j += i)
            ans[i] = (1LL * ans[i] + mod - ans[j]) % mod;
    for (int i = 1; i <= m; i++)
        printf("%d ", ans[i]);
    return 0;
}