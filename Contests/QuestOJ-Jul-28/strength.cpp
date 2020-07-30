// strength.cpp
#include <bits/stdc++.h>

using namespace std;

typedef vector<int> poly;

const int MAX_N = 1e5 + 200, mod = 998244353, G = 3;

int poly_siz, poly_bit, rev[MAX_N << 2], pi[MAX_N], ansBox[MAX_N], n, ai[MAX_N];
poly nodes[MAX_N << 2], pols[MAX_N << 2];

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
    poly_bit = 0, poly_siz = 1;
    while (poly_siz <= len)
        poly_siz <<= 1, poly_bit++;
}

void ntt_initialize()
{
    for (int i = 0; i < poly_siz; i++)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (poly_bit - 1));
}

void ntt(poly &arr, int dft)
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

poly multiply(poly a, poly b)
{
    int lft = a.size(), rig = b.size();
    ntt_prepare(lft + rig - 1), ntt_initialize();
    a.resize(poly_siz), b.resize(poly_siz);
    ntt(a, 1), ntt(b, 1);
    for (int i = 0; i < poly_siz; i++)
        a[i] = 1LL * a[i] * b[i] % mod;
    ntt(a, -1), a.resize(lft + rig - 1);
    return a;
}

poly rev_multiply(poly a, poly b)
{
    int lft = a.size(), rig = b.size();
    reverse(b.begin(), b.end());
    poly res = multiply(a, b), ret;
    ret.resize(lft - rig + 1);
    for (int i = 0; i <= lft - rig; i++)
        ret[i] = res[rig - 1 + i];
    return ret;
}

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void build(int l, int r, int p)
{
    if (l == r)
        return (void)(nodes[p] = poly{int((mod + 1LL - pi[l]) % mod), pi[l]});
    build(l, mid, lson), build(mid + 1, r, rson);
    nodes[p] = multiply(nodes[lson], nodes[rson]);
}

void update(int l, int r, int p)
{
    if (l == r)
        return (void)(ansBox[l] = pols[p][0]);
    pols[lson] = rev_multiply(pols[p], nodes[rson]);
    pols[rson] = rev_multiply(pols[p], nodes[lson]);
    update(l, mid, lson), update(mid + 1, r, rson);
}

int main()
{
    scanf("%d", &n);
    poly res = multiply(poly{2, 3}, poly{2, 3});
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    for (int i = 1, x, y; i <= n; i++)
        scanf("%d%d", &x, &y), pi[i] = 1LL * x * fpow(y, mod - 2) % mod;
    build(1, n, 1);
    for (int i = 1; i <= n; i++)
        pols[1].push_back(ai[i]);
    update(1, n, 1);
    for (int i = 1; i <= n; i++)
        printf("%d ", ansBox[i]);
    puts("");
    return 0;
}