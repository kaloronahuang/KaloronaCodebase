// D.cpp
#include <bits/stdc++.h>
#define pr pair<int, int>

using namespace std;

const int MAX_N = 1010, MAX_E = 500 * 999 + 2000, mod = 2147483647;

int n, m, head[MAX_N], current, dist[MAX_N], indeg[MAX_N];
bool vis[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_E << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].nxt = head[src], edges[current].to = dst;
    edges[current].weight = weight, head[src] = current++;
}

void djisktra(bool first = true)
{
    if (first)
        memset(dist, 0x3f, sizeof(dist));
    memset(vis, false, sizeof(vis));
    priority_queue<pr> q;
    q.push(make_pair(0, 1)), dist[1] = 0;
    while (!q.empty())
    {
        int u = q.top().second;
        q.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[edges[i].to] >= dist[u] + edges[i].weight)
            {
                dist[edges[i].to] = dist[u] + edges[i].weight, q.push(make_pair(-dist[edges[i].to], edges[i].to));
                if (!first && dist[edges[i].to] == dist[u] + edges[i].weight)
                    indeg[edges[i].to]++;
            }
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v, len; i <= m; i++)
        scanf("%d%d%d", &u, &v, &len), addpath(u, v, len), addpath(v, u, len);
    djisktra(), djisktra(false);
    indeg[1] = 1;
    int ans = 1;
    for (int i = 1; i <= n; i++)
        ans = 1LL * ans * indeg[i] % mod;
    printf("%d", ans);
    return 0;
}