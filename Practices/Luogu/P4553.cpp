// P4553.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 420, INF = 0x3f3f3f3f;

int n, m, start_pos, end_pos, gS, gT, head[MAX_N], current, di[MAX_N];
int dist[MAX_N], flow[MAX_N], pre[MAX_N], vi[MAX_N], valve;
bool vis[MAX_N];

struct edge
{
    int to, nxt, weight, cost;
} edges[MAX_N * MAX_N << 2];

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

void addtube(int src, int dst, int L, int R, int cost)
{
    addtube(src, dst, R - L, cost), di[dst] += L, di[src] -= L;
}

bool spfa()
{
    memset(dist, 0x3f, sizeof(dist));
    memset(pre, -1, sizeof(pre)), memset(vis, false, sizeof(vis));
    queue<int> q;
    q.push(start_pos), flow[start_pos] = INF, vis[start_pos] = true, dist[start_pos] = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), vis[u] = false;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (edges[i].weight > 0 && dist[edges[i].to] > dist[u] + edges[i].cost)
            {
                dist[edges[i].to] = dist[u] + edges[i].cost;
                pre[edges[i].to] = i, flow[edges[i].to] = min(flow[u], edges[i].weight);
                if (!vis[edges[i].to])
                    q.push(edges[i].to), vis[edges[i].to] = true;
            }
    }
    return dist[end_pos] != INF;
}

int mfmc()
{
    int ret = 0;
    while (spfa())
    {
        int u = end_pos, i;
        ret += dist[end_pos] * flow[end_pos];
        while (u != start_pos)
        {
            i = pre[u];
            edges[i].weight -= flow[end_pos], edges[i ^ 1].weight += flow[end_pos];
            u = edges[i ^ 1].to;
        }
    }
    return ret;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    gS = (n << 1) + 1, valve = gS + 1, gT = valve + 1, start_pos = gT + 1, end_pos = start_pos + 1;
    for (int i = 1; i <= n; i++)
        scanf("%d", &vi[i]);
    addtube(gS, valve, m, 0);
    for (int i = 1; i <= n; i++)
        addtube(valve, i, m, 0), addtube(i + n, gT, m, 0), addtube(i, i + n, vi[i], vi[i], 0);
    for (int i = 1; i <= n; i++)
        for (int j = i + 1, x; j <= n; j++)
        {
            scanf("%d", &x);
            if (x != -1)
                addtube(i + n, j, m, x);
        }
    addtube(gT, gS, m, 0);
    for (int i = 1; i <= gT; i++)
        if (di[i] < 0)
            addtube(i, end_pos, -di[i], 0);
        else if (di[i] > 0)
            addtube(start_pos, i, di[i], 0);
    printf("%d\n", mfmc());
    return 0;
}