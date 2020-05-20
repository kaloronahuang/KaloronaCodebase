// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 8e5 + 200, mod = 998244353;

int T, poly_siz, poly_bit, rev[MAX_N], A[MAX_N], tmp[10][MAX_N], ans[MAX_N];

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

const int G = 3, Gi = fpow(G, mod - 2), inv3 = fpow(3, mod - 2), inv2 = fpow(2, mod - 2), inv6 = 1LL * inv2 * inv3 % mod;
const int inv4 = fpow(4, mod - 2), inv8 = fpow(8, mod - 2), inv24 = 1LL * inv4 * inv6 % mod;

void ntt_prepare(int limit)
{
    poly_bit = 0, poly_siz = 1;
    while (limit >= poly_siz)
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
        return (void)(A[l] = (0LL + A[l] + 1LL * (l % 3 == 1) * (1LL * A[l / 3] * inv3 % mod)) % mod);
    int mid = (l + r) >> 1, len = ((r - l + 1) << 1) + (mid - l + 1);
    solve(l, mid), ntt_prepare(len), ntt_initialize();
    for (int i = 0; i < poly_siz; i++)
        tmp[0][i] = (l + i <= mid) * A[l + i], tmp[1][i] = (i <= r - l) * A[i], tmp[2][i] = (i <= r - l && (i % 2 == 0)) * A[i >> 1];
    ntt(tmp[0], 1), ntt(tmp[1], 1), ntt(tmp[2], 1);
    for (int i = 0; i < poly_siz; i++)
        tmp[0][i] = (1LL * tmp[0][i] * tmp[1][i] % mod * tmp[1][i] % mod * (l ? inv2 : inv6) % mod + 1LL * tmp[0][i] * tmp[2][i] % mod * inv2 % mod) % mod;
    ntt(tmp[0], -1);
    for (int i = mid + 1; i <= r; i++)
        A[i] = (0LL + A[i] + tmp[0][i - l - 1]) % mod;
    solve(mid + 1, r);
}

int main()
{
    A[0] = 1, solve(0, 1e5), ntt_prepare(5e5), ntt_initialize();
    for (int i = 0; i < poly_siz; i++)
        tmp[2][i] = (i % 2 == 0) * A[i >> 1], tmp[3][i] = (i % 3 == 0) * A[i / 3];
    for (int i = 0; i <= (1e5) / 4; i++)
        ans[4 * i + 1] = 1LL * A[i] * inv4 % mod;
    for (int i = 0; i <= (1e5) / 2; i++)
        ans[i << 1] = A[i];
    ntt(A, 1), ntt(tmp[2], 1), ntt(tmp[3], 1);
    for (int i = 0; i < poly_siz; i++)
        tmp[0][i] = (1LL * tmp[2][i] * tmp[2][i] % mod * inv8 % mod + 1LL * A[i] * A[i] % mod * tmp[2][i] % mod * inv4 % mod +
                     1LL * A[i] * tmp[3][i] % mod * inv3 % mod + 1LL * A[i] * A[i] % mod * A[i] % mod * A[i] % mod * inv24 % mod) %
                    mod;
    ntt(tmp[0], -1);
    for (int i = 0; i < 1e5; i++)
        ans[i + 1] = (0LL + ans[i + 1] + tmp[0][i]) % mod;
    for (int i = 0; i < poly_siz; i++)
        tmp[0][i] = (1LL * A[i] * A[i] % mod * inv2 % mod + 1LL * tmp[2][i] * inv2 % mod + mod - A[i]) % mod;
    ntt(tmp[0], -1);
    for (int i = 0; i <= 1e5; i++)
        ans[i] = (0LL + ans[i] + mod - tmp[0][i]) % mod;
    scanf("%d", &T);
    while (T--)
    {
        int n;
        scanf("%d", &n), printf("%d\n", ans[n]);
    }
    return 0;
}