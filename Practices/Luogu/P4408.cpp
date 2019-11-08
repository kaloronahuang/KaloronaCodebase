// P4408.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 200100;

int head[MAX_N], current, n, m;
ll dist[MAX_N][2];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void dfs(int u, int fa, int id)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dist[edges[i].to][id] = dist[u][id] + edges[i].weight, dfs(edges[i].to, u, id);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v, w; i <= m; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
    int stp = 0, edp = 0;
    ll diameter = 0, ans = 0;
    dfs(1, 0, 0);
    for (int i = 1; i <= n; i++)
        if (dist[i][0] > dist[stp][0])
            stp = i;
    dfs(stp, 0, 1);
    for (int i = 1; i <= n; i++)
        if (dist[i][1] > dist[edp][1])
            edp = i;
    diameter = dist[edp][1];
    dist[edp][0] = 0, dfs(edp, 0, 0);
    for (int i = 1; i <= n; i++)
        ans = max(ans, diameter + min(dist[i][0], dist[i][1]));
    printf("%lld", ans);
    return 0;
}