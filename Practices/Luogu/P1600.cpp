// P1600.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 3e6 + 2000;
int head[MAX_N], current, fa[20][MAX_N], dep[MAX_N], wi[MAX_N], max_dep;
int bucket[MAX_N << 1], n, m, si[MAX_N], di[MAX_N], status[MAX_N], answer[MAX_N];
int bucket_up[1000011];
vector<int> lcaS[MAX_N], lcaT[MAX_N], tbuck[MAX_N];
struct route
{
    int s, t, lca, len;
} routes[MAX_N];
struct edge
{
    int to, nxt;
} edges[MAX_N << 1];
void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}
void initialize(int u)
{
    max_dep = max(max_dep, dep[u]);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa[0][u])
        {
            dep[edges[i].to] = dep[u] + 1;
            fa[0][edges[i].to] = u;
            initialize(edges[i].to);
        }
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
void dfs_downward(int u)
{
    int now = wi[u] + dep[u], previous;
    if (now <= max_dep)
        previous = bucket[now];
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa[0][u])
            dfs_downward(edges[i].to);
    bucket[dep[u]] += status[u];
    if (now <= max_dep)
        answer[u] = bucket[now] - previous;
    for (int i = 0, siz = lcaS[u].size(); i < siz; i++)
        bucket[dep[lcaS[u][i]]]--;
}
void dfs_upward(int u)
{
    int now = dep[u] - wi[u] + MAX_N, previous = bucket_up[now];
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa[0][u])
            dfs_upward(edges[i].to);
    for (int i = 0, siz = tbuck[u].size(); i < siz; i++)
        bucket_up[MAX_N + tbuck[u][i]]++;
    answer[u] += bucket_up[now] - previous;
    for (int i = 0, siz = lcaT[u].size(); i < siz; i++)
        bucket_up[MAX_N + lcaT[u][i]]--;
}
int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n - 1; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    }
    dep[1] = 1, initialize(1);
    for (int i = 1; i < 20; i++)
        for (int j = 1; j <= n; j++)
            fa[i][j] = fa[i - 1][fa[i - 1][j]];
    for (int i = 1; i <= n; i++)
        scanf("%d", &wi[i]);

    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &routes[i].s, &routes[i].t);
        status[routes[i].s]++;
        routes[i].lca = getLCA(routes[i].s, routes[i].t);
        routes[i].len = dep[routes[i].s] + dep[routes[i].t] - 2 * dep[routes[i].lca];
        lcaS[routes[i].lca].push_back(routes[i].s);
    }
    dfs_downward(1);

    for (int i = 1; i <= m; i++)
    {
        tbuck[routes[i].t].push_back(dep[routes[i].t] - routes[i].len);
        lcaT[routes[i].lca].push_back(dep[routes[i].t] - routes[i].len);
    }
    dfs_upward(1);

    for (int i = 1; i <= m; i++)
        if (dep[routes[i].s] - dep[routes[i].lca] == wi[routes[i].lca])
            answer[routes[i].lca]--;
    for (int i = 1; i <= n; i++)
        printf("%d ", answer[i]);
    return 0;
}