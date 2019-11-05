// AGC040C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e7 + 200, mod = 998244353;

int fac[MAX_N], inv[MAX_N], fac_inv[MAX_N], n, pow2[MAX_N];

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

int comb(int n_, int k_) { return 1LL * fac[n_] * fac_inv[n_ - k_] % mod * fac_inv[k_] % mod; }

int main()
{
    scanf("%d", &n);
    for (int i = fac[0] = pow2[0] = 1; i <= n; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod, pow2[i] = 1LL * pow2[i - 1] * 2 % mod;
    fac_inv[n] = quick_pow(fac[n], mod - 2);
    for (int i = n - 1; i >= 0; i--)
    {
        inv[i] = 1LL * fac_inv[i + 1] * fac[i] % mod;
        fac_inv[i] = 1LL * fac_inv[i + 1] * (i + 1) % mod;
    }
    int ans = quick_pow(3, n);
    for (int i = (n >> 1) + 1; i <= n; i++)
        ans = (1LL * ans - 2LL * comb(n, i) * pow2[n - i] % mod + mod) % mod;
    printf("%d", ans);
    return 0;
}