// UVa7040.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200, mod = 1e9 + 7;

int T, n, m, k, fac[MAX_N], fac_inv[MAX_N], inv[MAX_N];

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

void preprocess()
{
    for (int i = fac[0] = 1; i < MAX_N; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    inv[0] = inv[1] = 1;
    for (int i = 2; i < MAX_N; i++)
        inv[i] = 1LL * (mod - mod / i) * inv[mod % i] % mod;
    for (int i = fac_inv[0] = 1; i < MAX_N; i++)
        fac_inv[i] = 1LL * fac_inv[i - 1] * inv[i] % mod;
}

int binomial(int n_, int k_) { return 1LL * fac[n_] * fac_inv[k_] % mod * fac_inv[n_ - k_] % mod; }

int main()
{
    scanf("%d", &T), preprocess();
    while (T--)
    {
        scanf("%d%d%d", &n, &m, &k);
        int pans = 0;
        for (int i = 0, opt = ((k - i) & 1) ? mod - 1 : 1; i <= k; i++, opt = mod - opt)
            pans = (0LL + pans + 1LL * opt * binomial(k, i) % mod * i % mod * fpow(i - 1, n - 1) % mod) % mod;
        // then we wanna {m \choose k};
        for (int i = m - k + 1; i <= m; i++)
            pans = 1LL * pans * i % mod;
        pans = 1LL * pans * fac_inv[k] % mod;
        printf("%d\n", pans);
    }
    return 0;
}