// E.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mod = 998244353, MAX_N = 2e5 + 200;

int n, k, fac[MAX_N], fac_inv[MAX_N];

int binomial(int n_, int k_) { return 1LL * fac[n_] * fac_inv[k_] % mod * fac_inv[n_ - k_] % mod; }

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
    scanf("%d%d", &n, &k);
    if (k >= n)
        puts("0"), exit(0);
    if (k == 0)
    {
        int ans = 1;
        for (int i = 1; i <= n; i++)
            ans = 1LL * ans * i % mod;
        printf("%d\n", ans);
        return 0;
    }
    for (int i = fac[0] = 1; i <= n; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    fac_inv[0] = fac_inv[1] = 1;
    for (int i = 2; i <= n; i++)
        fac_inv[i] = 1LL * (mod - mod / i) * fac_inv[mod % i] % mod;
    for (int i = 2; i <= n; i++)
        fac_inv[i] = 1LL * fac_inv[i] * fac_inv[i - 1] % mod;
    int slot = n - k;
    // int ans = (0LL + fpow(slot, n) + mod - 1LL * slot * fpow(slot - 1, n) % mod) % mod;
    int ans = 0;
    for (int i = slot, opt = 1; i >= 1; i--, opt = mod - opt)
    {
        ans = (0LL + ans + 1LL * opt * binomial(slot, i) % mod * fpow(i, n) % mod) % mod;
    }
    printf("%lld\n", 2LL * ans * binomial(n, slot) % mod);
    return 0;
}