// CF1261D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4e5 + 200, mod = 998244353;

int n, limit, hi[MAX_N], fac[MAX_N], aff, fac_inv[MAX_N];

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

const int inv2 = quick_pow(2, mod - 2);

int binomial(int n_, int k_) { return 1LL * fac[n_] * fac_inv[n_ - k_] % mod * fac_inv[k_] % mod; }

int main()
{
    scanf("%d%d", &n, &limit);
    for (int i = 0; i < n; i++)
        scanf("%d", &hi[i]);
    if (limit == 1)
        puts("0"), exit(0);
    for (int i = 0; i < n; i++)
        if (hi[i] != hi[(i + 1) % n])
            aff++;
    for (int i = fac[0] = 1; i <= n; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    fac_inv[n] = quick_pow(fac[n], mod - 2);
    for (int i = n - 1; i >= 0; i--)
        fac_inv[i] = 1LL * fac_inv[i + 1] * (i + 1) % mod;
    int gans = 0;
    for (int i = 0; i <= aff - 1; i++)
    {
        int tmp = 1LL * quick_pow(limit - 2, i) * binomial(aff, i) % mod;
        if ((aff - i) & 1)
            tmp = 1LL * tmp * quick_pow(2, aff - i - 1) % mod;
        else
            tmp = 1LL * tmp * inv2 % mod * ((0LL + quick_pow(2, aff - i) + mod - binomial(aff - i, (aff - i) >> 1)) % mod) % mod;
        gans = (0LL + gans + tmp) % mod;
    }
    gans = 1LL * gans * quick_pow(limit, n - aff) % mod;
    printf("%d\n", gans);
    return 0;
}