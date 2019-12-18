// LOJ6012.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, INF = 0x3f3f3f3f;

int head[MAX_N], current, n, ci[110][110], dist[MAX_N], pre[MAX_N], flow[MAX_N];
int st, ed;
bool vis[MAX_N];

struct edge
{
    int to, nxt, weight, cost;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight, int cost)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].cost = cost, edges[current].weight = weight;
    head[src] = current++;
}

void addtube(int u, int v, int w, int c) { addpath(u, v, w, c), addpath(v, u, 0, -c); }

bool bfs()
{
    memset(dist, 0x3f, sizeof(dist)), memset(flow, 0x3f, sizeof(flow));
    memset(vis, false, sizeof(vis)), memset(pre, -1, sizeof(pre));
    queue<int> q;
    q.push(st), dist[st] = 0, vis[st] = true;
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), vis[u] = false;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (edges[i].weight > 0 && dist[edges[i].to] > dist[u] + edges[i].cost)
            {
                dist[edges[i].to] = dist[u] + edges[i].cost;
                pre[edges[i].to] = i, flow[edges[i].to] = min(edges[i].weight, flow[u]);
                if (!vis[edges[i].to])
                    vis[edges[i].to] = true, q.push(edges[i].to);
            }
    }
    return pre[ed] != -1;
}

long long mfmc()
{
    long long tot_cost = 0, tot_flow = 0;
    while (bfs())
    {
        tot_flow += flow[ed], tot_cost += 1LL * flow[ed] * dist[ed];
        int p = ed;
        while (p != st)
        {
            int i = pre[p];
            edges[i].weight -= flow[ed], edges[i ^ 1].weight += flow[ed];
            p = edges[i ^ 1].to;
        }
    }
    return tot_cost;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n), st = 0, ed = n * 2 + 1;
    for (int i = 1; i <= n; i++)
        addtube(st, i, 1, 0), addtube(i + n, ed, 1, 0);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", &ci[i][j]), addtube(i, j + n, 1, ci[i][j]);
    printf("%lld\n", mfmc());
    memset(head, -1, sizeof(head)), current = 0;
    for (int i = 1; i <= n; i++)
        addtube(st, i, 1, 0), addtube(i + n, ed, 1, 0);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            addtube(i, j + n, 1, -ci[i][j]);
    printf("%lld\n", -mfmc());
    return 0;
}