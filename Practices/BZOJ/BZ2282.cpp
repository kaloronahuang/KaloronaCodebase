// BZ2282.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200, INF = 0x3f3f3f3f;

int head[MAX_N], current, n, m, groot, gdown, pt, val, up[MAX_N], dep[MAX_N], upweight[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].weight = weight;
    edges[current].nxt = head[src], head[src] = current++;
}

void dfs(int u, int fa, int dist)
{
    if (dist > val)
        val = dist, pt = u;
    up[u] = fa, dep[u] = dep[fa] + upweight[u];
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u, dist + edges[i].weight), upweight[edges[i].to] = edges[i].weight;
}

void findDiameter()
{
    val = 0, pt = 0;
    dfs(1, 0, 0), groot = pt, val = 0;
    memset(dep, 0, sizeof(dep));
    dfs(groot, 0, 0), gdown = pt;
}

bool check(int mid)
{
    int p1 = gdown;
    while (up[p1] && dep[gdown] - dep[up[p1]] <= mid)
        p1 = up[p1];
    int p2 = p1;
    while (up[p2] && dep[p1] - dep[up[p2]] <= m)
        p2 = up[p2];
    return dep[p2] <= mid;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v, w; i <= n - 1; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
    findDiameter();
    int l = 0, r = 1e9, res;
    printf(check(0) ? "YES\n" : "NO\n");
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
            r = mid - 1, res = mid;
        else
            l = mid + 1;
    }
    printf("%d\n", res);
    return 0;
}