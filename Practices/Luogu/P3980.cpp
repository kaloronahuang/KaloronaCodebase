// P3980.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAX_N = 1110, MAX_M = 30100, INF = 0x3f3f3f3f;

int head[MAX_N], current, flow[MAX_N], dist[MAX_N], pre[MAX_N];
int s, t, req[MAX_N], n, m, tmpx, tmpy, tmpz;
bool vis[MAX_N];

struct edge
{
    int to, nxt, weight, cost;
} edges[MAX_M << 1];

void addpath(int src, int dst, int weight, int cst)
{
    edges[current].to = dst, edges[current].weight = weight;
    edges[current].nxt = head[src], edges[current].cost = cst;
    head[src] = current++;
}

void add(int src, int dst, int weight, int cst)
{
    addpath(src, dst, weight, cst);
    addpath(dst, src, 0, -cst);
}

bool spfa()
{
    memset(dist, 0x3f, sizeof(dist));
    queue<int> q;
    q.push(s), vis[s] = true, dist[s] = 0;
    flow[s] = INF;
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), vis[u] = false;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (edges[i].weight > 0 && dist[edges[i].to] > dist[u] + edges[i].cost)
            {
                dist[edges[i].to] = dist[u] + edges[i].cost, pre[edges[i].to] = i;
                flow[edges[i].to] = min(flow[u], edges[i].weight);
                if (!vis[edges[i].to])
                    vis[edges[i].to] = true, q.push(edges[i].to);
            }
    }
    return dist[t] != INF;
}

ll mcmf()
{
    ll ans = 0;
    while (spfa())
    {
        ans += 1LL * dist[t] * flow[t];
        int u = t, i = pre[u];
        while (u != s)
        {
            edges[i].weight -= flow[t], edges[i ^ 1].weight += flow[t];
            u = edges[i ^ 1].to, i = pre[u];
        }
    }
    return ans;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &req[i]), add(i, i + 1, INF - req[i], 0);
    add(s = 0, 1, INF, 0), add(n + 1, t = n + 2, INF, 0);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &tmpx, &tmpy, &tmpz), add(tmpx, tmpy + 1, INF, tmpz);
    printf("%lld", mcmf());
    return 0;
}