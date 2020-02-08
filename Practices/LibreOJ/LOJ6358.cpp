// LOJ6358.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e7 + 200, m = 4, mod = 998244353, G = 3;

int f[MAX_N], n, fac[MAX_N], fac_inv[MAX_N];

int quick_pow(int bas, int tim, int cmod)
{
    int ret = 1;
    while (tim)
    {
        if (tim & 1)
            ret = 1LL * ret * bas % cmod;
        bas = 1LL * bas * bas % cmod;
        tim >>= 1;
    }
    return ret;
}

const int wn = quick_pow(G, (mod - 1) / 4, mod);
int wns[4], wn_org[4];

int binomial(int n_, int k_) { return 1LL * fac[n_] * fac_inv[k_] % mod * fac_inv[n_ - k_] % mod; }

int main()
{
    scanf("%d", &n);
    for (int i = fac[0] = fac_inv[0] = 1; i <= n; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    fac_inv[n] = quick_pow(fac[n], mod - 2, mod);
    for (int i = n - 1; i >= 1; i--)
        fac_inv[i] = 1LL * fac_inv[i + 1] * (i + 1) % mod;
    for (int i = 0; i < 4; i++)
        wn_org[i] = quick_pow(wn, i, mod) - 1, wns[i] = 1;
    int m_inv = quick_pow(m, mod - 2, mod);
    for (int k = 0; k <= n; k++)
    {
        for (int i = 0; i < m; i++)
            f[k] = (1LL * f[k] + wns[i]) % mod;
        f[k] = 1LL * f[k] * m_inv % mod;
        for (int i = 0; i < m; i++)
            wns[i] = 1LL * wns[i] * wn_org[i] % mod;
    }
    int ans = 0;
    for (int k = n, pow_2 = 2; k >= 0; k--, pow_2 = 1LL * pow_2 * pow_2 % mod)
    {
        // subset is k;
        int tmp = 1LL * f[k] * binomial(n, k) % mod * ((pow_2 + mod - 1) % mod) % mod;
        ans = (0LL + ans + tmp) % mod;
    }
    printf("%d\n", ans + 1);
    return 0;
}