// BZ2138.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 401000, INF = 0x3f3f3f3f;

int n, m, ai[MAX_N], li[MAX_N], ri[MAX_N], ki[MAX_N], nodes[MAX_N << 2][2], tag[MAX_N << 2][2], aff[MAX_N];
int pa[MAX_N], org[2][MAX_N], bi[MAX_N], ord[MAX_N];

struct segment
{
    int l, r, id;
    bool operator<(const segment &rhs) const { return l < rhs.l; }
} segs[MAX_N];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

// SegmentTree;

int conclude(int idx, int a, int b) { return idx ? max(a, b) : min(a, b); }

void pushdown(int p, int idx)
{
    if (tag[p][idx])
    {
        nodes[lson][idx] += tag[p][idx], nodes[rson][idx] += tag[p][idx];
        tag[lson][idx] += tag[p][idx], tag[rson][idx] += tag[p][idx], tag[p][idx] = 0;
    }
}

void pushup(int p, int idx) { nodes[p][idx] = conclude(idx, nodes[lson][idx], nodes[rson][idx]); }

void build(int l, int r, int p, int idx)
{
    if (l == r)
        return (void)(nodes[p][idx] = org[idx][l]);
    build(l, mid, lson, idx), build(mid + 1, r, rson, idx);
    pushup(p, idx);
}

void update(int ql, int qr, int l, int r, int p, int idx, int val)
{
    if (ql <= l && r <= qr)
        return (void)(tag[p][idx] += val, nodes[p][idx] += val);
    pushdown(p, idx);
    if (ql <= mid)
        update(ql, qr, l, mid, lson, idx, val);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, idx, val);
    pushup(p, idx);
}

int query(int ql, int qr, int l, int r, int p, int idx)
{
    if (ql <= l && r <= qr)
        return nodes[p][idx];
    pushdown(p, idx);
    int ret = -INF + 2 * (1 - idx) * INF;
    if (ql <= mid)
        ret = conclude(idx, ret, query(ql, qr, l, mid, lson, idx));
    if (mid < qr)
        ret = conclude(idx, ret, query(ql, qr, mid + 1, r, rson, idx));
    return ret;
}

int main()
{
    int x, y, z, P;
    scanf("%d%d%d%d%d", &n, &x, &y, &z, &P);
    for (int i = 1; i <= n; i++)
        ai[i] = (1LL * (i - x) * (i - x) % P + 1LL * (i - y) * (i - y) % P + 1LL * (i - z) * (i - z) % P) % P;
    scanf("%d", &m);
    if (m == 0)
        return 0;
    scanf("%d%d%d%d%d%d", &ki[1], &ki[2], &x, &y, &z, &P);
    for (int i = 3; i <= m; i++)
        ki[i] = (1LL * x * ki[i - 1] % P + 1LL * y * ki[i - 2] % P + z) % P;
    for (int i = 1; i <= m; i++)
        scanf("%d%d", &segs[i].l, &segs[i].r), segs[i].id = i;
    sort(segs + 1, segs + 1 + m);
    for (int i = 1, ptr = n = 0; i <= m; i++)
    {
        for (ptr = max(ptr, segs[i].l); ptr <= segs[i].r; ptr++)
            ai[++n] = ai[ptr], aff[ptr] = n;
        li[segs[i].id] = aff[segs[i].l], ri[segs[i].id] = aff[segs[i].r], ord[segs[i].id] = i;
    }
    for (int i = 1; i <= n; i++)
        pa[i] = pa[i - 1] + ai[i];
    for (int i = 1; i <= m; i++)
        org[1][ord[i]] = -pa[ri[i]];
    for (int i = 1; i <= m; i++)
        org[0][ord[i]] = -pa[li[i] - 1];
    build(1, m, 1, 0), build(1, m, 1, 1);
    for (int i = 1; i <= m; i++)
    {
        int u = ord[i], rig = query(1, u, 1, m, 1, 0), lft = query(u, m, 1, m, 1, 1);
        ki[i] = min(ki[i], rig - lft), printf("%d\n", ki[i]);
        update(u, m, 1, m, 1, 1, ki[i]);
        if (u != m)
            update(u + 1, m, 1, m, 1, 0, ki[i]);
    }
    return 0;
}