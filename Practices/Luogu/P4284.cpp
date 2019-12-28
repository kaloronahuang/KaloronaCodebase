// P4284.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 2000;

int head[MAX_N], current, n, upward[MAX_N];
double qi[MAX_N], f[MAX_N], g[MAX_N];

struct edge
{
    int to, nxt;
    double weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, double weight)
{
    edges[current].weight = weight, edges[current].to = dst;
    edges[current].nxt = head[src], head[src] = current++;
}

void dfs1(int u, int fa)
{
    f[u] = (1.0 - qi[u]);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            upward[edges[i].to] = i, dfs1(edges[i].to, u), f[u] *= (1 - edges[i].weight + f[edges[i].to] * edges[i].weight);
}

void dfs2(int u, int fa)
{
    if (u == 1)
        g[u] = f[u];
    else
        // change the root;
        g[u] = f[u] * (1 - edges[upward[u]].weight + edges[upward[u]].weight * (g[fa] / (1.0 - edges[upward[u]].weight + f[u] * edges[upward[u]].weight)));
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs2(edges[i].to, u);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1, a, b, p; i <= n - 1; i++)
        scanf("%d%d%d", &a, &b, &p), addpath(a, b, double(p) / 100.0), addpath(b, a, double(p) / 100.0);
    for (int i = 1; i <= n; i++)
        scanf("%lf", &qi[i]), qi[i] /= 100.0;
    dfs1(1, 0), dfs2(1, 0);
    double ans = 0;
    for (int i = 1; i <= n; i++)
        ans += (1.0 - g[i]);
    printf("%.6lf\n", ans);
    return 0;
}