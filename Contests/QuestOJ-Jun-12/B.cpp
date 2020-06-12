// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4e5 + 200, mod = 998244353, G = 3;

int n, pk, ai[MAX_N], rev[MAX_N], poly_siz, poly_bit, poly[40][MAX_N];

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

const int invG = fpow(G, mod - 2);

void ntt_prepare(int len)
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
        int omega_n = fpow(dft == 1 ? G : invG, (mod - 1) / (step << 1));
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

void solve(int l, int r, int dep)
{
    if (l == r)
        return (void)(poly[dep][0] = 1, poly[dep][1] = ai[l] % mod);
    int mid = (l + r) >> 1;
    solve(l, mid, dep + 1), solve(mid + 1, r, dep + 2);
    int lft = mid - l + 1, rig = r - mid;
    ntt_prepare(lft + rig), ntt_initialize();
    for (int i = lft + 1; i < poly_siz; i++)
        poly[dep + 1][i] = 0;
    for (int i = rig + 1; i < poly_siz; i++)
        poly[dep + 2][i] = 0;
    ntt(poly[dep + 1], 1), ntt(poly[dep + 2], 1);
    for (int i = 0; i < poly_siz; i++)
        poly[dep][i] = 1LL * poly[dep + 1][i] * poly[dep + 2][i] % mod;
    ntt(poly[dep], -1);
}

int main()
{
    scanf("%d%d", &n, &pk);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    solve(1, n, 0);
    int ans = 0, coeff = 1, inv = fpow(n, mod - 2);
    for (int i = n; i >= 0; i--)
    {
        ans = (0LL + ans + 1LL * coeff * poly[0][i] % mod) % mod;
        coeff = 1LL * coeff * (mod - 1) % mod * (pk - (n - i) + mod) % mod * inv % mod;
    }
    printf("%lld\n", (0LL + poly[0][n] + mod - ans) % mod);
    return 0;
}
