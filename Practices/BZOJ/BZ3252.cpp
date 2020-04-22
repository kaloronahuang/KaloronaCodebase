// BZ3252.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

typedef long long ll;

int n, head[MAX_N], current, tlimit, val[MAX_N], lft[MAX_N], rig[MAX_N], anti[MAX_N], ptot, up[MAX_N], id[MAX_N << 2], deg[MAX_N];
ll dist[MAX_N], nodes[MAX_N << 2], tag[MAX_N << 2];
bool vis[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void pushup(int p)
{
    if (nodes[lson] > nodes[rson])
        id[p] = id[lson], nodes[p] = nodes[lson];
    else
        id[p] = id[rson], nodes[p] = nodes[rson];
}

void build(int l, int r, int p)
{
    if (l == r)
        return (void)(nodes[p] = dist[anti[l]], id[p] = l);
    build(l, mid, lson), build(mid + 1, r, rson);
    pushup(p);
}

void pushdown(int p)
{
    if (tag[p] != 0)
    {
        nodes[lson] += tag[p], nodes[rson] += tag[p];
        tag[lson] += tag[p], tag[rson] += tag[p];
        tag[p] = 0;
    }
}

void update(int ql, int qr, int l, int r, int p, int val)
{
    if (ql <= l && r <= qr)
    {
        nodes[p] -= val, tag[p] -= val;
        return;
    }
    pushdown(p);
    if (ql <= mid)
        update(ql, qr, l, mid, lson, val);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, val);
    pushup(p);
}

void jump(int u)
{
    while (u)
    {
        if (vis[u])
            break;
        vis[u] = true;
        update(lft[u], rig[u], 1, ptot, 1, val[u]);
        u = up[u];
    }
}

void dfs(int u, int fa)
{
    dist[u] = dist[fa] + val[u], up[u] = fa;
    if (fa != 0 && deg[u] == 1)
    {
        // leaf;
        lft[u] = rig[u] = ++ptot, anti[ptot] = u;
        return;
    }
    lft[u] = ptot + 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u);
    rig[u] = ptot;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &tlimit);
    for (int i = 1; i <= n; i++)
        scanf("%d", &val[i]);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u), deg[u]++, deg[v]++;
    dfs(1, 0), build(1, ptot, 1);
    ll ans = 0;
    while (tlimit--)
        ans += nodes[1], jump(anti[id[1]]);
    printf("%lld\n", ans);
    return 0;
}