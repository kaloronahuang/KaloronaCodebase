// P3261.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 301000;

int head[MAX_N], current, ptot, n, m;
ll hi[MAX_N], fa[MAX_N], ai[MAX_N], vi[MAX_N], si[MAX_N], ci[MAX_N], roots[MAX_N], dep[MAX_N], ans1[MAX_N], ans2[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N];

struct node
{
    int lson, rson, dist;
    ll value, mul, add;
} nodes[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void update(int p, ll delta, ll prod)
{
    if (p != 0)
    {
        nodes[p].value *= prod, nodes[p].value += delta;
        nodes[p].mul *= prod, nodes[p].add *= prod, nodes[p].add += delta;
    }
}

void pushdown(int p)
{
    update(nodes[p].lson, nodes[p].add, nodes[p].mul);
    update(nodes[p].rson, nodes[p].add, nodes[p].mul);
    nodes[p].mul = 1, nodes[p].add = 0;
}

int merge(int x, int y)
{
    if (x == 0 || y == 0)
        return x + y;
    pushdown(x), pushdown(y);
    if (nodes[x].value > nodes[y].value)
        swap(x, y);
    nodes[x].rson = merge(nodes[x].rson, y);
    if (nodes[nodes[x].lson].dist < nodes[nodes[x].rson].dist)
        swap(nodes[x].lson, nodes[x].rson);
    nodes[x].dist = nodes[nodes[x].rson].dist + 1;
    return x;
}

void dfs(int u)
{
    dep[u] = dep[fa[u]] + 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        dfs(edges[i].to), roots[u] = merge(roots[u], roots[edges[i].to]);
    // pop the soliders;
    while (roots[u] != 0 && nodes[roots[u]].value < hi[u])
    {
        pushdown(roots[u]), ans1[u]++;
        ans2[roots[u]] = dep[ci[roots[u]]] - dep[u];
        roots[u] = merge(nodes[roots[u]].lson, nodes[roots[u]].rson);
    }
    if (ai[u] == 0)
        update(roots[u], vi[u], 1);
    else
        update(roots[u], 0, vi[u]);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &hi[i]);
    for (int i = 2; i <= n; i++)
        scanf("%lld%lld%lld", &fa[i], &ai[i], &vi[i]), addpath(fa[i], i);
    for (int i = 1; i <= m; i++)
    {
        scanf("%lld%lld", &si[i], &ci[i]), nodes[i].mul = 1, nodes[i].value = si[i];
        roots[ci[i]] = merge(roots[ci[i]], i);
    }
    dfs(1);
    while (roots[1])
        pushdown(roots[1]), ans2[roots[1]] = dep[ci[roots[1]]], roots[1] = merge(nodes[roots[1]].lson, nodes[roots[1]].rson);
    for (int i = 1; i <= n; i++)
        printf("%lld\n", ans1[i]);
    for (int i = 1; i <= m; i++)
        printf("%lld\n", ans2[i]);
    return 0;
}