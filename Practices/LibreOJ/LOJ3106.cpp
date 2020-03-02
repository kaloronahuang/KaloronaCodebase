// LOJ3106.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4040, mod = 998244353, G = 3;

int n, a, b, c, d, rev[MAX_N], fac[MAX_N], fac_inv[MAX_N], f[5][MAX_N];

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
                arr[k + step] = (0LL + arr[k] + mod - t) % mod, arr[k] = (1LL * arr[k] + t) % mod;
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

int solve(int x)
{
    memset(f, 0, sizeof(f));
    for (int i = 0; i <= a - x; i++)
        f[0][i] = fac_inv[i];
    for (int i = 0; i <= b - x; i++)
        f[1][i] = fac_inv[i];
    for (int i = 0; i <= c - x; i++)
        f[2][i] = fac_inv[i];
    for (int i = 0; i <= d - x; i++)
        f[3][i] = fac_inv[i];
    int poly_bit = 0;
    while ((1 << poly_bit) <= (a + b + c + d - 4 * x))
        poly_bit++;
    ntt_initialize(poly_bit);
    for (int i = 0; i < 4; i++)
        ntt(f[i], 1, 1 << poly_bit);
    for (int i = 0; i < (1 << poly_bit); i++)
        f[0][i] = 1LL * f[0][i] * f[1][i] % mod * f[2][i] % mod * f[3][i] % mod;
    ntt(f[0], -1, (1 << poly_bit));
    return 1LL * f[0][n - 4 * x] * fac[n - 4 * x] % mod;
}

int main()
{
    scanf("%d%d%d%d%d", &n, &a, &b, &c, &d);
    for (int i = fac[0] = 1; i < MAX_N; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    fac_inv[MAX_N - 1] = fpow(fac[MAX_N - 1], mod - 2);
    for (int i = MAX_N - 2; i >= 0; i--)
        fac_inv[i] = 1LL * fac_inv[i + 1] * (i + 1) % mod;
    int ans = 0;
    for (int i = 0, opt = 1; i <= min(n >> 2, min(a, min(b, min(c, d)))); i++, opt = -opt)
        ans = (0LL + ans + mod + 1LL * opt * binomial(n - 3 * i, i) % mod * solve(i) % mod) % mod;
    printf("%d\n", ans);
    return 0;
}