// P4389.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4e5 + 200, mod = 998244353, G = 3;

int rev[MAX_N], A[MAX_N], F[MAX_N], n, m, fac[MAX_N], inv[MAX_N], ans[MAX_N];

/*

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

const int Gi = quick_pow(G, mod - 2);

void prepare(int &poly_bit, int &poly_siz, int cmp)
{
    poly_siz = 1, poly_bit = 0;
    while (poly_siz <= cmp)
        poly_siz <<= 1, poly_bit++;
}

void ntt_initialize(int poly_bit)
{
    for (int i = 1; i < poly_bit; i++)
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

void poly_inverse(int deg, int *src, int *dst, int poly_bit = 0, int poly_siz = 1)
{
    static int tmp[MAX_N];
    if (deg == 1)
        return (void)(dst[0] = quick_pow(src[0], mod - 2));
    poly_inverse((deg + 1) >> 1, src, dst);
    prepare(poly_bit, poly_siz, deg << 1), ntt_initialize(poly_bit);
    for (int i = 0; i < deg; i++)
        tmp[i] = src[i];
    for (int i = deg; i < poly_siz; i++)
        tmp[i] = 0;
    ntt(tmp, 1, poly_siz), ntt(dst, 1, poly_siz);
    for (int i = 0; i < poly_siz; i++)
        dst[i] = 1LL * dst[i] * ((2LL - 1LL * dst[i] * tmp[i] % mod) % mod) % mod;
    ntt(dst, -1, poly_siz);
    for (int i = deg; i < poly_siz; i++)
        dst[i] = 0;
}

void poly_diff(int deg, int *src, int *dst)
{
    for (int i = 1; i < deg; i++)
        dst[i - 1] = 1LL * src[i] * i % mod;
    dst[deg - 1] = 0;
}

void poly_sum(int deg, int *src, int *dst)
{
    for (int i = 1; i < deg; i++)
        dst[i] = 1LL * src[i - 1] * quick_pow(i, mod - 2) % mod;
    dst[0] = 0;
}

void poly_ln(int deg, int *src, int *dst, int poly_bit = 0, int poly_siz = 1)
{
    static int tmp_diff[MAX_N], tmp_inv[MAX_N];
    poly_diff(deg, src, tmp_diff), poly_inverse(deg, src, tmp_inv);
    prepare(poly_bit, poly_siz, (deg << 1)), ntt_initialize(poly_bit);
    ntt(tmp_diff, 1, poly_siz), ntt(tmp_inv, 1, poly_siz);
    for (int i = 0; i < poly_siz; i++)
        tmp_diff[i] = 1LL * tmp_diff[i] * tmp_inv[i] % mod;
    ntt(tmp_diff, -1, poly_siz);
    poly_sum(deg, tmp_diff, dst);
    for (int i = deg; i < poly_siz; i++)
        dst[i] = 0;
    for (int i = 0; i < poly_siz; i++)
        tmp_diff[i] = tmp_inv[i] = 0;
}

void poly_exp(int deg, int *src, int *dst, int poly_bit = 0, int poly_siz = 1)
{
    if (deg == 1)
        return (void)(dst[0] = 1);
    static int tmp_ln[MAX_N];
    poly_exp((deg + 1) >> 1, src, dst), poly_ln(deg, dst, tmp_ln);
    prepare(poly_bit, poly_siz, (deg << 1)), ntt_initialize(poly_bit);
    for (int i = 0; i < deg; i++)
        tmp_ln[i] = (0LL + src[i] + mod - tmp_ln[i]) % mod;
    for (int i = deg; i < poly_siz; i++)
        tmp_ln[i] = 0;
    tmp_ln[0] = (tmp_ln[0] + 1) % mod;
    ntt(tmp_ln, 1, poly_siz), ntt(dst, 1, poly_siz);
    for (int i = 0; i < poly_siz; i++)
        dst[i] = 1LL * tmp_ln[i] * dst[i] % mod;
    ntt(dst, -1, poly_siz);
    for (int i = deg; i < poly_siz; i++)
        dst[i] = 0;
    for (int i = 0; i < poly_siz; i++)
        tmp_ln[i] = 0;
}

*/

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

const int Gi = quick_pow(G, mod - 2);

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

void poly_inverse(int deg, int *src, int *dst)
{
    static int tmp[MAX_N];
    if (deg == 1)
        return (void)(dst[0] = quick_pow(src[0], mod - 2));
    poly_inverse((deg + 1) >> 1, src, dst);
    int poly_bit = 0, poly_siz = 1;
    while (poly_siz <= (deg << 1))
        poly_siz <<= 1, poly_bit++;
    ntt_initialize(poly_bit);
    for (int i = 0; i < deg; i++)
        tmp[i] = src[i];
    for (int i = deg; i < poly_siz; i++)
        tmp[i] = 0;
    ntt(tmp, 1, poly_siz), ntt(dst, 1, poly_siz);
    for (int i = 0; i < poly_siz; i++)
        dst[i] = 1LL * dst[i] * ((2LL + mod - 1LL * tmp[i] * dst[i] % mod) % mod) % mod;
    ntt(dst, -1, poly_siz);
    for (int i = deg; i < poly_siz; i++)
        dst[i] = 0;
}

void poly_diff(int *src, int *dst, int deg)
{
    for (int i = 0; i < deg - 1; i++)
        dst[i] = 1LL * src[i + 1] * (i + 1) % mod;
    dst[deg - 1] = 0;
}

void poly_sum(int *src, int *dst, int deg)
{
    for (int i = 1; i < deg; i++)
        dst[i] = 1LL * src[i - 1] * quick_pow(i, mod - 2) % mod;
    dst[0] = 0;
}

void poly_ln(int deg, int *src, int *dst)
{
    static int tmp_diff[MAX_N], tmp_inv[MAX_N];
    int poly_bit = 0, poly_siz = 1;
    while (poly_siz <= (deg << 1))
        poly_siz <<= 1, poly_bit++;
    ntt_initialize(poly_bit);
    for (int i = 0; i < poly_siz; i++)
        tmp_diff[i] = tmp_inv[i] = 0;
    poly_diff(src, tmp_diff, deg), poly_inverse(deg, src, tmp_inv);
    ntt(tmp_inv, 1, poly_siz), ntt(tmp_diff, 1, poly_siz);
    for (int i = 0; i < poly_siz; i++)
        tmp_diff[i] = 1LL * tmp_diff[i] * tmp_inv[i] % mod;
    ntt(tmp_diff, -1, poly_siz);
    for (int i = deg; i < poly_siz; i++)
        tmp_diff[i] = 0;
    poly_sum(tmp_diff, dst, deg);
}

void poly_exp(int deg, int *src, int *dst)
{
    static int tmp_ln[MAX_N];
    if (deg == 1)
        return (void)(dst[0] = 1);
    poly_exp((deg + 1) >> 1, src, dst), poly_ln(deg, dst, tmp_ln);
    int poly_bit = 0, poly_siz = 1;
    while (poly_siz <= (deg << 1))
        poly_siz <<= 1, poly_bit++;
    ntt_initialize(poly_bit);
    for (int i = 0; i < deg; i++)
        tmp_ln[i] = (0LL + src[i] + mod - tmp_ln[i]) % mod;
    for (int i = deg; i < poly_siz; i++)
        tmp_ln[i] = 0;
    tmp_ln[0] = (tmp_ln[0] + 1) % mod;
    ntt(dst, 1, poly_siz), ntt(tmp_ln, 1, poly_siz);
    for (int i = 0; i < poly_siz; i++)
        dst[i] = 1LL * dst[i] * tmp_ln[i] % mod;
    ntt(dst, -1, poly_siz);
    for (int i = deg; i < poly_siz; i++)
        dst[i] = tmp_ln[i] = 0;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, val; i <= n; i++)
        scanf("%d", &val), A[val]++;
    for (int i = fac[0] = 1; i <= m; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    int bas = quick_pow(fac[m], mod - 2);
    for (int i = m; i >= 0; i--)
        inv[i] = 1LL * bas * fac[i - 1] % mod, bas = 1LL * bas * i % mod;
    for (int i = 1; i <= m; i++)
        if (A[i])
            for (int j = i; j <= m; j += i)
                F[j] = (0LL + F[j] + 1LL * A[i] * (mod - inv[j / i]) % mod) % mod;
    poly_exp(m + 1, F, ans), memset(F, 0, sizeof(F)), poly_inverse(m + 1, ans, F);
    for (int i = 1; i <= m; i++)
        printf("%d\n", F[i]);
    return 0;
}