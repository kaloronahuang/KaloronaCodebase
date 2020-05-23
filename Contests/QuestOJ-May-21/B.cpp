// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 8e5 + 200, mod = 998244353, G = 3;

int n, m, fac[MAX_N], fac_inv[MAX_N], inv[MAX_N], rev[MAX_N], poly_siz, poly_bit, g[MAX_N], f[MAX_N], ginv[MAX_N], finv[MAX_N], ans[MAX_N];

int fpow(int bas, long long tim)
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
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (poly_bit - 1));
}

void ntt_prepare(int len)
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
    if (deg == 1)
        return (void)(dst[0] = fpow(src[0], mod - 2));
    poly_inverse(src, dst, (deg + 1) >> 1);
    static int tmp[MAX_N];
    ntt_prepare(deg << 1);
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
    scanf("%d%d", &n, &m);
    for (int i = fac[0] = 1; i <= n; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    inv[0] = inv[1] = 1;
    for (int i = 2; i <= n; i++)
        inv[i] = 1LL * (mod - mod / i) * inv[mod % i] % mod;
    for (int i = fac_inv[0] = 1; i <= n; i++)
        fac_inv[i] = 1LL * fac_inv[i - 1] * inv[i] % mod;
    ntt_prepare(n);
    int siz = poly_siz;
    for (int i = 0; i < siz; i++)
        g[i] = 1LL * fpow(2, 1LL * i * (i - 1) / 2) * fac_inv[i] % mod;
    g[0] = 1, poly_inverse(g, ginv, siz);
    for (int i = 0; i < min(m, siz); i++)
        f[i] = (0LL + mod - ginv[i]) % mod;
    f[0] = mod - 1;
    poly_inverse(f, finv, siz);
    for (int i = 0; i < siz; i++)
        ans[i] = 1LL * finv[i] * fac[i] % mod;
    printf("%lld\n", (0LL + 1LL * g[n] * fac[n] % mod + ans[n]) % mod);
    return 0;
}