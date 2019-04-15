// P2053.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 3010, MAX_M = 100010, INF = 0x3f3f3f3f;
int head[MAX_N], current, n, m, dist[MAX_N], cur[MAX_N], s, t, answer, pre[MAX_N];
bool vis[MAX_N];
struct edge
{
    int to, nxt, weight, cost;
} edges[MAX_M];
void addpath(int src, int dst, int weight, int cost)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, edges[current].cost = cost;
    head[src] = current++;
}
void add(int src, int dst, int weight, int cost)
{
    addpath(src, dst, weight, cost);
    addpath(dst, src, 0, -cost);
}
bool bfs()
{
    memset(dist, 0x3f, sizeof(dist));
    memset(vis, false, sizeof(vis));
    memset(pre, -1, sizeof(pre));
    queue<int> q;
    q.push(s), dist[s] = 0, vis[s] = true;
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), vis[u] = false;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (edges[i].weight > 0 && dist[edges[i].to] > dist[u] + edges[i].cost)
            {
                dist[edges[i].to] = dist[u] + edges[i].cost, pre[edges[i].to] = i;
                if (!vis[edges[i].to])
                    vis[edges[i].to] = true, q.push(edges[i].to);
            }
    }
    return dist[t] != INF;
}
void calc()
{
    int mv = INF;
    for (int i = pre[t]; i != -1; i = pre[edges[i ^ 1].to])
        mv = min(mv, edges[i].weight);
    answer += mv * dist[t];
    for (int i = pre[t]; i != -1; i = pre[edges[i ^ 1].to])
        edges[i].weight -= mv, edges[i ^ 1].weight += mv;
}
void mfmc()
{
    for (; bfs(); calc())
        ;
}
int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &m, &n);
    t = n + n * m + 1;
    for (int i = 1; i <= n; i++)
        add(s, i, 1, 0);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            int cst;
            scanf("%d", &cst);
            for (int k = 1; k <= n; k++)
                add(i, j * n + k, 1, cst * k);
        }
    for (int i = n + 1; i < t; i++)
        add(i, t, 1, 0);
    mfmc();
    printf("%.2lf", double(answer) / double(n));
    return 0;
}