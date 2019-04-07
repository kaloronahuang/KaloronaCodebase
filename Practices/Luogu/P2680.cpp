// P2680.cpp
#include <bits/stdc++.h>
#define pr pair<int, int>
using namespace std;
const int MAX_N = 3e5 + 2000;
int n, m, head[MAX_N], current, tmpx, tmpy, tmpz, tag[MAX_N];
int fa[20][MAX_N], dist[MAX_N], dep[MAX_N], sideWeight[MAX_N];
struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];
struct route
{
    int src, dst, dist, lca;
} routes[MAX_N];
void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}
void dfs(int u)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (fa[0][u] != edges[i].to)
        {
            dep[edges[i].to] = dep[u] + 1, fa[0][edges[i].to] = u;
            dist[edges[i].to] = dist[u] + edges[i].weight;
            sideWeight[edges[i].to] = edges[i].weight;
            dfs(edges[i].to);
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
bool compare(route a, route b) { return a.dist > b.dist; }
void complete(int u)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa[0][u])
            complete(edges[i].to), tag[u] += tag[edges[i].to];
}
bool check(int attempt)
{
    memset(tag, 0, sizeof(tag));
    int pubSide = 0, numOfSides = 0;
    for (int i = 1; i <= m; i++)
    {
        if (routes[i].dist <= attempt)
            break;
        tag[routes[i].src]++, tag[routes[i].dst]++;
        tag[routes[i].lca] -= 2;
        numOfSides++;
    }
    complete(1);
    for (int i = 1; i <= n; i++)
        if (tag[i] == numOfSides)
            pubSide = max(pubSide, sideWeight[i]);
    return routes[1].dist - pubSide <= attempt;
}
int main()
{
    int l = 0, r = 0;
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n - 1; i++)
    {
        scanf("%d%d%d", &tmpx, &tmpy, &tmpz), l = max(l, tmpz);
        addpath(tmpx, tmpy, tmpz), addpath(tmpy, tmpx, tmpz);
    }
    dep[1] = 1, dfs(1);
    for (int i = 1; i < 20; i++)
        for (int j = 1; j <= n; j++)
            fa[i][j] = fa[i - 1][fa[i - 1][j]];
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &tmpx, &tmpy);
        route &curt = routes[i];
        curt.src = tmpx, curt.dst = tmpy, curt.lca = getLCA(tmpx, tmpy);
        curt.dist = dist[tmpx] + dist[tmpy] - 2 * dist[curt.lca];
        r = max(r, curt.dist);
    }
    sort(routes + 1, routes + 1 + m, compare);
    l = r - l;
    while (l <= r)
        if (check((l + r) >> 1))
            r = ((l + r) >> 1) - 1;
        else
            l = ((l + r) >> 1) + 1;
    printf("%d", l);
    return 0;
}