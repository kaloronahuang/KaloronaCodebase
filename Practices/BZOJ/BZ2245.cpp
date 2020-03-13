// BZ2245.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, MAX_M = 1e6 + 200;

typedef long long ll;

int n, m, head[MAX_N], current, pre[MAX_N], flow[MAX_N], start_pos, end_pos, tmp[MAX_N];
ll dist[MAX_N];
bool vis[MAX_N];

struct edge
{
    int to, nxt, weight, cost;
} edges[MAX_M << 1];

void addpath(int src, int dst, int weight, int cost)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, edges[current].cost = cost;
    head[src] = current++;
}

void addtube(int src, int dst, int weight, int cost) { addpath(src, dst, weight, cost), addpath(dst, src, 0, -cost); }

bool spfa()
{
    memset(dist, 0x3f, sizeof(dist));
    memset(vis, false, sizeof(vis));
    memset(flow, 0, sizeof(flow));
    queue<int> q;
    q.push(start_pos), vis[start_pos] = true, dist[start_pos] = 0;
    flow[start_pos] = 0x3f3f3f3f;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        vis[u] = false;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[edges[i].to] > dist[u] + edges[i].cost && edges[i].weight > 0)
            {
                dist[edges[i].to] = dist[u] + edges[i].cost;
                flow[edges[i].to] = min(edges[i].weight, flow[u]);
                pre[edges[i].to] = i;
                if (!vis[edges[i].to])
                    q.push(edges[i].to), vis[edges[i].to] = true;
            }
    }
    return flow[end_pos] != 0;
}

ll mfmc()
{
    ll ret = 0;
    while (spfa())
    {
        int p = end_pos;
        ret += 1LL * dist[end_pos] * flow[end_pos];
        while (p != start_pos)
            edges[pre[p]].weight -= flow[end_pos], edges[pre[p] ^ 1].weight += flow[end_pos], p = edges[pre[p] ^ 1].to;
    }
    return ret;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    start_pos = n + m + n * m + 100 * n, end_pos = start_pos + 1;
    for (int i = 1, val; i <= m; i++)
        scanf("%d", &val), addtube(i, end_pos, val, 0);
    for (int i = 1; i <= n; i++)
        for (int j = 1, val; j <= m; j++)
        {
            scanf("%d", &val);
            if (val == 1)
                addtube(i + m, j, 0x3f3f3f3f, 0);
        }
    for (int i = 1, segtot; i <= n; i++)
    {
        scanf("%d", &segtot);
        for (int j = 1; j <= segtot; j++)
            scanf("%d", &tmp[j]);
        tmp[segtot + 1] = 0x3f3f3f3f;
        for (int j = 1, w; j <= segtot + 1; j++)
            scanf("%d", &w), addtube(start_pos, i + m, tmp[j] - tmp[j - 1], w);
    }
    printf("%lld\n", mfmc());
    return 0;
}