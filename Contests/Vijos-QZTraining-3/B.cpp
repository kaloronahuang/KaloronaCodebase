// B.cpp
#include <bits/stdc++.h>
#define ll long long
#define pr pair<ll, int>

using namespace std;

const ll MAX_N = 3e5 + 500, MAX_E = 2e6 + 500, INF = 1e14;

ll n, m, k, head[MAX_N], current, dist_forward[MAX_N], dist_backward[MAX_N], *dist, stpt, edpt, tmp;
bool vis[MAX_N];

struct edge
{
    int to, nxt;
    ll weight;
} edges[MAX_E];

void addpath(int src, int dst, ll weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void dijkstra()
{
    memset(vis, false, sizeof(vis));
    priority_queue<pr> pq;
    pq.push(make_pair(0, stpt)), dist[stpt] = 0;
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
    memset(dist_forward, 0x3f, sizeof(dist_forward)), memset(dist_backward, 0x3f, sizeof(dist_backward));
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1, u, v, w; i <= m - 1; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
    stpt = 1, edpt = n;
    dist = dist_forward, dijkstra();
    swap(stpt, edpt);
    dist = dist_backward, dijkstra();
    int src, dst;
    scanf("%d%d", &src, &dst);
    ll other = min(dist_forward[src] + dist_backward[dst], dist_backward[src] + dist_forward[dst]);
    if (other >= INF)
        while (k--)
            puts("+Inf");
    else
        while (k--)
            scanf("%d", &tmp), printf("%lld\n", min(dist_forward[n], other + tmp));
    return 0;
}