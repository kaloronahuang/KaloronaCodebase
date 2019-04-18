// LOJ6008.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 8010, MAX_M = 1e6 + 2000, INF = 0x3f3f3f3f;
int head[MAX_N], current, n, ri[MAX_N], P, M, F, N, S, st, ed, dist[MAX_N], flow[MAX_N], pre[MAX_N];
bool vis[MAX_N];
struct edge
{
    int to, nxt, weight, cost;
} edges[MAX_M];
void addpath(int u, int v, int w, int c)
{
    edges[current].to = v, edges[current].weight = w, edges[current].cost = c;
    edges[current].nxt = head[u], head[u] = current++;
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
    scanf("%d%d%d%d%d%d", &n, &P, &M, &F, &N, &S);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ri[i]);
    ed = (n << 1) + 1;
    for (int i = 1; i <= n; i++)
    {
        addtube(st, i, INF, P), addtube(st, i + n, ri[i], 0), addtube(i, ed, ri[i], 0);
        if (i + M <= n)
            addtube(i + n, i + M, INF, F);
        if (i + N <= n)
            addtube(i + n, i + N, INF, S);
    }
    for (int i = 1; i < n; i++)
        addtube(i + n, i + n + 1, INF, 0);
    printf("%lld", mfmc());
    return 0;
}