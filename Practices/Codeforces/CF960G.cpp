// CF960G.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, G = 3, mod = 998244353;

int n, A, B, fac[MAX_N], fac_inv[MAX_N], rev[MAX_N], tA[20][MAX_N];

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

void process_fac()
{
    for (int i = fac[0] = 1; i <= n; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    fac_inv[n] = quick_pow(fac[n], mod - 2);
    for (int i = n - 1; i >= 0; i--)
        fac_inv[i] = 1LL * fac_inv[i + 1] * (i + 1) % mod;
}

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
                int t = 1LL * arr[k + step] * omega_nk % mod;
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

void solve(int l, int r, int dep)
{
    if (l == r)
        return (void)(tA[dep][0] = l, tA[dep][1] = 1);
    int mid = (l + r) >> 1;
    solve(l, mid, dep + 1);
    for (int i = 0; i <= mid - l + 1; i++)
        tA[dep][i] = tA[dep + 1][i];
    solve(mid + 1, r, dep + 1);
    int poly_siz = 1, poly_bit = 0;
    while (poly_siz < (r - l + 10))
        poly_siz <<= 1, poly_bit++;
    ntt_initialize(poly_bit);
    for (int i = mid - l + 2; i < poly_siz; i++)
        tA[dep][i] = 0;
    for (int i = r - mid + 1; i < poly_siz; i++)
        tA[dep + 1][i] = 0;
    ntt(tA[dep], 1, poly_siz), ntt(tA[dep + 1], 1, poly_siz);
    for (int i = 0; i < poly_siz; i++)
        tA[dep][i] = 1LL * tA[dep][i] * tA[dep + 1][i] % mod;
    ntt(tA[dep], -1, poly_siz);
}

int main()
{
    scanf("%d%d%d", &n, &A, &B);
    if (A == 0 || B == 0 || A + B - 2 > n - 1)
        puts("0"), exit(0);
    if (n == 1)
        puts("1"), exit(0);
    process_fac(), solve(0, n - 2, 0);
    printf("%lld\n", 1LL * fac[A + B - 2] * fac_inv[A - 1] % mod * fac_inv[B - 1] % mod * tA[0][A + B - 2] % mod);
    return 0;
}