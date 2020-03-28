// UOJ450.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 501000, mod = 19491001, g = 7;

int n, k, d, fac[MAX_N], fac_inv[MAX_N], inv[MAX_N], omega[3];

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

const int inv2 = fpow(2, mod - 2);

int binomial(int n_, int k_) { return 1LL * fac[n_] * fac_inv[k_] % mod * fac_inv[n_ - k_] % mod; }

int main()
{
    scanf("%d%d%d", &n, &k, &d);
    if (d == 1)
        printf("%d\n", fpow(k, n)), exit(0);
    inv[0] = inv[1] = 1;
    for (int i = 2; i <= k; i++)
        inv[i] = 1LL * inv[mod % i] * (mod - mod / i) % mod;
    for (int i = fac[0] = fac_inv[0] = 1; i <= k; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod, fac_inv[i] = 1LL * fac_inv[i - 1] * inv[i] % mod;
    if (d == 2)
    {
        int ans = 0;
        for (int j = 0; j <= k; j++)
            ans = (1LL * binomial(k, j) * fpow((2LL * j + mod - k) % mod, n) % mod + ans) % mod;
        ans = 1LL * ans * fpow(inv2, k) % mod;
        printf("%d\n", ans);
    }
    else
    {
        int ans = 0;
        omega[0] = 1, omega[1] = fpow(g, (mod - 1) / 3), omega[2] = 1LL * omega[1] * omega[1] % mod;
        for (int i = 0; i <= k; i++)
            for (int j = 0; i + j <= k; j++)
            {
                int p = (0LL + (k - i - j) + 1LL * omega[1] * i % mod + 1LL * omega[2] * j % mod) % mod;
                ans = (0LL + ans + 1LL * binomial(k, i) * binomial(k - i, j) % mod * fpow(p, n) % mod) % mod;
            }
        printf("%lld\n", 1LL * ans * fpow(fpow(d, k), mod - 2) % mod);
    }
    return 0;
}