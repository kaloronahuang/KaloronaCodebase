// P4568.cpp
#include <bits/stdc++.h>
typedef long long ll;
#define pr pair<ll, int>

using namespace std;

const int MAX_N = 2e6 + 200;

int head[MAX_N], current, n, m, k, s, t;
ll dist[MAX_N];
bool vis[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void shortest_path(int src)
{
    memset(dist, 0x3f, sizeof(dist));
    memset(vis, false, sizeof(vis));
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
    scanf("%d%d%d%d%d", &n, &m, &k, &s, &t);
    for (int i = 1, u, v, w; i <= m; i++)
    {
        scanf("%d%d%d", &u, &v, &w);
        for (int layer = 0; layer <= k; layer++)
        {
            addpath(u + layer * n, v + layer * n, w), addpath(v + layer * n, u + layer * n, w);
            if (layer < k)
                addpath(u + layer * n, v + (layer + 1) * n, 0), addpath(v + layer * n, u + (layer + 1) * n, 0);
        }
    }
    shortest_path(s);
    ll ans = 0x3f3f3f3f3f3f3f3f;
    for (int i = 0; i <= k; i++)
        ans = min(ans, dist[i * n + t]);
    printf("%lld\n", ans);
    return 0;
}