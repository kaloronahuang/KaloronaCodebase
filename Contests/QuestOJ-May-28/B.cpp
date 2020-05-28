// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200, mod = 1e9 + 7, RANGE = 3e5;

typedef long long ll;
typedef pair<int, int> pii;

int n, m, ki[MAX_N], weights[MAX_N], ai[MAX_N], pres[2][MAX_N];

struct tup
{
    int pos, val;
    bool operator<(const tup &rhs) const { return val < rhs.val || (val == rhs.val && pos > rhs.pos); }
} tps[MAX_N];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

namespace seg1
{

    int nodes[MAX_N << 2], tag[MAX_N << 2];

    void build(int l, int r, int p)
    {
        tag[p] = 1, nodes[p] = 0;
        if (l == r)
            return;
        build(l, mid, lson), build(mid + 1, r, rson);
        nodes[p] = (0LL + nodes[lson] + nodes[rson]) % mod;
    }

    void modify(int p, int x) { nodes[p] = 1LL * nodes[p] * x % mod, tag[p] = 1LL * tag[p] * x % mod; }

    void pushdown(int p)
    {
        if (tag[p] != 1)
            modify(lson, tag[p]), modify(rson, tag[p]), tag[p] = 1;
    }

    void updateMultiply(int ql, int qr, int l, int r, int p, int val)
    {
        if (ql <= l && r <= qr)
            return (void)(modify(p, val));
        pushdown(p);
        if (ql <= mid)
            updateMultiply(ql, qr, l, mid, lson, val);
        if (mid < qr)
            updateMultiply(ql, qr, mid + 1, r, rson, val);
        nodes[p] = (0LL + nodes[lson] + nodes[rson]) % mod;
    }

    int query(int ql, int qr, int l, int r, int p)
    {
        if (ql <= l && r <= qr)
            return nodes[p];
        pushdown(p);
        int ret = 0;
        if (ql <= mid)
            ret = (0LL + ret + query(ql, qr, l, mid, lson)) % mod;
        if (mid < qr)
            ret = (0LL + ret + query(ql, qr, mid + 1, r, rson)) % mod;
        return ret;
    }

    void updateAdd(int qx, int l, int r, int p, int val)
    {
        if (l == r)
            return (void)(nodes[p] = (0LL + nodes[p] + val) % mod);
        pushdown(p);
        if (qx <= mid)
            updateAdd(qx, l, mid, lson, val);
        else
            updateAdd(qx, mid + 1, r, rson, val);
        nodes[p] = (0LL + nodes[lson] + nodes[rson]) % mod;
    }

} // namespace seg1

namespace seg2
{

    int nodes[MAX_N << 2], siz[MAX_N << 2];

    void pushup(int p) { siz[p] = (0LL + siz[lson] + siz[rson]) % mod, nodes[p] = (0LL + nodes[rson] + 1LL * ki[siz[rson]] * nodes[lson] % mod) % mod; }

    void build(int l, int r, int p)
    {
        if (l == r)
            return (void)(nodes[p] = 1, siz[p] = 0);
        build(l, mid, lson), build(mid + 1, r, rson);
        pushup(p);
    }

    void update(int qx, int l, int r, int p)
    {
        if (l == r)
            return (void)(nodes[p] = 1LL * nodes[p] * ki[1] % mod, siz[p]++);
        if (qx <= mid)
            update(qx, l, mid, lson);
        else
            update(qx, mid + 1, r, rson);
        pushup(p);
    }

    pii query(int ql, int qr, int l, int r, int p)
    {
        if (ql <= l && r <= qr)
            return make_pair(siz[p], nodes[p]);
        if (qr <= mid)
            return query(ql, qr, l, mid, lson);
        else if (mid < ql)
            return query(ql, qr, mid + 1, r, rson);
        {
            pii lft = query(ql, qr, l, mid, lson);
            pii rig = query(ql, qr, mid + 1, r, rson);
            return make_pair(lft.first + rig.first, (0LL + rig.second + 1LL * lft.second * ki[rig.first] % mod) % mod);
        }
    }

} // namespace seg2

void solve(int *arr)
{
    for (int i = 1; i <= n; i++)
        tps[i] = tup{i, ai[i]};
    sort(tps + 1, tps + 1 + n);
    seg2::build(1, n, 1);
    for (int i = 1; i <= n; i++)
        seg2::update(tps[i].pos, 1, n, 1), weights[tps[i].pos] = 1LL * seg2::query(1, tps[i].pos, 1, n, 1).second * tps[i].val % mod;
    seg1::build(1, RANGE, 1);
    for (int i = 1; i <= n; i++)
    {
        int v = weights[i];
        seg1::updateMultiply(ai[i], RANGE, 1, RANGE, 1, ki[1]);
        seg1::updateAdd(ai[i], 1, RANGE, 1, v);
        arr[i] = (0LL + arr[i - 1] + seg1::nodes[1]) % mod;
    }
}

int main()
{
    scanf("%d%d%d", &n, &m, &ki[1]), ki[0] = 1;
    for (int i = 2; i <= n; i++)
        ki[i] = 1LL * ki[i - 1] * ki[1] % mod;
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    solve(pres[0]);
    reverse(ai + 1, ai + 1 + n);
    solve(pres[1]);
    reverse(pres[1] + 1, pres[1] + 1 + n);
    while (m--)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%lld\n", (0LL + pres[0][n] + mod - pres[0][l - 1] + mod - pres[1][r + 1]) % mod);
    }
    return 0;
}