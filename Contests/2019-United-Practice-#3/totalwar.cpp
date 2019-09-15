// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 200;

int fa[20][MAX_N], head[MAX_N], current, val[20][MAX_N], n, m, q, dep[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].nxt = head[src], edges[current].to = dst;
    head[src] = current++;
}

pair<int, int> getLca(int x, int y)
{
    int ans = max(val[0][x], val[0][y]);
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = 19; i >= 0; i--)
        if (dep[fa[i][x]] >= dep[y])
            ans = max(ans, max(val[i][x], val[0][fa[i][x]])), x = fa[i][x];
    if (x == y)
        return make_pair(x, ans);
    for (int i = 19; i >= 0; i--)
        if (fa[i][x] != fa[i][y])
            ans = max(ans, max(max(val[i][x], val[0][fa[i][x]]), max(val[i][y], val[0][fa[i][y]]))), x = fa[i][x], y = fa[i][y];
    return make_pair(fa[0][x], max(ans, val[0][fa[0][x]]));
}

void predfs(int u)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        dep[edges[i].to] = dep[u] + 1, predfs(edges[i].to);
}

void dfs(int u)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        dfs(edges[i].to), val[0][u] += val[0][edges[i].to];
}

int main()
{
    freopen("totalwar.in", "r", stdin);
    freopen("totalwar.out", "w", stdout);
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 2; i <= n; i++)
        scanf("%d", &fa[0][i]), addpath(fa[0][i], i);
    dep[1] = 1, predfs(1);
    for (int i = 1; i < 20; i++)
        for (int j = 1; j <= n; j++)
            fa[i][j] = fa[i - 1][fa[i - 1][j]];
    for (int i = 1, u, v; i <= m; i++)
    {
        scanf("%d%d", &u, &v);
        int lca = getLca(u, v).first;
        val[0][u]++, val[0][v]++, val[0][lca]--, val[0][fa[0][lca]]--;
    }
    val[0][fa[0][1]] = 0, dfs(1);
    for (int i = 1; i < 20; i++)
        for (int j = 1; j <= n; j++)
            val[i][j] = max(val[i - 1][j], val[i - 1][fa[i - 1][j]]);
    for (int i = 1, u, v; i <= q; i++)
        scanf("%d%d", &u, &v), printf("%d\n", getLca(u, v).second);
    return 0;
}