// CF961G.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, mod = 1e9 + 7;

int n, k, wi[MAX_N], fac[MAX_N], fac_inv[MAX_N];

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

int stirling(int n_, int k_)
{
    int ret = 0;
    for (int i = 0, opt = 1; i <= k_; i++, opt = (mod - opt) % mod)
        ret = (0LL + ret + 1LL * opt * fac_inv[i] % mod * quick_pow(k_ - i, n_) % mod * fac_inv[k_ - i] % mod) % mod;
    return ret;
}

int main()
{
    scanf("%d%d", &n, &k);
    int acc = 0;
    for (int i = 1, val; i <= n; i++)
        scanf("%d", &val), acc = (0LL + acc + val) % mod;
    for (int i = fac[0] = 1; i <= n; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    fac_inv[n] = quick_pow(fac[n], mod - 2);
    for (int i = n - 1; i >= 0; i--)
        fac_inv[i] = 1LL * fac_inv[i + 1] * (i + 1) % mod;
    int p = (stirling(n, k) + 1LL * (n - 1) * stirling(n - 1, k) % mod) % mod;
    printf("%lld\n", 1LL * acc * p % mod);
    return 0;
}