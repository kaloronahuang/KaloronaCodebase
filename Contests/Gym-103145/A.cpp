// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5010 * 5010, mod = 998244353;

int T, fac[MAX_N], fac_inv[MAX_N], n;

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
    for (int i = fac[0] = 1; i < MAX_N; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    fac_inv[MAX_N - 1] = fpow(fac[MAX_N - 1], mod - 2);
    for (int i = MAX_N - 2; i >= 0; i--)
        fac_inv[i] = 1LL * fac_inv[i + 1] * (i + 1) % mod;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        int gans = 0;
        for (int x = 1; x <= n; x++)
        {
            int pans = 1LL * n * binomial(n * n - x, n - 1) % mod * fac[n * n - n] % mod * fac[n] % mod;
            gans = (0LL + gans + pans) % mod;
        }
        printf("%d\n", gans);
    }
    return 0;
}