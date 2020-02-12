// P4705.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4e5 + 200, mod = 998244353, G = 3;

int n, m, fac[MAX_N], fac_inv[MAX_N], ai[MAX_N], bi[MAX_N], rev[MAX_N], limit, SA[MAX_N], SB[MAX_N];

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

void poly_diff(int *src, int *dst, int poly_siz)
{
    for (int i = 0; i < poly_siz - 1; i++)
        dst[i] = 1LL * src[i + 1] * (i + 1) % mod;
    dst[poly_siz - 1] = 0;
}

int tmp_pool[30][MAX_N];

void solve(int dep, int l, int r, int *src)
{
    if (l == r)
        return (void)(tmp_pool[dep][0] = 1, tmp_pool[dep][1] = (mod - src[l]) % mod);
    int mid = (l + r) >> 1;
    solve(dep + 1, l, mid, src);
    for (int i = 0; i <= mid - l + 1; i++)
        tmp_pool[dep][i] = tmp_pool[dep + 1][i];
    solve(dep + 1, mid + 1, r, src);
    int len = r - l + 2, poly_bit = 0, poly_siz = 1;
    while (poly_siz <= len)
        poly_siz <<= 1, poly_bit++;
    ntt_initialize(poly_bit);
    for (int i = mid - l + 2; i < poly_siz; i++)
        tmp_pool[dep][i] = 0;
    for (int i = r - mid + 1; i < poly_siz; i++)
        tmp_pool[dep + 1][i] = 0;
    ntt(tmp_pool[dep], 1, poly_siz), ntt(tmp_pool[dep + 1], 1, poly_siz);
    for (int i = 0; i < poly_siz; i++)
        tmp_pool[dep][i] = 1LL * tmp_pool[dep][i] * tmp_pool[dep + 1][i] % mod, tmp_pool[dep + 1][i] = 0;
    ntt(tmp_pool[dep], -1, poly_siz);
}

void build(int *src, int *dst, int len)
{
    static int tmp_inv[MAX_N];
    memset(tmp_pool, 0, sizeof(tmp_pool));
    int poly_bit = 0, poly_siz = 1;
    while (poly_siz < (max(len, limit) << 1))
        poly_siz <<= 1, poly_bit++;
    solve(0, 1, len, src);
    poly_inverse(poly_siz >> 1, tmp_pool[0], tmp_inv);
    poly_diff(tmp_pool[0], tmp_pool[0], poly_siz), ntt_initialize(poly_bit);
    ntt(tmp_pool[0], 1, poly_siz), ntt(tmp_inv, 1, poly_siz);
    for (int i = 0; i < poly_siz; i++)
        dst[i] = 1LL * tmp_pool[0][i] * tmp_inv[i] % mod;
    ntt(dst, -1, poly_siz);
    for (int i = poly_siz - 2; i >= 0; i--)
        dst[i + 1] = 1LL * dst[i] * (mod - 1) % mod;
    dst[0] = len;
    for (int i = 0; i < poly_siz; i++)
    {
        if (i > limit)
            dst[i] = 0;
        dst[i] = 1LL * dst[i] * fac_inv[i] % mod;
        tmp_inv[i] = 0;
    }
}

void preprcoess(int upper)
{
    for (int i = fac[0] = 1; i <= upper; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    fac_inv[upper] = quick_pow(fac[upper], mod - 2);
    for (int i = upper - 1; i >= 0; i--)
        fac_inv[i] = 1LL * fac_inv[i + 1] * (i + 1) % mod;
}

int main()
{
    scanf("%d%d", &n, &m), preprcoess(MAX_N - 1);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    for (int i = 1; i <= m; i++)
        scanf("%d", &bi[i]);
    scanf("%d", &limit);
    build(ai, SA, n), build(bi, SB, m);
    int poly_bit = 0, poly_siz = 1;
    while (poly_siz <= (limit << 1))
        poly_siz <<= 1, poly_bit++;
    ntt_initialize(poly_bit);
    ntt(SA, 1, poly_siz), ntt(SB, 1, poly_siz);
    for (int i = 0; i < poly_siz; i++)
        SA[i] = 1LL * SA[i] * SB[i] % mod;
    ntt(SA, -1, poly_siz);
    for (int i = 1; i <= limit; i++)
        printf("%lld\n", 1LL * quick_pow(1LL * n * m % mod, mod - 2) * SA[i] % mod * fac[i] % mod);
    return 0;
}