// P3376.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 11000, MAX_M = 210000, INF = 0x3f3f3f3f;
int n, m, s, t, head[MAX_N], dep[MAX_N], current, tmpx, tmpy, tmpz;
struct edge
{
    int to, nxt, weight;
} edges[MAX_M];
void addpath(int src, int dst, int w)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = w, head[src] = current++;
}
void add(int u, int v, int w) { addpath(u, v, w), addpath(v, u, 0); }
bool bfs()
{
    memset(dep, 0, sizeof(dep));
    queue<int> q;
    q.push(s), dep[s] = 1;
    do
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (edges[i].weight > 0 && !dep[edges[i].to])
                dep[edges[i].to] = dep[u] + 1, q.push(edges[i].to);
    } while (!q.empty());
    if (dep[t] == 0)
        return false;
    return true;
}
int dfs(int u, int flow)
{
    if (u == t || flow == 0)
        return flow;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (dep[u] + 1 == dep[edges[i].to] && edges[i].weight != 0)
        {
            int di = dfs(edges[i].to, min(flow, edges[i].weight));
            if (di > 0)
            {
                edges[i].weight -= di, edges[i ^ 1].weight += di;
                return di;
            }
        }
    return 0;
}
int Dinic()
{
    int ans = 0;
    while (bfs())
        while (int d = dfs(s, INF))
            ans += d;
    return ans;
}
int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d%d", &n, &m, &s, &t);
    for (int i = 0; i < m; i++)
        scanf("%d%d%d", &tmpx, &tmpy, &tmpz), add(tmpx, tmpy, tmpz);
    printf("%d", Dinic());
    return 0;
}