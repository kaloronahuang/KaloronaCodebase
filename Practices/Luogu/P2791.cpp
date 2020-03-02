// P2791.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 30000, mod = 998244353, G = 3, RANGE = 2e7 + 1;

int n, m, S, L, rev[MAX_N], fac[RANGE], fac_inv[RANGE], f[2][MAX_N];

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

const int Gi = fpow(G, mod - 2);

void ntt_initialize(int poly_bit)
{
    for (int i = 0; i < (1 << poly_bit); i++)
        rev[i] = ((rev[i >> 1] >> 1) | ((i & 1) << (poly_bit - 1)));
}

void ntt(int *arr, int dft, int poly_siz)
{
    for (int i = 0; i < poly_siz; i++)
        if (i < rev[i])
            swap(arr[i], arr[rev[i]]);
    for (int step = 1; step < poly_siz; step <<= 1)
    {
        int omega_n = fpow(dft == 1 ? G : Gi, (mod - 1) / (step << 1));
        for (int j = 0; j < poly_siz; j += (step << 1))
        {
            int omega_nk = 1;
            for (int k = j; k < j + step; k++, omega_nk = 1LL * omega_nk * omega_n % mod)
            {
                int t = 1LL * arr[k + step] * omega_nk % mod;
                arr[k + step] = (0LL + arr[k] + mod - t) % mod, arr[k] = (0LL + arr[k] + t) % mod;
            }
        }
    }
    if (dft == -1)
    {
        int inv = fpow(poly_siz, mod - 2);
        for (int i = 0; i < poly_siz; i++)
            arr[i] = 1LL * arr[i] * inv % mod;
    }
}

int binomial(int n_, int k_) { return 1LL * fac[n_] * fac_inv[n_ - k_] % mod * fac_inv[k_] % mod; }

void initialize(int limit)
{
    for (int i = fac[0] = 1; i <= limit; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    fac_inv[limit] = fpow(fac[limit], mod - 2);
    for (int i = limit - 1; i >= 0; i--)
        fac_inv[i] = 1LL * fac_inv[i + 1] * (i + 1) % mod;
}

int main()
{
    scanf("%d%d%d%d", &n, &m, &S, &L);
    initialize(max(n, L));
    int poly_bit = 0;
    while ((1 << poly_bit) <= (L << 1))
        poly_bit++;
    int poly_siz = 1 << poly_bit;
    ntt_initialize(poly_bit);
    for (int i = 0, opt = 1; i <= L; i++, opt = mod - opt)
        f[0][i] = 1LL * opt * fac_inv[i] % mod;
    for (int i = 0; i <= L; i++)
        f[1][i] = 1LL * fac_inv[i] * fpow(i, L) % mod;
    ntt(f[0], 1, poly_siz), ntt(f[1], 1, poly_siz);
    for (int i = 0; i < poly_siz; i++)
        f[0][i] = 1LL * f[0][i] * f[1][i] % mod;
    ntt(f[0], -1, poly_siz);
    while (S--)
    {
        int ni, mi, ki, ret = 0;
        scanf("%d%d%d", &ni, &mi, &ki);
        int limit = min(L, min(mi, min(ni, ki)));
        for (int i = 0; i <= limit; i++)
            ret = (0LL + ret + 1LL * f[0][i] * fac_inv[mi - i] % mod * fac[ni - i] % mod * fac_inv[ki - i] % mod) % mod;
        ret = 1LL * ret * fac[mi] % mod * fac_inv[ni] % mod * fac[ki] % mod;
        printf("%d\n", ret);
    }
    return 0;
}