// lover.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 1e5 + 200;

int n, m, ftot, mem[MAX_N];

struct frame
{
    int x, l, r, w;
};
vector<frame> frames[MAX_N];

struct node
{
    ll val;
    int id;
} nodes[MAX_N << 2][2], pending[MAX_N];
node infty = node{ll(1e18), 0};
ll tags[MAX_N << 2];

int find(int x) { return mem[x] == x ? x : mem[x] = find(mem[x]); }

// SegmentTree;

void updateNode(int p, node cnode)
{
    if (cnode.val < nodes[p][0].val)
    {
        if (cnode.id != nodes[p][0].id)
            nodes[p][1] = nodes[p][0];
        nodes[p][0] = cnode;
    }
    else if (cnode.val < nodes[p][1].val && cnode.id != nodes[p][0].id)
        nodes[p][1] = cnode;
}

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void pushup(int p)
{
    nodes[p][0] = nodes[p][1] = infty;
    for (int i = 0; i < 2; i++)
        updateNode(p, nodes[lson][i]), updateNode(p, nodes[rson][i]);
}

void build(int l, int r, int p)
{
    tags[p] = 0;
    if (l == r)
        return (void)(nodes[p][0] = node{0, find(l)}, nodes[p][1] = infty);
    build(l, mid, lson), build(mid + 1, r, rson);
    pushup(p);
}

void pushdown(int p)
{
    if (tags[p])
    {
        tags[lson] += tags[p], tags[rson] += tags[p];
        for (int i = 0; i < 2; i++)
            nodes[lson][i].val += tags[p], nodes[rson][i].val += tags[p];
        tags[p] = 0;
    }
}

void update(int ql, int qr, int l, int r, int p, ll val)
{
    if (ql <= l && r <= qr)
        return (void)(nodes[p][0].val += val, nodes[p][1].val += val, tags[p] += val);
    pushdown(p);
    if (ql <= mid)
        update(ql, qr, l, mid, lson, val);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, val);
    pushup(p);
}

#undef mid
#undef rson
#undef lson

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, l1, r1, l2, r2, w; i <= m; i++)
    {
        scanf("%d%d%d%d%d", &l1, &r1, &l2, &r2, &w);
        frames[l1].push_back(frame{l1, l2, r2, w});
        frames[r1 + 1].push_back(frame{r1 + 1, l2, r2, -w});
        frames[l2].push_back(frame{l2, l1, r1, w});
        frames[r2 + 1].push_back(frame{r2 + 1, l1, r1, -w});
    }
    for (int i = 1; i <= n; i++)
        mem[i] = i;
    ll ans = 0, component_tot = n;
    while (component_tot > 1)
    {
        build(1, n, 1);
        for (int i = 1; i <= n; i++)
            pending[i] = infty;
        for (int i = 1; i <= n; i++)
        {
            for (frame x : frames[i])
                update(x.l, x.r, 1, n, 1, x.w);
            int u = find(i);
            node curt;
            curt = (u == nodes[1][0].id) ? nodes[1][1] : nodes[1][0];
            if (curt.val < pending[u].val)
                pending[u] = curt;
        }
        for (int u = 1; u <= n; u++)
            if (find(u) == u && find(pending[u].id) != u)
                component_tot--, mem[find(pending[u].id)] = u, ans += pending[u].val;
    }
    printf("%lld\n", ans);
    return 0;
}