// CF1218E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4e4 + 200, mod = 998244353, G = 3;

int n, k, ai[MAX_N], qtot, rev[MAX_N], tmp[MAX_N];

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

const int Gi = quick_pow(G, mod - 2), inv2 = quick_pow(2, mod - 2);

void ntt(vector<int> &arr, int dft, int poly_siz, int poly_bit)
{
    for (int i = 0; i < poly_siz; i++)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (poly_bit - 1));
    for (int step = 1; step < poly_siz; step <<= 1)
    {
        int omega_n = quick_pow(dft == 1 ? G : Gi, (mod - 1) / (step << 1));
        for (int j = 0; j < poly_siz; j += (step << 1))
        {
            int omega_nk = 1;
            for (int k = j; k < j + step; k++, omega_nk = 1LL * omega_nk * omega_n % mod)
            {
                int t = 1LL * arr[k + step] * omega_nk % mod;
                arr[k + step] = (1LL * arr[k] + mod - t) % mod;
                arr[k] = (1LL * arr[k] + t) % mod;
            }
        }
    }
    int inv = quick_pow(poly_siz, mod - 2);
    if (dft == -1)
        for (int i = 0; i < poly_siz; i++)
            arr[i] = 1LL * arr[i] * inv % mod;
}

vector<int> polyMultiply(vector<int> &polyA, vector<int> &polyB)
{
    int cntA = polyA.size(), cntB = polyB.size(), tot_len = (max(cntA, cntB) << 1), poly_bit = 0;
    while ((1 << poly_bit) <= tot_len)
        poly_bit++;
    int poly_siz = 1 << poly_bit;
    vector<int> A(poly_siz, 0), B(poly_siz, 0);
    for (int i = 0; i < cntA; i++)
        A[i] = polyA[i];
    for (int i = 0; i < cntB; i++)
        B[i] = polyB[i];
    ntt(A, 1, poly_siz, poly_bit), ntt(B, 1, poly_siz, poly_bit);
    for (int i = 0; i < poly_siz; i++)
        A[i] = 1LL * A[i] * B[i] % mod;
    ntt(A, -1, poly_siz, poly_bit);
    
    return A;
}

vector<int> solve(int l, int r)
{
    if (l == r)
        return vector<int>{1, ai[l]};
    int mid = (l + r) >> 1;
    vector<int> lPoly = solve(l, mid), rPoly = solve(mid + 1, r);
    return polyMultiply(lPoly, rPoly);
}

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++)
        scanf("%d", &ai[i]);
    memcpy(tmp, ai, sizeof(tmp));
    scanf("%d", &qtot);
    while (qtot--)
    {
        int opt, a, l, r, d;
        scanf("%d%d%d%d", &opt, &a, &l, &r);
        if (opt == 1)
        {
            l--, ai[l] = r;
            for (int i = 0; i < n; i++)
                ai[i] = (0LL + a + mod - ai[i]) % mod;
        }
        else
        {
            scanf("%d", &d), l--, r--;
            for (int i = l; i <= r; i++)
                ai[i] = (0LL + a + mod - 0LL + (0LL + ai[i] + d) % mod) % mod;
        }
        vector<int> ans = solve(0, n - 1);
        memcpy(ai, tmp, sizeof(tmp));
        printf("%d\n", ans[k]);
    }
    return 0;
}