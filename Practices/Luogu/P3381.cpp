// P3381.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 5010, MAX_M = 50020;
int n, m, s, t, head[MAX_N], dist[MAX_N], flow[MAX_N], vis[MAX_N], fa[MAX_N];
int tmpx, tmpy, tmpz, tmpw, current, last[MAX_N];
int maxflow, mincost;
struct edge
{
    int to, nxt, weight, cost;
} edges[MAX_M << 1];
void addpath(int u, int v, int w, int c)
{
    edges[current].to = v, edges[current].nxt = head[u];
    edges[current].weight = w, edges[current].cost = c;
    head[u] = current++;
}
void add(int u, int v, int w, int c) { addpath(u, v, w, c), addpath(v, u, 0, -c); }
bool spfa()
{
    queue<int> q;
    memset(dist, 0x3f, sizeof(dist)), memset(flow, 0x3f, sizeof(flow));
    memset(vis, 0, sizeof(vis)), q.push(s);
    vis[s] = true, fa[t] = -1, dist[s] = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), vis[u] = false;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (edges[i].weight > 0 && dist[edges[i].to] > dist[u] + edges[i].cost)
            {
                dist[edges[i].to] = dist[u] + edges[i].cost;
                fa[edges[i].to] = u, last[edges[i].to] = i;
                flow[edges[i].to] = min(flow[u], edges[i].weight);
                if (!vis[edges[i].to])
                    vis[edges[i].to] = true, q.push(edges[i].to);
            }
    }
    return fa[t] != -1;
}
void costDinic()
{
    while (spfa())
    {
        int now = t;
        maxflow += flow[t], mincost += dist[t] * flow[t];
        while (now != s)
        {
            edges[last[now]].weight -= flow[t];
            edges[last[now] ^ 1].weight += flow[t];
            now = fa[now];
        }
    }
}
int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d%d", &n, &m, &s, &t);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d%d", &tmpx, &tmpy, &tmpz, &tmpw), add(tmpx, tmpy, tmpz, tmpw);
    costDinic();
    printf("%d %d", maxflow, mincost);
    return 0;
}