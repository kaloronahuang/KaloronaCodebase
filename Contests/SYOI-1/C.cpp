// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200;

int head[MAX_N], current, n, m, mem[MAX_N], tag[MAX_N], fa[20][MAX_N], dep[MAX_N], q;

struct edge
{
    int from, to, nxt, weight;
    bool operator<(const edge &nd) const { return weight < nd.weight; }
} org[MAX_N], edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

int find(int x) { return x == mem[x] ? x : mem[x] = find(mem[x]); }

void dfs(int u, int fat)
{
    dep[u] = dep[fat] + 1, fa[0][u] = fat;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fat)
            dfs(edges[i].to, u);
}

int getLCA(int x, int y)
{
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = 19; i >= 0; i--)
        if (dep[fa[i][x]] >= dep[y])
            x = fa[i][x];
    if (x == y)
        return x;
    for (int i = 19; i >= 0; i--)
        if (fa[i][x] != fa[i][y])
            x = fa[i][x], y = fa[i][y];
    return fa[0][x];
}

void redfs(int u, int fat)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fat)
            redfs(edges[i].to, u), tag[u] += tag[edges[i].to];
}

int main()
{
    freopen("tanxia.in", "r", stdin);
    freopen("tanxia.out", "w", stdout);
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; i++)
        mem[i] = i;
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &org[i].from, &org[i].to, &org[i].weight);
    sort(org + 1, org + 1 + m);
    for (int i = 1; i <= m; i++)
    {
        int x = org[i].from, y = org[i].to;
        if (find(x) != find(y))
            mem[find(x)] = find(y), addpath(x, y, org[i].weight), addpath(y, x, org[i].weight);
    }
    dfs(1, 0);
    for (int i = 1; i <= 19; i++)
        for (int j = 1; j <= n; j++)
            fa[i][j] = fa[i - 1][fa[i - 1][j]];
    while (q--)
    {
        int u, v, lca;
        scanf("%d%d", &u, &v);
        tag[u]++, tag[v]++, lca = getLCA(u, v);
        tag[lca]--, tag[fa[0][lca]]--;
    }
    redfs(1, 0);
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        //printf("%d ", tag[i]);
        if (tag[i] >= tag[ans])
            ans = i;
    }
    //puts("");
    printf("%d %d", ans, tag[ans]);
    return 0;
}