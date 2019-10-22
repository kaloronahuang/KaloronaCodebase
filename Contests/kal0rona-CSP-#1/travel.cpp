// travel.cpp
#include <bits/stdc++.h>
typedef long long ll;
#define pr pair<ll, int>

using namespace std;

const int MAX_N = 6e5 + 200;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int head[MAX_N], current, n, m1, m2;
ll dist[MAX_N];
bool vis[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N * 10];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void shortest_path(int src)
{
    memset(dist, 0x3f, sizeof(dist));
    priority_queue<pr> pq;
    pq.push(make_pair(0, src)), dist[src] = 0;
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[edges[i].to] > dist[u] + edges[i].weight)
                dist[edges[i].to] = dist[u] + edges[i].weight, pq.push(make_pair(-dist[edges[i].to], edges[i].to));
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &m1, &m2);
    for (int i = 1, u, v, w; i <= m1; i++)
    {
        scanf("%d%d%d", &u, &v, &w);
        for (int layer = 0; layer <= m2; layer++)
            addpath(u + layer * n, v + layer * n, w);
    }
    for (int i = 1, u, v; i <= m2; i++)
    {
        scanf("%d%d", &u, &v);
        for (int layer = 0; layer < m2; layer++)
            addpath(u + layer * n, v + (layer + 1) * n, 0);
    }
    shortest_path(1);
    for (int layer = 0; layer <= m2; layer++)
        if (dist[layer * n + n] < INF)
            printf("%d\n%lld", layer, dist[layer * n + n]), exit(0);
    puts("-1");
    return 0;
}