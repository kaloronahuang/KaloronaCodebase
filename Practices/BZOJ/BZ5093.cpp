// BZ5093.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 8e5 + 200, mod = 998244353, g = 3;

int n, lower, rev[MAX_N], dpow[MAX_N], S[MAX_N], poly_bit, poly_siz, fac[MAX_N], fac_inv[MAX_N], inv[MAX_N];
int A[MAX_N], B[MAX_N];

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

const int gi = fpow(g, mod - 2);

void ntt_prepare(int len)
{
    poly_bit = 0, poly_siz = 1;
    while ((1 << poly_bit) <= len)
        poly_bit++;
    poly_siz = 1 << poly_bit;
}

void ntt_initialize()
{
    for (int i = 0; i < poly_siz; i++)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (poly_bit - 1));
}

void ntt(int *arr, int dft)
{
    for (int i = 0; i < poly_siz; i++)
        if (i < rev[i])
            swap(arr[i], arr[rev[i]]);
    for (int step = 1; step < poly_siz; step <<= 1)
    {
        int omega_n = fpow(dft == 1 ? g : gi, (mod - 1) / (step << 1));
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
        int inv = fpow(poly_siz, mod - 2);
        for (int i = 0; i < poly_siz; i++)
            arr[i] = 1LL * arr[i] * inv % mod;
    }
}

void preprocess()
{
    dpow[0] = 1;
    for (int i = 1; i <= lower; i++)
        dpow[i] = 1LL * dpow[i - 1] * (n - i) % mod;
    // process the stirling number 2nd;
    for (int i = fac[0] = 1; i <= lower; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    inv[0] = inv[1] = 1;
    for (int i = 2; i <= lower; i++)
        inv[i] = 1LL * (mod - mod / i) * inv[mod % i] % mod;
    for (int i = fac_inv[0] = 1; i <= lower; i++)
        fac_inv[i] = 1LL * fac_inv[i - 1] * inv[i] % mod;
    for (int i = 0, opt = 1; i <= lower; i++, opt = mod - opt)
        A[i] = 1LL * opt * fac_inv[i] % mod;
    for (int i = 0; i <= lower; i++)
        B[i] = 1LL * fpow(i, lower) * fac_inv[i] % mod;
    ntt_prepare(lower << 1), ntt_initialize(), ntt(A, 1), ntt(B, 1);
    for (int i = 0; i < poly_siz; i++)
        S[i] = 1LL * A[i] * B[i] % mod;
    ntt(S, -1);
}

int main()
{
    scanf("%d%d", &n, &lower), preprocess();
    int ans = 0;
    for (int i = 0; i <= lower; i++)
        ans = (0LL + ans + 1LL * S[i] * dpow[i] % mod * fpow(2, n - i - 1) % mod) % mod;
    printf("%lld\n", 1LL * ans * fpow(2, 1LL * (n - 1) * (n - 2) / 2 % (mod - 1)) % mod * n % mod);
    return 0;
}