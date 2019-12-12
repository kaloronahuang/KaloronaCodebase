// LOJ6013.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110, INF = 0x3f3f3f3f;

int n, ai[MAX_N], avg, head[MAX_N], current, flow[MAX_N], pre[MAX_N];
int st, ed, dist[MAX_N];
bool vis[MAX_N];

struct edge
{
    int to, nxt, weight, cost;
} edges[MAX_N * MAX_N << 1];

void addpath(int src, int dst, int weight, int cost)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].cost = cost, edges[current].weight = weight;
    head[src] = current++;
}

void addtube(int src, int dst, int weight, int cost)
{
    addpath(src, dst, weight, cost);
    addpath(dst, src, 0, -cost);
}

bool bfs()
{
    memset(vis, false, sizeof(vis)), memset(dist, 0x3f, sizeof(dist));
    memset(flow, 0x3f, sizeof(flow)), memset(pre, -1, sizeof(pre));
    queue<int> q;
    q.push(st), dist[st] = 0, vis[st] = true;
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), vis[u] = false;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[edges[i].to] > dist[u] + edges[i].cost && edges[i].weight > 0)
            {
                dist[edges[i].to] = dist[u] + edges[i].cost;
                pre[edges[i].to] = i, flow[edges[i].to] = min(flow[u], edges[i].weight);
                if (vis[edges[i].to] == false)
                    q.push(edges[i].to), vis[edges[i].to] = true;
            }
    }
    return pre[ed] != -1;
}

int mfmc()
{
    int cost = 0, flw = 0;
    while (bfs())
    {
        flw += flow[ed], cost += flow[ed] * dist[ed];
        int p = ed;
        while (p != st)
            edges[pre[p]].weight -= flow[ed], edges[pre[p] ^ 1].weight += flow[ed], p = edges[pre[p] ^ 1].to;
    }
    return cost;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), avg += ai[i];
    st = n + 1, ed = st + 1, avg /= n;
    for (int i = 1; i <= n; i++)
        addtube(i, ed, avg, 0);
    for (int i = 1; i <= n; i++)
        addtube(i, i % n + 1, INF, 1), addtube(i % n + 1, i, INF, 1);
    for (int i = 1; i <= n; i++)
        addtube(st, i, ai[i], 0);
    printf("%d\n", mfmc());
    return 0;
}