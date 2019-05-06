// P4899.cpp
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 401000, MAX_M = 401000, INF = 0x3f3f3f3f;

int n, m, q, mapping[MAX_N];

struct edge
{
    int from, to, nxt;
} source[MAX_M];

struct Ufs
{
    int buff[MAX_N];

    void init(int amount)
    {
        for (int i = 1; i <= amount; i++)
            buff[i] = i;
    }

    int find(int x) { return x == buff[x] ? x : buff[x] = find(buff[x]); }
} Uu, Ul;

struct graph
{
    int head[MAX_N], current, lft[MAX_N], rig[MAX_N], anti[MAX_N], dfn;
    int fa[20][MAX_N], val[MAX_N];
    edge edges[MAX_M];

    graph() { memset(head, -1, sizeof(head)); }

    void addpath(int u, int v)
    {
        edges[current].to = v, edges[current].from = u;
        edges[current].nxt = head[u], head[u] = current++;
    }

    void initialize(int u)
    {
        if (u <= n)
            anti[++dfn] = u, lft[u] = dfn, val[u] = u;
        else
            lft[u] = dfn + 1;
        for (int i = 1; i < 20; i++)
            fa[i][u] = fa[i - 1][fa[i - 1][u]];
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            fa[0][edges[i].to] = u, initialize(edges[i].to);
        rig[u] = dfn;
    }

    int find_max(int u, int upper)
    {
        for (int i = 19; i >= 0; i--)
            if (val[fa[i][u]] <= upper)
                u = fa[i][u];
        return u;
    }

    int find_min(int u, int lower)
    {
        for (int i = 19; i >= 0; i--)
            if (val[fa[i][u]] >= lower)
                u = fa[i][u];
        return u;
    }
} Tu, Tl;

bool compare_u(const edge &a, const edge &b) { return max(a.from, a.to) < max(b.from, b.to); }

bool compare_l(const edge &a, const edge &b) { return min(a.from, a.to) > min(b.from, b.to); }

void kruskal_u()
{
    int tot = n;
    sort(source + 1, source + 1 + m, compare_u);
    Uu.init(n << 1);
    for (int i = 1; i <= m; i++)
    {
        int a = Uu.find(source[i].from), b = Uu.find(source[i].to);
        int v = max(source[i].from, source[i].to);
        if (a != b)
        {
            Uu.buff[a] = Uu.buff[b] = ++tot;
            Tu.val[tot] = v;
            Tu.addpath(tot, a), Tu.addpath(tot, b);
        }
    }
    Tu.initialize(tot);
}

void kruskal_l()
{
    int tot = n;
    sort(source + 1, source + 1 + m, compare_l);
    Ul.init(n << 1);
    for (int i = 1; i <= m; i++)
    {
        int a = Ul.find(source[i].from), b = Ul.find(source[i].to);
        int v = min(source[i].from, source[i].to);
        if (a != b)
        {
            Ul.buff[a] = Ul.buff[b] = ++tot;
            Tl.val[tot] = v;
            Tl.addpath(tot, a), Tl.addpath(tot, b);
        }
    }
    Tl.initialize(tot);
}

struct sustainable_segment_node
{
    int sum, lson, rson;
};

struct sustainable_segment_tree
{
    sustainable_segment_node nodes[MAX_N << 5];
    int roots[MAX_N], tot;

    int update(int qx, int l, int r, int pre, int val)
    {
        int p = ++tot;
        nodes[p] = nodes[pre], nodes[p].sum += val;
        if (l == r)
            return p;
        int mid = (l + r) >> 1;
        if (qx <= mid)
            nodes[p].lson = update(qx, l, mid, nodes[pre].lson, val);
        else
            nodes[p].rson = update(qx, mid + 1, r, nodes[pre].rson, val);
        return p;
    }

    int query(int ql, int qr, int l, int r, int p, int pre)
    {
        if (ql <= l && r <= qr)
            return nodes[p].sum - nodes[pre].sum;
        int mid = (l + r) >> 1, ans = 0;
        if (ql <= mid)
            ans += query(ql, qr, l, mid, nodes[p].lson, nodes[pre].lson);
        if (mid < qr)
            ans += query(ql, qr, mid + 1, r, nodes[p].rson, nodes[pre].rson);
        return ans;
    }
} seg;

// Tu -> Te

int main()
{
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= m; i++)
        scanf("%d%d", &source[i].from, &source[i].to), source[i].from++, source[i].to++;
    kruskal_l(), kruskal_u();
    Tu.val[0] = INF;
    for (int i = 1; i <= n; i++)
        mapping[Tl.anti[i]] = i;
    seg.roots[0] = 0;
    for (int i = 1; i <= n; i++)
        seg.roots[i] = seg.update(mapping[Tu.anti[i]], 1, n, seg.roots[i - 1], 1);
    while (q--)
    {
        int s, e, l, r;
        scanf("%d%d%d%d", &s, &e, &l, &r), s++, e++, l++, r++;
        int x = Tl.find_min(s, l), y = Tu.find_max(e, r);
        int res = seg.query(Tl.lft[x], Tl.rig[x], 1, n, seg.roots[Tu.rig[y]], seg.roots[Tu.lft[y] - 1]);
        puts(res ? "1" : "0");
    }
    return 0;
}