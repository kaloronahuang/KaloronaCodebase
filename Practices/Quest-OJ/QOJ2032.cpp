// QOJ2032.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, mod = 998244353, G = 3;

int n, K, poly_bit, poly_siz, rev[MAX_N], fac[MAX_N], fac_inv[MAX_N], pow2[MAX_N];
int f[MAX_N], g[MAX_N];

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
        int omega_n = quick_pow((dft == 1 ? G : Gi), (mod - 1) / (step << 1));
        for (int j = 0; j < poly_siz; j += (step << 1))
        {
            int omega_nk = 1;
            for (int k = j; k < j + step; k++, omega_nk = 1LL * omega_nk * omega_n % mod)
            {
                int t = 1LL * arr[k + step] * omega_nk % mod;
                arr[k + step] = (0LL + arr[k] + mod - t) % mod;
                arr[k] = (1LL * arr[k] + t) % mod;
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

void polyMultiply(int *A, int *B)
{
    ntt(A, 1), ntt(B, 1);
    for (int i = 0; i < poly_siz; i++)
        A[i] = 1LL * A[i] * B[i] % mod;
    ntt(A, -1);
    for (int i = 0; i < poly_siz; i++)
        B[i] = 0;
    for (int i = K + 1; i < poly_siz; i++)
        A[i] = 0;
}

void multiply(int *A, int coeff)
{
    for (int i = 0, acc = 1; i <= K; i++, acc = 1LL * acc * coeff % mod)
        A[i] = 1LL * A[i] * acc % mod;
}

void solve(int idx)
{
    if (idx == 0)
        return (void)(f[0] = 1);
    if (idx & 1)
    {
        solve(idx - 1), g[0] = 0;
        for (int i = 1; i <= K; i++)
            g[i] = fac_inv[i];
        multiply(g, quick_pow(2, idx - 1));
        polyMultiply(f, g);
    }
    else
    {
        solve(idx >> 1);
        for (int i = 0; i <= K; i++)
            g[i] = f[i];
        multiply(g, quick_pow(2, idx >> 1));
        polyMultiply(f, g);
    }
}

int main()
{
    scanf("%d%d", &n, &K);
    for (int i = fac[0] = 1; i <= K; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    fac_inv[K] = quick_pow(fac[K], mod - 2);
    for (int i = K - 1; i >= 0; i--)
        fac_inv[i] = 1LL * fac_inv[i + 1] * (i + 1) % mod;
    for (int i = pow2[0] = 1; i <= max(n, K); i++)
        pow2[i] = 2LL * pow2[i - 1] % mod;
    while ((1 << poly_bit) <= (K << 1))
        poly_bit++;
    poly_siz = (1 << poly_bit), ntt_initialize();
    solve(n);
    int ans = 0;
    for (int i = n; i <= K; i++)
        ans = (1LL * ans + 1LL * f[i] * fac[K] % mod * fac_inv[K - i] % mod) % mod;
    printf("%d\n", ans % mod);
    return 0;
}