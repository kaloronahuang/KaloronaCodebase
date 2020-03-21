// UOJ50.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 8e5 + 200, mod = 998244353, G = 3;

int n, rev[MAX_N], poly_bit, poly_siz, f[MAX_N], fac[MAX_N], fac_inv[MAX_N], inv[MAX_N], A[MAX_N], B[MAX_N], g[MAX_N];
char str[MAX_N];

int check(int pos) { return str[pos] == '1'; }

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

void initialize()
{
    for (int i = fac[0] = 1; i <= n; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    fac_inv[n] = fpow(fac[n], mod - 2);
    for (int i = n - 1; i >= 0; i--)
        fac_inv[i] = 1LL * fac_inv[i + 1] * (i + 1) % mod;
    inv[0] = inv[1] = 1;
    for (int i = 2; i <= n; i++)
        inv[i] = 1LL * inv[mod % i] * (mod - mod / i) % mod;
}

void ntt_prep(int siz)
{
    poly_siz = 1, poly_bit = 0;
    while (poly_siz <= siz)
        poly_siz <<= 1, poly_bit++;
}

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

void solve(int l, int r)
{
    if (l == r)
    {
        if (l == 1)
            f[l] = 1;
        else
            f[l] = 1LL * inv[2] * f[l] % mod * fac[l - 1] % mod;
        return;
    }
    int mid = (l + r) >> 1;
    solve(l, mid);
    ntt_prep(mid - l + 1 + r - l), ntt_initialize();
    for (int i = l; i <= mid; i++)
        A[i - l] = g[i];
    for (int i = 0; i <= r - l; i++)
        B[i] = 1LL * check(i) * fac_inv[i] % mod;
    ntt(A, 1), ntt(B, 1);
    for (int i = 0; i < poly_siz; i++)
        A[i] = 1LL * A[i] * B[i] % mod;
    ntt(A, -1);
    for (int i = mid + 1; i <= r; i++)
        f[i] = (0LL + f[i] + A[i - l - 1]) % mod;
    for (int i = 0; i < poly_siz; i++)
        A[i] = B[i] = 0;
    for (int i = l; i <= mid; i++)
        A[i - l] = 1LL * f[i] * fac_inv[i] % mod;
    for (int i = 0; i <= r - l; i++)
        if (i < l)
            B[i] = 2LL * f[i] * fac_inv[i] % mod;
        else if (i <= mid)
            B[i] = 1LL * f[i] * fac_inv[i] % mod;
    ntt(A, 1), ntt(B, 1);
    for (int i = 0; i < poly_siz; i++)
        A[i] = 1LL * A[i] * B[i] % mod;
    ntt(A, -1);
    for (int i = mid + 1; i <= r; i++)
        g[i] = (0LL + g[i] + A[i - l]) % mod;
    for (int i = 0; i < poly_siz; i++)
        A[i] = B[i] = 0;
    solve(mid + 1, r);
}

int main()
{
    scanf("%d%s", &n, str), initialize();
    f[1] = 1, solve(1, n);
    for (int i = 1; i <= n; i++)
        printf("%d\n", f[i]);
    return 0;
}