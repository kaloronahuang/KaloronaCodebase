// A.cpp
#include <bits/stdc++.h>
#define pr pair<int, int>

using namespace std;

const int MAX_N = 1100;

int n, m, c, dist[MAX_N * MAX_N], current, head[MAX_N * MAX_N];
bool vis[MAX_N * MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[1010 + MAX_N * MAX_N];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void djisktra()
{
    memset(dist, 0x3f, sizeof(dist));
    priority_queue<pr> q;
    q.push(make_pair(0, 1));
    dist[1] = 0;
    while (!q.empty())
    {
        int u = q.top().second;
        q.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[edges[i].to] > dist[u] + edges[i].weight)
                dist[edges[i].to] = dist[u] + edges[i].weight, q.push(make_pair(-dist[edges[i].to], edges[i].to));
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &m, &c);
    for (int i = 1; i <= m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        for (int layer = 0; layer < n; layer++)
            addpath(layer * n + u, layer * n + v, w);
        for (int layer = 0; layer < n - 1; layer++)
            addpath(layer * n + u, (layer + 1) * n + v, 0);
    }
    djisktra();
    for (int layer = 0; layer < n; layer++)
        if (dist[layer * n + n] <= c)
        {
            printf("%d", layer);
            return 0;
        }
    return 0;
}