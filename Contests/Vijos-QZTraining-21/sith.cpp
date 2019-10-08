// sith.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, m, q, head[MAX_N], current, fa[20][MAX_N], dep[MAX_N], val[20][MAX_N], curt_lca, ans;

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u, int fat)
{
    fa[0][u] = fat, dep[u] = dep[fat] + 1, val[0][u] = (fat == 0) ? u : min(u, fat);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fat)
            dfs(edges[i].to, u);
}

pair<int, int> getLCA(int x, int y)
{
    int alongside = min(x, y);
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = 19; i >= 0; i--)
        if (dep[fa[i][x]] >= dep[y])
            alongside = min(alongside, val[i][x]), x = fa[i][x];
    if (x == y)
        return make_pair(x, alongside);
    for (int i = 19; i >= 0; i--)
        if (fa[i][x] != fa[i][y])
            alongside = min(alongside, min(val[i][x], val[i][y])), x = fa[i][x], y = fa[i][y];
    alongside = min(alongside, val[0][x]);
    return make_pair(fa[0][x], alongside);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &q);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dfs(1, 0);
    for (int i = 1; i <= 19; i++)
        for (int j = 1; j <= n; j++)
            fa[i][j] = fa[i - 1][fa[i - 1][j]], val[i][j] = min(val[i - 1][j], val[i - 1][fa[i - 1][j]]);
    int opt, tmp;
    while (q--)
    {
        scanf("%d%d", &opt, &tmp);
        if (opt == 2)
            printf("%d\n", min(getLCA(tmp, curt_lca).second, ans));
        else if (curt_lca == 0)
            curt_lca = tmp, ans = tmp;
        else
        {
            pair<int, int> ret = getLCA(tmp, curt_lca);
            ans = min(ans, ret.second), curt_lca = ret.first;
        }
    }
    return 0;
}