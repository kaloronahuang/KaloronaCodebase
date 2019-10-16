// LOJ6011.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110, INF = 0x3f3f3f3f;

int head[MAX_N * 10], current, n, m, st, ed, tot;
int upward[MAX_N * 10], flow[MAX_N * 10], dist[MAX_N * 10];
bool vis[MAX_N * 10];

struct edge
{
    int to, nxt, weight, cost, org_w, org_c;
    void reset() { weight = org_w, cost = org_c; }
} edges[MAX_N * MAX_N * MAX_N / 10];

void addpath(int src, int dst, int weight, int cost)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, edges[current].cost = cost;
    edges[current].org_c = cost, edges[current].org_w = weight;
    head[src] = current++;
}

void addtube(int src, int dst, int weight, int cost)
{
    addpath(src, dst, weight, cost);
    addpath(dst, src, 0, -cost);
}

bool spfa_min(int src)
{
    memset(dist, 0x3f, sizeof(dist));
    memset(vis, false, sizeof(vis));
    memset(flow, 0, sizeof(flow));
    queue<int> q;
    q.push(src), vis[src] = true, dist[src] = 0;
    flow[src] = 0x3f3f3f3f;
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
                upward[edges[i].to] = i;
                if (!vis[edges[i].to])
                    q.push(edges[i].to), vis[edges[i].to] = true;
            }
    }
    return flow[ed] != 0;
}

bool spfa_max(int src)
{
    memset(dist, 128, sizeof(dist));
    memset(vis, false, sizeof(vis));
    memset(flow, 0, sizeof(flow));
    queue<int> q;
    q.push(src), vis[src] = true, dist[src] = 0;
    flow[src] = 0x3f3f3f3f;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        vis[u] = false;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[edges[i].to] < dist[u] + edges[i].cost && edges[i].weight > 0)
            {
                dist[edges[i].to] = dist[u] + edges[i].cost;
                flow[edges[i].to] = min(edges[i].weight, flow[u]);
                upward[edges[i].to] = i;
                if (!vis[edges[i].to])
                    q.push(edges[i].to), vis[edges[i].to] = true;
            }
    }
    return flow[ed] != 0;
}

int mcmf(bool (*func)(int))
{
    int ans = 0;
    while (func(st))
    {
        ans += dist[ed] * flow[ed];
        int pt = ed, i = upward[pt];
        while (pt != st)
        {
            edges[i].weight -= flow[ed], edges[i ^ 1].weight += flow[ed];
            pt = edges[i ^ 1].to, i = upward[pt];
        }
    }
    return ans;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m), tot = n + m;
    st = tot + 1, ed = st + 1;
    for (int i = 1, tmp; i <= n; i++)
        scanf("%d", &tmp), addtube(st, i, tmp, 0);
    for (int i = 1, tmp; i <= m; i++)
        scanf("%d", &tmp), addtube(i + n, ed, tmp, 0);
    for (int i = 1; i <= n; i++)
        for (int j = 1, tmp; j <= m; j++)
            scanf("%d", &tmp), addtube(i, j + n, INF, tmp);
    printf("%d\n", mcmf(spfa_min));
    for (int i = 0; i < current; i++)
        edges[i].reset();
    printf("%d\n", mcmf(spfa_max));
    return 0;
}