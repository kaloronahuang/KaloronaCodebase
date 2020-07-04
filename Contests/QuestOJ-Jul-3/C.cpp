// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 8e5 + 200, mod = 998244353, g = 3;

int n, m, ai[MAX_N], bi[MAX_N], ci[MAX_N], rev[MAX_N], poly_bit, poly_siz, A[MAX_N], B[MAX_N], ansBox[4][MAX_N];
long long ans[4];

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

const int gInv = fpow(g, mod - 2);

void ntt_prepare(int len)
{
    poly_bit = 0, poly_siz = 1;
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
        int omega_n = fpow(dft == 1 ? g : gInv, (mod - 1) / (step << 1));
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

void solve(int *res, int typ)
{
    for (int i = 0; i < poly_siz; i++)
        A[i] = B[i] = 0;
    for (int i = 0; i < n; i++)
        if ((ai[i] & typ) == ai[i])
            A[i] = 1;
    for (int i = 0; i < n; i++)
        if ((bi[i] & typ) == bi[i])
            B[i] = 1;
    ntt(A, 1), ntt(B, 1);
    for (int i = 0; i < poly_siz; i++)
        A[i] = 1LL * A[i] * B[i] % mod;
    ntt(A, -1);
    for (int i = 0; i < (n << 1) - 1; i++)
        if ((ci[i] & typ) == ci[i])
            res[i] = A[i];
        else
            res[i] = 0;
}

int main()
{
    scanf("%d%d", &n, &m);
    ntt_prepare((n << 1) - 1), ntt_initialize();
    while (m--)
    {
        int typ, pos, col;
        scanf("%d%d%d", &typ, &pos, &col);
        if (typ == 1)
            ai[pos - 1] |= 1 << col;
        else if (typ == 2)
            bi[pos - 1] |= 1 << col;
        else
            ci[pos - 2] |= 1 << col;
    }
    for (int i = 0; i < 4; i++)
        solve(ansBox[i], i);
    for (int i = 0; i < 2 * n - 1; i++)
    {
        ans[0] += ansBox[0][i];
        ans[1] += ansBox[1][i] - ansBox[0][i];
        ans[2] += ansBox[2][i] - ansBox[0][i];
        ans[3] += ansBox[3][i] - ansBox[1][i] - ansBox[2][i] + ansBox[0][i];
    }
    for (int i = 0; i < 4; i++)
        printf("%lld ", ans[i]);
    puts("");
    return 0;
}