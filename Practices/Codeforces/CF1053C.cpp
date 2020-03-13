// CF1053C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, mod = 1e9 + 7;

typedef long long ll;

int n, q, ai[MAX_N], bi[MAX_N], wi[MAX_N];
ll sum[MAX_N << 2], diff[MAX_N << 2];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

// segment tree;

void pushup(int p) { sum[p] = sum[lson] + sum[rson], diff[p] = (diff[lson] + diff[rson]) % mod; }

void build(int l, int r, int p)
{
    if (l == r)
    {
        sum[p] = wi[l], diff[p] = 1LL * wi[l] * bi[l];
        return;
    }
    build(l, mid, lson), build(mid + 1, r, rson);
    pushup(p);
}

void update(int qx, int l, int r, int p)
{
    if (l == r)
    {
        sum[p] = wi[l], diff[p] = 1LL * wi[l] * bi[l];
        return;
    }
    if (qx <= mid)
        update(qx, l, mid, lson);
    else
        update(qx, mid + 1, r, rson);
    pushup(p);
}

ll query(int ql, int qr, int l, int r, int p, ll *nodes, bool opt = false)
{
    if (ql > qr)
        return 0;
    if (ql <= l && r <= qr)
        return nodes[p];
    ll ret = 0;
    if (ql <= mid)
        ret += query(ql, qr, l, mid, lson, nodes);
    if (mid < qr)
        ret += query(ql, qr, mid + 1, r, rson, nodes);
    if (opt)
        ret %= mod;
    return ret;
}

#undef mid

int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), bi[i] = ai[i] - i;
    for (int i = 1; i <= n; i++)
        scanf("%d", &wi[i]);
    build(1, n, 1);
    while (q--)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        if (l < 0)
            l = -l, wi[l] = r, update(l, 1, n, 1);
        else
        {
            int lb = l, rb = r, res = l;
            while (lb <= rb)
            {
                int mid = (lb + rb) >> 1;
                if (query(l, mid, 1, n, 1, sum) >= query(mid + 1, r, 1, n, 1, sum))
                    res = mid, rb = mid - 1;
                else
                    lb = mid + 1;
            }
            ll part1 = (1LL * query(l, res - 1, 1, n, 1, sum, true) * (ai[res] - res) % mod + mod - query(l, res - 1, 1, n, 1, diff, true)) % mod;
            ll part2 = (1LL * query(res + 1, r, 1, n, 1, sum, true) * (res + mod - ai[res]) % mod + query(res + 1, r, 1, n, 1, diff, true)) % mod;
            printf("%lld\n", (0LL + part1 + part2) % mod);
        }
    }
    return 0;
}