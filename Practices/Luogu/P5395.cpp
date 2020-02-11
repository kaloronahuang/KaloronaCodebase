// P5395.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 6e5 + 200, mod = 167772161, G = 3;

int n, poly_bit, poly_siz, rev[MAX_N], A[MAX_N], B[MAX_N], res[MAX_N], fac[MAX_N], fac_inv[MAX_N];

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

void ntt_initialize()
{
    for (int i = 0; i < poly_siz; i++)
        rev[i] = ((rev[i >> 1] >> 1) | ((i & 1) << (poly_bit - 1)));
}

void ntt(int *arr, int dft)
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

int main()
{
    scanf("%d", &n);
    while ((1 << poly_bit) <= (n << 1))
        poly_bit++;
    poly_siz = (1 << poly_bit);
    ntt_initialize();
    for (int i = fac[0] = 1; i <= n; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    fac_inv[n] = quick_pow(fac[n], mod - 2);
    for (int i = n - 1; i >= 0; i--)
        fac_inv[i] = 1LL * fac_inv[i + 1] * (i + 1) % mod;
    for (int i = 0, opt = 1; i <= n; i++)
        A[i] = 1LL * opt * fac_inv[i] % mod, opt = (mod - opt) % mod;
    for (int i = 0; i <= n; i++)
        B[i] = 1LL * quick_pow(i, n) * fac_inv[i] % mod;
    ntt(A, 1), ntt(B, 1);
    for (int i = 0; i < poly_siz; i++)
        res[i] = 1LL * A[i] * B[i] % mod;
    ntt(res, -1);
    for (int i = 0; i <= n; i++)
        printf("%d ", res[i]);
    putchar('\n');
    return 0;
}