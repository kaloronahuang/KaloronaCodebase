// E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int head[MAX_N], current, n, q, dep[MAX_N], fa[20][MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u)
{
    dep[u] = dep[fa[0][u]] + 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa[0][u])
            fa[0][edges[i].to] = u, dfs(edges[i].to);
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

int getDist(int x, int y) { return dep[x] + dep[y] - (dep[getLCA(x, y)] << 1); }

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dfs(1), scanf("%d", &q);
    for (int i = 1; i <= 19; i++)
        for (int j = 1; j <= n; j++)
            fa[i][j] = fa[i - 1][fa[i - 1][j]];
    while (q--)
    {
        int x, y, a, b, k;
        scanf("%d%d%d%d%d", &x, &y, &a, &b, &k);
        int org = getDist(a, b);
        int loop = min(getDist(a, x) + getDist(y, b), getDist(a, y) + getDist(x, b)) + 1;
        int loop_1 = getDist(x, y) + getDist(a, x) + getDist(b, x) + 1;
        int loop_2 = getDist(x, y) + getDist(a, y) + getDist(b, y) + 1;
        int ans = 2e9;
        if ((org % 2) == (k % 2))
            ans = org;
        if ((loop % 2) == (k % 2))
            ans = min(ans, loop);
        if ((loop_1 % 2) == (k % 2))
            ans = min(ans, loop_1);
        if ((loop_2 % 2) == (k % 2))
            ans = min(ans, loop_2);
        puts(ans <= k ? "YES" : "NO");
    }
    return 0;
}