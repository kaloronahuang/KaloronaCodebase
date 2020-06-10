// P4542.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, MAX_E = 1e6 + 200, INF = 0x3f3f3f3f;

typedef long long ll;

int n, m, k, current, head[MAX_N], pre[MAX_N], start_pos, end_pos, flow[MAX_N];
int mp[220][220];
ll dist[MAX_N];
bool vis[MAX_N];

struct edge
{
    int to, nxt, weight, cost;
} edges[MAX_E << 1];

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
    queue<int> q;
    memset(dist, 0x3f, sizeof(dist)), memset(pre, -1, sizeof(pre));
    memset(vis, false, sizeof(vis)), memset(flow, 0x3f, sizeof(flow));
    q.push(start_pos), dist[start_pos] = 0, flow[start_pos] = INF;
    vis[start_pos] = true;
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
                    q.push(edges[i].to), vis[edges[i].to] = true;
            }
    }
    return pre[end_pos] != -1;
}

int main()
{
    memset(head, -1, sizeof(head));
    memset(mp, 0x3f, sizeof(mp));
    scanf("%d%d%d", &n, &m, &k), n++;
    start_pos = n + n + 1, end_pos = start_pos + 1;
    for (int i = 1; i <= n; i++)
        mp[i][i] = 0;
    for (int i = 1, u, v, e; i <= m; i++)
    {
        scanf("%d%d%d", &u, &v, &e);
        u++, v++, mp[u][v] = mp[v][u] = min(mp[u][v], e);
    }
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (k < max(i, j))
                    mp[i][j] = min(mp[i][j], mp[i][k] + mp[k][j]);
    for (int i = 1; i <= n; i++)
    {
        addtube(start_pos, i, (i == 1) ? k : 1, 0);
        addtube(i + n, end_pos, 1, 0);
        for (int j = i + 1; j <= n; j++)
            if (mp[i][j] != INF)
                addtube(i, j + n, 1, mp[i][j]);
    }
    ll ret = 0;
    while (spfa())
    {
        ret += 1LL * dist[end_pos] * flow[end_pos];
        int u = end_pos;
        while (u != start_pos)
        {
            edges[pre[u]].weight -= flow[end_pos], edges[pre[u] ^ 1].weight += flow[end_pos];
            u = edges[pre[u] ^ 1].to;
        }
    }
    printf("%lld\n", ret);
    return 0;
}