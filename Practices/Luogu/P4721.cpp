// P4721.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4e5 + 200, mod = 998244353, G = 3, Gi = 332748118;

int n, g[MAX_N], f[MAX_N], poly_siz, poly_bit, rev[MAX_N];
int A[MAX_N], B[MAX_N];

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
                arr[k + step] = (1LL * arr[k] + mod - t) % mod;
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

void solve(int l, int r)
{
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    solve(l, mid);

    int len = (r - l - 1);
    poly_siz = poly_bit = 0;
    while ((1 << poly_bit) <= len)
        poly_bit++;
    poly_siz = (1 << poly_bit);
    for (int i = 0; i < poly_siz; i++)
    {
        rev[i] = ((rev[i >> 1] >> 1) | ((i & 1) << (poly_bit - 1)));
        A[i] = B[i] = 0;
    }

    for (int i = l; i <= mid; i++)
        A[i - l] = f[i];
    for (int i = 1; i <= r - l; i++)
        B[i - 1] = g[i];
    ntt(A, 1), ntt(B, 1);
    for (int i = 0; i < poly_siz; i++)
        A[i] = 1LL * A[i] * B[i] % mod;
    ntt(A, -1);
    for (int i = mid + 1; i <= r; i++)
        f[i] = (1LL * f[i] + A[i - l - 1]) % mod;
    solve(mid + 1, 1LL * r);
}

int main()
{
    scanf("%d", &n), f[0] = 1;
    for (int i = 1; i <= n - 1; i++)
        scanf("%d", &g[i]);
    solve(0, n - 1);
    for (int i = 0; i < n; i++)
        printf("%d ", f[i]);
    return 0;
}