// P2469.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, INF = 0x3f3f3f3f;
typedef long long ll;

int head[MAX_N], current, n, m, START, END, flow[MAX_N], pre[MAX_N], ai[MAX_N];
ll dist[MAX_N];
bool vis[MAX_N];

struct edge
{
    int to, nxt, weight, cost;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight, int cost)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, edges[current].cost = cost;
    head[src] = current++;
}

void addtube(int src, int dst, int weight, int cost)
{
    addpath(src, dst, weight, cost);
    addpath(dst, src, 0, -cost);
}

bool spfa()
{
    memset(dist, 0x3f, sizeof(dist)), memset(vis, false, sizeof(vis));
    queue<int> q;
    q.push(START), vis[START] = true, dist[START] = 0, flow[START] = INF;
    while (!q.empty())
    {
        ll u = q.front();
        q.pop(), vis[u] = false;
        for (ll i = head[u]; i != -1; i = edges[i].nxt)
            if (edges[i].weight > 0 && dist[edges[i].to] > dist[u] + edges[i].cost)
            {
                dist[edges[i].to] = dist[u] + edges[i].cost;
                flow[edges[i].to] = min(flow[u], edges[i].weight);
                pre[edges[i].to] = i;
                if (!vis[edges[i].to])
                    vis[edges[i].to] = true, q.push(edges[i].to);
            }
    }
    return dist[END] != 0x3f3f3f3f3f3f3f3f;
}

ll mcmf()
{
    ll max_flow = 0, min_cost = 0;
    while (spfa())
    {
        ll p = END, i = pre[END];
        max_flow += flow[END], min_cost += 1LL * flow[END] * dist[END];
        while (p != START)
        {
            edges[i].weight -= flow[END], edges[i ^ 1].weight += flow[END];
            p = edges[i ^ 1].to, i = pre[p];
        }
    }
    return min_cost;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m), START = 0, END = (n << 1) | 1;
    for (int i = 1; i <= n; i++)
        addtube(START, i, 1, 0), addtube(i + n, END, 1, 0);
    for (int i = 1, cost; i <= n; i++)
        scanf("%d", &cost), ai[i] = cost, addtube(START, i + n, 1, cost);
    for (int i = 1, u, v, w; i <= m; i++)
    {
        scanf("%d%d%d", &u, &v, &w);
        if (u > v)
            swap(u, v);
        if (w < ai[v])
            addtube(u, v + n, 1, w);
    }
    printf("%lld\n", mcmf());
    return 0;
}