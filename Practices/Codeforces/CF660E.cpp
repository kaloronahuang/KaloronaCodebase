// CF660E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200, mod = 1e9 + 7;

int n, m, fac[MAX_N], fac_inv[MAX_N];

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
    scanf("%d%d", &n, &m);
    int ans = fpow(m, n);
    for (int i = fac[0] = 1; i < MAX_N; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    fac_inv[0] = fac_inv[1] = 1;
    for (int i = 2; i < MAX_N; i++)
        fac_inv[i] = 1LL * (mod - mod / i) * fac_inv[mod % i] % mod;
    for (int i = 2; i < MAX_N; i++)
        fac_inv[i] = 1LL * fac_inv[i - 1] * fac_inv[i] % mod;
    for (int i = 1; i <= n; i++)
        ans = (0LL + ans + 1LL * fpow(m, n - i + 1) * fpow((2LL * m + mod - 1) % mod, i - 1) % mod) % mod;
    printf("%d\n", ans);
    return 0;
}