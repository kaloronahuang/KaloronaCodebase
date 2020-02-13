// P4491.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e7 + 200, mod = 1004535809, g = 3;

int n, m, s, wi[MAX_N], rev[MAX_N], fac[MAX_N], fac_inv[MAX_N], limit, f[MAX_N], A[MAX_N];

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

const int gi = quick_pow(g, mod - 2);

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
        int omega_n = quick_pow(dft == 1 ? g : gi, (mod - 1) / (step << 1));
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

int binomial(int n_, int k_) { return 1LL * fac[n_] * fac_inv[n_ - k_] % mod * fac_inv[k_] % mod; }

int main()
{
    scanf("%d%d%d", &n, &m, &s), limit = min(m, n / s);
    for (int i = 0; i <= m; i++)
        scanf("%d", &wi[i]);
    for (int i = fac[0] = 1; i <= max(n, m); i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    fac_inv[max(n, m)] = quick_pow(fac[max(n, m)], mod - 2);
    for (int i = max(n, m) - 1; i >= 0; i--)
        fac_inv[i] = 1LL * fac_inv[i + 1] * (i + 1) % mod;
    for (int i = 0; i <= limit; i++)
        f[i] = 1LL * fac[i] * binomial(m, i) % mod * fac[n] % mod * quick_pow(1LL * quick_pow(fac[s], i) * fac[n - s * i] % mod, mod - 2) % mod * quick_pow(m - i, n - s * i) % mod;
    for (int i = 0; i <= limit; i++)
        A[i] = 1LL * (((limit - i) & 1) ? mod - 1 : 1LL) * fac_inv[limit - i] % mod;
    int poly_siz = 1, poly_bit = 0;
    while (poly_siz <= ((limit + 1) << 1))
        poly_siz <<= 1, poly_bit++;
    ntt_initialize(poly_bit);
    ntt(A, 1, poly_siz), ntt(f, 1, poly_siz);
    for (int i = 0; i < poly_siz; i++)
        A[i] = 1LL * A[i] * f[i] % mod;
    ntt(A, -1, poly_siz);
    int ans = 0;
    for (int i = 0; i <= limit; i++)
        ans = (0LL + ans + 1LL * A[limit + i] * wi[i] % mod * fac_inv[i] % mod) % mod;
    printf("%d\n", ans);
    return 0;
}