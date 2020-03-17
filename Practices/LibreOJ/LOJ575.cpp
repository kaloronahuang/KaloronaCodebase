// LOJ575.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4e5 + 200, mod = 998244353, G = 3;

int n, poly_siz, poly_bit, rev[MAX_N], pre[MAX_N], fac[MAX_N], fac_inv[MAX_N], f[MAX_N], g[MAX_N], A[MAX_N], B[MAX_N];
char opt[MAX_N];

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

void ntt_prep(int len)
{
    poly_siz = 1, poly_bit = 0;
    while (poly_siz <= len)
        poly_siz <<= 1, poly_bit++;
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
        int omega_n = fpow(dft == 1 ? G : Gi, (mod - 1) / (step << 1));
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

void solve(int l, int r)
{
    if (l == r)
    {
        if (l == 0)
            f[0] = 1;
        else
            f[l] = (pre[l - 1] & 1) ? (mod - f[l]) % mod : f[l];
        if (opt[l] == '>' || l == 0)
            g[l] = (pre[l] & 1) ? (mod - f[l]) % mod : f[l];
        return;
    }
    int mid = (l + r) >> 1;
    solve(l, mid);
    int lft_len = mid - l + 1, rig_len = r - l;
    ntt_prep(lft_len + rig_len - 1), ntt_initialize();
    for (int i = 0; i < lft_len; i++)
        A[i] = g[i + l];
    for (int i = lft_len; i < poly_siz; i++)
        A[i] = 0;
    for (int i = 0; i < rig_len; i++)
        B[i] = fac_inv[i + 1];
    for (int i = rig_len; i < rig_len; i++)
        B[i] = 0;
    ntt(A, 1), ntt(B, 1);
    for (int i = 0; i < poly_siz; i++)
        A[i] = 1LL * A[i] * B[i] % mod;
    ntt(A, -1);
    for (int i = mid + 1; i <= r; i++)
        f[i] = (0LL + A[i - l - 1] + f[i]) % mod;
    solve(mid + 1, r);
}

int main()
{
    scanf("%s", opt + 1), n = strlen(opt + 1) + 1;
    for (int i = 1; i <= n; i++)
        pre[i] = pre[i - 1] + (opt[i] == '>');
    for (int i = fac[0] = 1; i <= n; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    fac_inv[n] = fpow(fac[n], mod - 2);
    for (int i = n - 1; i >= 0; i--)
        fac_inv[i] = 1LL * fac_inv[i + 1] * (i + 1) % mod;
    solve(0, n);
    printf("%lld\n", 1LL * f[n] * fac[n] % mod);
    return 0;
}