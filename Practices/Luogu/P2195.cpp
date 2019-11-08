// P2195.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200;

int n, m, q, fa[MAX_N], siz[MAX_N], diameter[MAX_N], head[MAX_N], current, mx_p, val;

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

void unite(int x, int y)
{
    if (find(x) == find(y))
        return;
    if (siz[x] < siz[y])
        swap(x, y);
    siz[find(x)] += siz[find(y)], fa[find(y)] = find(x);
}

void merge(int x, int y)
{
    x = find(x), y = find(y);
    if (x == y)
        return;
    if (siz[x] < siz[y])
        swap(x, y);
    siz[x] += siz[y], fa[y] = x;
    diameter[x] = max(max(((diameter[x] + 1) >> 1) + ((diameter[y] + 1) >> 1) + 1, diameter[x]), diameter[y]);
}

void dfs(int u, int fa, int dep)
{
    if (dep > val)
        val = dep, mx_p = u;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u, dep + 1);
}

int get_diameter(int u)
{
    mx_p = -1, val = -1;
    dfs(u, 0, 0);
    int tmp = mx_p;
    mx_p = -1, val = -1;
    dfs(tmp, 0, 0);
    return val;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; i++)
        fa[i] = i, siz[i] = 1, diameter[i] = 1;
    for (int i = 1, u, v; i <= m; i++)
    {
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
        unite(u, v);
    }
    for (int i = 1; i <= n; i++)
        if (find(i) == i)
            diameter[i] = get_diameter(i);
    while (q--)
    {
        int opt, u, v;
        scanf("%d", &opt);
        if (opt == 1)
            scanf("%d", &u), printf("%d\n", diameter[find(u)]);
        else
            scanf("%d%d", &u, &v), merge(u, v);
    }
    return 0;
}