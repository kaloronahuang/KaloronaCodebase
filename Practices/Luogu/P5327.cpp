// P5327.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

typedef long long ll;

int n, head[MAX_N], current, dfn[MAX_N], st[20][MAX_N], stot, ptot;
int log2_[MAX_N], dep[MAX_N], m, roots[MAX_N], up[MAX_N];
vector<int> remTag[MAX_N];
ll ans;

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

struct node
{
    int val, lson, rson, s, t, sum;
} nodes[MAX_N * 30];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u, int fa)
{
    up[u] = fa, st[0][++stot] = u, dfn[u] = stot, dep[u] = dep[fa] + 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u), st[0][++stot] = u;
}

int gmin(int x, int y) { return dep[x] < dep[y] ? x : y; }

int getLCA(int x, int y)
{
    if (x == 0 || y == 0)
        return 0;
    if (dfn[x] > dfn[y])
        swap(x, y);
    int d = log2_[dfn[y] - dfn[x] + 1];
    return gmin(st[d][dfn[x]], st[d][dfn[y] - (1 << d) + 1]);
}

void pushup(int p)
{
    nodes[p].sum = nodes[nodes[p].lson].sum + nodes[nodes[p].rson].sum - dep[getLCA(nodes[nodes[p].lson].t, nodes[nodes[p].rson].s)];
    nodes[p].s = (nodes[nodes[p].lson].s ? nodes[nodes[p].lson].s : nodes[nodes[p].rson].s);
    nodes[p].t = (nodes[nodes[p].rson].t ? nodes[nodes[p].rson].t : nodes[nodes[p].lson].t);
}

#define mid ((l + r) >> 1)

int update(int qx, int l, int r, int p, int val)
{
    if (p == 0)
        p = ++ptot;
    if (l == r)
    {
        nodes[p].val += val;
        if (nodes[p].val > 0)
            nodes[p].s = nodes[p].t = qx, nodes[p].sum = dep[qx];
        else
            nodes[p].s = nodes[p].t = nodes[p].sum = 0;
        return p;
    }
    if (dfn[qx] <= mid)
        nodes[p].lson = update(qx, l, mid, nodes[p].lson, val);
    else
        nodes[p].rson = update(qx, mid + 1, r, nodes[p].rson, val);
    pushup(p);
    return p;
}

int query(int p) { return nodes[p].sum - dep[getLCA(nodes[p].s, nodes[p].t)]; }

int merge(int x, int y, int l, int r)
{
    if (x == 0 || y == 0)
        return x + y;
    if (l == r)
    {
        nodes[x].val += nodes[y].val, nodes[x].sum |= nodes[y].sum;
        nodes[x].s |= nodes[y].s, nodes[x].t |= nodes[y].t;
        return x;
    }
    nodes[x].lson = merge(nodes[x].lson, nodes[y].lson, l, mid);
    nodes[x].rson = merge(nodes[x].rson, nodes[y].rson, mid + 1, r);
    pushup(x);
    return x;
}

void solve(int u, int fa)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            solve(edges[i].to, u);
    for (int v : remTag[u])
        roots[u] = update(v, 1, stot, roots[u], -1);
    ans += query(roots[u]), roots[up[u]] = merge(roots[up[u]], roots[u], 1, stot);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dfs(1, 0);
    for (int i = 2; i <= stot; i++)
        log2_[i] = log2_[i >> 1] + 1;
    for (int i = 1; i < 20; i++)
        for (int j = 1; j + (1 << i) - 1 <= stot; j++)
            st[i][j] = gmin(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
    for (int i = 1, u, v, lca; i <= m; i++)
    {
        scanf("%d%d", &u, &v), lca = getLCA(u, v);
        roots[u] = update(u, 1, stot, roots[u], 1), roots[u] = update(v, 1, stot, roots[u], 1);
        roots[v] = update(u, 1, stot, roots[v], 1), roots[v] = update(v, 1, stot, roots[v], 1);
        remTag[lca].push_back(u), remTag[lca].push_back(v);
        remTag[up[lca]].push_back(u), remTag[up[lca]].push_back(v);
    }
    solve(1, 0), printf("%lld\n", ans >> 1);
    return 0;
}