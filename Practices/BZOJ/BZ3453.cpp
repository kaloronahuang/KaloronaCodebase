// BZ3453.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_K = 220, mod = 1234567891;

int T, k, a, n, d, fac_inv[MAX_K], f[MAX_K], g[MAX_K], omega[MAX_K];

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

void calcOmega(int upper)
{
    for (int i = 1, opt = ((upper - i) & 1) ? mod - 1 : 1; i <= upper; i++, opt = mod - opt)
        omega[i] = 1LL * opt * fac_inv[upper - i] % mod * fac_inv[i - 1] % mod;
}

int evaluate(int x, int upper, int *yi)
{
    if (x <= upper)
        return yi[x];
    int base = 1, ret = 0;
    for (int i = 1; i <= upper; i++)
        base = 1LL * base * ((0LL + x - i) % mod) % mod;
    for (int i = 1; i <= upper; i++)
        ret = (0LL + ret + 1LL * yi[i] * omega[i] % mod * fpow(x - i, mod - 2) % mod) % mod;
    return 1LL * ret * base % mod;
}

int main()
{
    scanf("%d", &T), fac_inv[0] = fac_inv[1] = 1;
    for (int i = 2; i < MAX_K; i++)
        fac_inv[i] = 1LL * (mod - mod / i) * fac_inv[mod % i] % mod;
    for (int i = 2; i < MAX_K; i++)
        fac_inv[i] = 1LL * fac_inv[i] * fac_inv[i - 1] % mod;
    while (T--)
    {
        scanf("%d%d%d%d", &k, &a, &n, &d), f[0] = 0;
        for (int i = 1; i <= k + 3; i++)
            f[i] = (0LL + f[i - 1] + fpow(i, k)) % mod;
        for (int i = 1; i <= k + 3; i++)
            g[i] = (0LL + g[i - 1] + f[i]) % mod;
        calcOmega(k + 3);
        for (int i = 0; i <= k + 4; i++)
            f[i] = evaluate((1LL * i * d % mod + a) % mod, k + 3, g);
        for (int i = 1; i <= k + 4; i++)
            f[i] = (0LL + f[i] + f[i - 1]) % mod;
        calcOmega(k + 4);
        printf("%d\n", evaluate(n, k + 4, f));
    }
    return 0;
}