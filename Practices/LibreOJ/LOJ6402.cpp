// LOJ6402.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e6 + 200, mod = 998244353, G = 3;

int n, rev[MAX_N], poly_siz, poly_bit, fi[MAX_N], gi[MAX_N], gInv[MAX_N], hi[MAX_N], ans[MAX_N], upper[MAX_N];

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

void ntt_initialize()
{
    for (int i = 0; i < poly_siz; i++)
        rev[i] = ((rev[i >> 1] >> 1) | ((i & 1) << (poly_bit - 1)));
}

void prepare(int len)
{
    poly_siz = 1, poly_bit = 0;
    while (poly_siz <= len)
        poly_siz <<= 1, poly_bit++;
    ntt_initialize();
}

void ntt(int *arr, int dft)
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

void poly_inverse(int *src, int *dst, int deg)
{
    static int tmp[MAX_N];
    if (deg == 1)
        return (void)(dst[0] = fpow(src[0], mod - 2));
    poly_inverse(src, dst, (deg + 1) >> 1);
    prepare(deg << 1);
    for (int i = 0; i < deg; i++)
        tmp[i] = src[i];
    for (int i = deg; i < poly_siz; i++)
        tmp[i] = 0;
    ntt(tmp, 1), ntt(dst, 1);
    for (int i = 0; i < poly_siz; i++)
        dst[i] = 1LL * dst[i] * ((2LL + mod - 1LL * tmp[i] * dst[i] % mod) % mod) % mod;
    ntt(dst, -1);
    for (int i = deg; i < poly_siz; i++)
        dst[i] = 0;
}

int main()
{
    scanf("%d", &n), n++;
    for (int i = gi[0] = 1; i <= n; i++)
        gi[i] = 1LL * gi[i - 1] * i % mod;
    for (int i = 0; i <= n; i++)
        upper[i] = 2LL * gi[i] % mod;
    upper[0] = (upper[0] + mod - 1) % mod;
    poly_inverse(gi, gInv, n + 1);
    prepare(n << 1);
    ntt(gInv, 1), ntt(upper, 1);
    for (int i = 0; i < poly_siz; i++)
        fi[i] = 1LL * gInv[i] * upper[i] % mod;
    ntt(fi, -1);
    for (int i = 0; i <= n; i++)
        hi[i] = (mod - 1LL * i * fi[i] % mod) % mod;
    hi[0] = (hi[0] + 1) % mod;
    poly_inverse(hi, ans, n + 1);
    printf("%d\n", ans[n - 1]);
    return 0;
}