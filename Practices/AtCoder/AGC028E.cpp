// AGC028E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, INF = 0x3f3f3f3f;

int n, pi[MAX_N], tag[MAX_N], suf[MAX_N];
char str[MAX_N];

struct SegmentTree
{

    int nodes[MAX_N << 2];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

    void build(int l, int r, int p)
    {
        if (l == r)
            return (void)(nodes[p] = -INF + 1);
        build(l, mid, lson), build(mid + 1, r, rson);
        nodes[p] = max(nodes[lson], nodes[rson]);
    }

    void update(int qx, int l, int r, int p, int val)
    {
        if (l == r)
            return (void)(nodes[p] = val);
        if (qx <= mid)
            update(qx, l, mid, lson, val);
        else
            update(qx, mid + 1, r, rson, val);
        nodes[p] = max(nodes[lson], nodes[rson]);
    }

    int query(int ql, int qr, int l, int r, int p)
    {
        if (ql <= l && r <= qr)
            return nodes[p];
        int ret = -INF;
        if (ql <= mid)
            ret = max(ret, query(ql, qr, l, mid, lson));
        if (mid < qr)
            ret = max(ret, query(ql, qr, mid + 1, r, rson));
        return ret;
    }

#undef mid
#undef rson
#undef lson

} tr[2];

bool check(int max_val, int const_term)
{
    if (const_term < 0)
        return false;
    if (const_term & 1)
        return tr[1].query(max_val, n, 1, n, 1) >= const_term;
    else
        return tr[0].query(max_val, n, 1, n, 1) >= const_term;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1, pre_max = 0; i <= n; i++)
    {
        scanf("%d", &pi[i]), tag[i] = 1;
        if (pi[i] > pre_max)
            pre_max = pi[i], tag[i] = 2;
    }
    tr[1].build(1, n, 1);
    for (int i = n; i >= 1; i--)
    {
        int max_val[2] = {tr[0].query(pi[i], n, 1, n, 1), tr[1].query(pi[i], n, 1, n, 1)};
        tr[1].update(pi[i], 1, n, 1, tag[i] + max_val[!(tag[i] & 1)]), tr[0].update(pi[i], 1, n, 1, tag[i] + max_val[(tag[i] & 1)]);
    }
    for (int i = n; i >= 1; i--)
        suf[i] = suf[i + 1] + tag[i] - 1;
    int cntX = 0, cntY = 0, maxX = 0, maxY = 0;
    for (int i = 1; i <= n; i++)
    {
        tr[1].update(pi[i], 1, n, 1, 1 - INF), tr[0].update(pi[i], 1, n, 1, 0);
        if (check(maxY, cntX + suf[i + 1] - cntY + (pi[i] > maxX)))
            str[i] = '0', cntX += pi[i] > maxX, maxX = max(maxX, pi[i]);
        else if (check(max(maxX, pi[i]), cntY + suf[i + 1] - cntX - (pi[i] > maxX)))
            str[i] = '0', cntX += pi[i] > maxX, maxX = max(maxX, pi[i]);
        else
            str[i] = '1', cntY += pi[i] > maxY, maxY = max(maxY, pi[i]);
    }
    if (cntX != cntY)
        puts("-1");
    else
        printf("%s\n", str + 1);
    return 0;
}