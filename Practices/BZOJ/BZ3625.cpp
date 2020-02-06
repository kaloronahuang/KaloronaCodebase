// BZ3625.cpp
#pragma GCC optimize(2)
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 200, mod = 998244353, G = 3;

int n, m, ci[MAX_N], rev[MAX_N], tmp[MAX_N], D[MAX_N], ans[MAX_N], bi[MAX_N], org[MAX_N];

int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x * f;
}

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

const int inv2 = quick_pow(2, mod - 2), Gi = quick_pow(G, mod - 2);

void ntt_initialize(int poly_bit)
{
    for (int i = 1; i < (1 << poly_bit); i++)
        rev[i] = ((rev[i >> 1] >> 1) | ((i & 1) << (poly_bit - 1)));
}

void ntt(int *arr, int dft, int poly_siz)
{
    for (int i = 0; i < poly_siz; i++)
        if (i < rev[i])
            swap(arr[i], arr[rev[i]]);
    for (int step = 1; step < poly_siz; step <<= 1)
    {
        int omega_n = quick_pow(dft == 1 ? G : Gi, (mod - 1) / (step << 1));
        for (int j = 0; j < poly_siz; j += (step << 1))
        {
            int omega_nk = 1;
            for (int k = j; k < j + step; k++, omega_nk = 1LL * omega_nk * omega_n % mod)
            {
                int t = 1LL * omega_nk * arr[k + step] % mod;
                arr[k + step] = (0LL + arr[k] + mod - t) % mod, arr[k] = (0LL + arr[k] + t) % mod;
            }
        }
    }
    if (dft == -1)
    {
        int inv = quick_pow(poly_siz, mod - 2);
        for (int i = 0; i < poly_siz; i++)
            arr[i] = 1LL * arr[i] * inv % mod;
    }
}

void poly_inverse(int *src, int *dst, int deg)
{
    if (deg == 1)
        return (void)(dst[0] = quick_pow(src[0], mod - 2));
    poly_inverse(src, dst, (deg + 1) >> 1);
    int poly_bit = 0, poly_siz = 1;
    while (poly_siz < (deg << 1))
        poly_siz <<= 1, poly_bit++;
    ntt_initialize(poly_bit);
    for (int i = 0; i < deg; i++)
        tmp[i] = src[i];
    for (int i = deg; i < poly_siz; i++)
        tmp[i] = 0;
    ntt(tmp, 1, poly_siz), ntt(dst, 1, poly_siz);
    for (int i = 0; i < poly_siz; i++)
        dst[i] = 1LL * dst[i] * ((2LL + mod - 1LL * dst[i] * tmp[i] % mod) % mod) % mod;
    ntt(dst, -1, poly_siz);
    for (int i = deg; i < poly_siz; i++)
        dst[i] = 0;
}

void poly_sqrt(int *src, int *dst, int deg)
{
    if (deg == 1)
        return (void)(dst[0] = 1);
    poly_sqrt(src, dst, (deg + 1) >> 1);

    for (int i = 0; i <= (deg << 1); i++)
        D[i] = 0;
    poly_inverse(dst, D, deg);

    int poly_bit = 0, poly_siz = 1;
    while (poly_siz < (deg << 1))
        poly_siz <<= 1, poly_bit++;
    ntt_initialize(poly_bit);

    for (int i = 0; i < deg; i++)
        tmp[i] = src[i];
    for (int i = deg; i < poly_siz; i++)
        tmp[i] = 0;

    ntt(dst, 1, poly_siz), ntt(D, 1, poly_siz), ntt(tmp, 1, poly_siz);
    for (int i = 0; i < poly_siz; i++)
        dst[i] = 1LL * inv2 * ((0LL + dst[i] + 1LL * tmp[i] * D[i] % mod) % mod) % mod;
    ntt(dst, -1, poly_siz);

    for (int i = deg; i < poly_siz; i++)
        dst[i] = 0;
}

int main()
{
    n = read(), m = read(), ci[0] = 1;
    for (int i = 1, val; i <= n; i++)
    {
        val = read();
        if (val <= m)
            ci[val] = mod - 4;
    }
    poly_sqrt(ci, bi, m + 1), bi[0]++;
    poly_inverse(bi, ans, m + 1);
    for (int i = 1; i <= m; i++)
        printf("%lld\n", 2LL * ans[i] % mod);
    return 0;
}