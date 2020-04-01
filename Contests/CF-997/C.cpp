// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200, mod = 998244353;

int n, fac[MAX_N], fac_inv[MAX_N], inv[MAX_N];

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

int binomial(int n_, int k_) { return 1LL * fac[n_] * fac_inv[k_] % mod * fac_inv[n_ - k_] % mod; }

int main()
{
    scanf("%d", &n);
    inv[0] = inv[1] = 1;
    for (int i = 2; i <= n; i++)
        inv[i] = 1LL * inv[mod % i] * (mod - mod / i) % mod;
    for (int i = fac[0] = fac_inv[0] = 1; i <= n; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod, fac_inv[i] = 1LL * fac_inv[i - 1] * inv[i] % mod;
    int ans = 0;
    for (int i = 1, opt = 1; i <= n; i++, opt = mod - opt)
        ans = (0LL + ans + 1LL * opt * binomial(n, i) % mod * fpow(3, i) % mod * fpow(3, 1LL * n * (n - i) % (mod - 1)) % mod) % mod;
    ans = 2LL * ans % mod;
    int part = 0;
    for (int i = 1, opt = mod - 1; i <= n; i++, opt = mod - opt)
    {
        int tmpi = 1LL * opt * binomial(n, i) % mod * fpow(3, ((mod - 1) - 1LL * n * i % (mod - 1)) % (mod - 1)) % mod;
        int tmpj = (0LL + fpow((1 + mod - fpow(3, (i + mod - 1 - n) % (mod - 1))) % mod, n) + mod - 1) % mod;
        part = (0LL + part + 1LL * tmpi * tmpj % mod) % mod;
    }
    part = 1LL * part * 3LL % mod * fpow(3, 1LL * n * n % (mod - 1)) % mod * (mod - 1) % mod;
    printf("%lld\n", (0LL + part + ans) % mod);
    return 0;
}