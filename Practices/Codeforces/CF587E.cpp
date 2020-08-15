// CF587E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, q, ai[MAX_N], bi[MAX_N];

struct Basis
{
    int base[40];
    void clear() { memset(base, 0, sizeof(base)); }
    void update(int x)
    {
        for (int i = 31; i >= 0; i--)
            if ((x & (1 << i)))
                if (base[i])
                    x ^= base[i];
                else
                    return (void)(base[i] = x);
    }
    int query()
    {
        int ret = 0;
        for (int i = 31; i >= 0; i--)
            if (base[i])
                ret++;
        return (1 << ret);
    }
    void merge(Basis src)
    {
        for (int i = 31; i >= 0; i--)
            if (src.base[i])
                update(src.base[i]);
    }
};

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

namespace BasisSGT
{

    Basis nodes[MAX_N << 2];

    void pushup(int p) { nodes[p].clear(), nodes[p].merge(nodes[lson]), nodes[p].merge(nodes[rson]); }

    void build(int l, int r, int p)
    {
        if (l == r)
            return (void)(nodes[p].clear(), nodes[p].update(bi[l]));
        build(l, mid, lson), build(mid + 1, r, rson), pushup(p);
    }

    void update(int qx, int l, int r, int p, int val)
    {
        if (l == r)
            return (void)(nodes[p].clear(), nodes[p].update(val));
        if (qx <= mid)
            update(qx, l, mid, lson, val);
        else
            update(qx, mid + 1, r, rson, val);
        pushup(p);
    }

    Basis query(int ql, int qr, int l, int r, int p)
    {
        if (ql <= l && r <= qr)
            return nodes[p];
        Basis ret;
        ret.clear();
        if (ql <= mid)
            ret.merge(query(ql, qr, l, mid, lson));
        if (mid < qr)
            ret.merge(query(ql, qr, mid + 1, r, rson));
        return ret;
    }

} // namespace BasisSGT

namespace XorSGT
{

    int nodes[MAX_N << 2], tag[MAX_N << 2];

    void modify(int p, int val) { nodes[p] ^= val, tag[p] ^= val; }

    void pushdown(int p)
    {
        if (tag[p] != 0)
            modify(lson, tag[p]), modify(rson, tag[p]), tag[p] = 0;
    }

    void build(int l, int r, int p)
    {
        if (l == r)
            return (void)(nodes[p] = ai[l]);
        build(l, mid, lson), build(mid + 1, r, rson);
    }

    void update(int ql, int qr, int l, int r, int p, int val)
    {
        if (ql <= l && r <= qr)
            return (void)(modify(p, val));
        pushdown(p);
        if (ql <= mid)
            update(ql, qr, l, mid, lson, val);
        if (mid < qr)
            update(ql, qr, mid + 1, r, rson, val);
    }

    int query(int qx, int l, int r, int p)
    {
        if (l == r)
            return nodes[p];
        pushdown(p);
        if (qx <= mid)
            return query(qx, l, mid, lson);
        else
            return query(qx, mid + 1, r, rson);
    }

} // namespace XorSGT

#undef mid
#undef rson
#undef lson

int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), bi[i] = ai[i - 1] ^ ai[i];
    BasisSGT::build(1, n, 1), XorSGT::build(1, n, 1);
    while (q--)
    {
        int opt, l, r, val;
        scanf("%d%d%d", &opt, &l, &r);
        if (opt == 1)
        {
            scanf("%d", &val);
            XorSGT::update(l, r, 1, n, 1, val);
            if (r != n)
                BasisSGT::update(r + 1, 1, n, 1, bi[r + 1] ^= val);
            BasisSGT::update(l, 1, n, 1, bi[l] ^= val);
        }
        else
        {
            Basis curt;
            curt.clear(), curt.update(XorSGT::query(l, 1, n, 1));
            if (l != r)
                curt.merge(BasisSGT::query(l + 1, r, 1, n, 1));
            printf("%d\n", curt.query());
        }
    }
    return 0;
}