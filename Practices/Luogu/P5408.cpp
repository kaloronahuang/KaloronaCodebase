// P5408.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 6e5 + 20000, mod = 167772161, g = 3;

int n, rev[MAX_N], fac[MAX_N], fac_inv[MAX_N], f[MAX_N];

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

const int Gi = quick_pow(g, mod - 2);

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
        int omega_n = quick_pow(dft == 1 ? g : Gi, (mod - 1) / (step << 1));
        for (int j = 0; j < poly_siz; j += (step << 1))
        {
            int omega_nk = 1;
            for (int k = j; k < j + step; k++, omega_nk = 1LL * omega_n * omega_nk % mod)
            {
                int t = 1LL * arr[k + step] * omega_nk % mod;
                arr[k + step] = (0LL + arr[k] + mod - t) % mod, arr[k] = (1LL * arr[k] + t) % mod;
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

void offset(int *src, int *dst, int deg, int c)
{
    static int A[MAX_N], B[MAX_N];
    // dst(x) = src(x + c);
    int poly_bit = 0, poly_siz = 1;
    while (poly_siz <= (deg << 1))
        poly_bit++, poly_siz <<= 1;
    for (int i = 0; i < deg; i++)
        A[deg - i - 1] = 1LL * src[i] * fac[i] % mod;
    int pow_acc = 1;
    for (int i = 0; i < deg; i++, pow_acc = 1LL * pow_acc * c % mod)
        B[i] = 1LL * pow_acc * fac_inv[i] % mod;
    for (int i = deg; i < poly_siz; i++)
        A[i] = B[i] = 0;
    ntt_initialize(poly_bit);
    ntt(A, 1, poly_siz), ntt(B, 1, poly_siz);
    for (int i = 0; i < poly_siz; i++)
        A[i] = 1LL * A[i] * B[i] % mod;
    ntt(A, -1, poly_siz);
    for (int i = 0; i < deg; i++)
        dst[i] = 1LL * A[deg - i - 1] * fac_inv[i] % mod;
}

void solve(int deg, int *src)
{
    static int A[MAX_N], B[MAX_N];
    if (deg == 0)
        return (void)(src[0] = 1);
    int len = (deg >> 1);
    solve(len, src);
    offset(src, A, len + 1, len);
    int poly_bit = 0, poly_siz = 1;
    while (poly_siz <= deg)
        poly_bit++, poly_siz <<= 1;
    for (int i = 0; i <= len; i++)
        B[i] = src[i];
    for (int i = len + 1; i < poly_siz; i++)
        A[i] = B[i] = 0;
    ntt_initialize(poly_bit);
    ntt(A, 1, poly_siz), ntt(B, 1, poly_siz);
    for (int i = 0; i < poly_siz; i++)
        A[i] = 1LL * A[i] * B[i] % mod;
    ntt(A, -1, poly_siz);
    if (deg & 1)
        for (int i = 0; i <= deg; i++)
            src[i] = ((i != 0 ? A[i - 1] : 0) + 1LL * (deg - 1) * A[i] % mod) % mod;
    else
        for (int i = 0; i <= deg; i++)
            src[i] = A[i];
}

int main()
{
    scanf("%d", &n);

    for (int i = fac[0] = 1; i <= (n << 1); i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    fac_inv[n << 1] = quick_pow(fac[n << 1], mod - 2);
    for (int i = (n << 1) - 1; i >= 0; i--)
        fac_inv[i] = 1LL * fac_inv[i + 1] * (i + 1) % mod;

    solve(n, f);
    for (int i = 0; i <= n; i++)
        printf("%d ", f[i]);
    putchar('\n');
    return 0;
}