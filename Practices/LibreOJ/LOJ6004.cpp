// LOJ6004.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 30000, INF = 0x3f3f3f3f;
bool vis[MAX_N];
int m, n, ri[MAX_N], ci[MAX_N], head[MAX_N], current, s, t, dep[MAX_N], cur[MAX_N];
struct edge
{
    int to, nxt, weight;
} edges[79000];
void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].weight = weight;
    edges[current].nxt = head[src], head[src] = current++;
}
void add(int src, int dst, int weight) { addpath(src, dst, weight), addpath(dst, src, 0); }
bool bfs()
{
    memset(dep, 0, sizeof(dep)), memset(vis, false, sizeof(vis));
    queue<int> q;
    q.push(s), dep[s] = 1;
    while (!q.empty())
    {
        int curt = q.front();
        q.pop(), vis[curt] = true;
        for (int i = head[curt]; i != -1; i = edges[i].nxt)
            if (edges[i].weight > 0 && !dep[edges[i].to])
                dep[edges[i].to] = dep[curt] + 1, q.push(edges[i].to);
    }
    return dep[t] != 0;
}
int dfs(int u, int flow)
{
    if (u == t || flow == 0)
        return flow;
    for (int &i = cur[u]; i != -1; i = edges[i].nxt)
        if (dep[edges[i].to] == dep[u] + 1 && edges[i].weight > 0)
        {
            int to = edges[i].to, fl = dfs(to, min(flow, edges[i].weight));
            if (fl > 0)
            {
                edges[i].weight -= fl, edges[i ^ 1].weight += fl;
                return fl;
            }
        }
    return 0;
}
int dinic()
{
    int ans = 0;
    while (bfs())
    {
        for (int i = 0; i <= t; i++)
            cur[i] = head[i];
        while (int flow = dfs(s, INF))
            ans += flow;
    }
    return ans;
}
int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &m, &n);
    int mes = 0;
    for (int i = 1; i <= m; i++)
        scanf("%d", &ri[i]), mes += ri[i];
    for (int i = 1; i <= n; i++)
        scanf("%d", &ci[i]);
    s = n + m + 1, t = n + m + 2;
    for (int i = 1; i <= m; i++)
    {
        add(s, i, ri[i]);
        for (int j = 1; j <= n; j++)
            add(i, m + j, 1);
    }
    for (int i = 1; i <= n; i++)
        add(m + i, t, ci[i]);
    if (dinic() == mes)
        puts("1");
    else
    {
        puts("0");
        return 0;
    }
    for (int mem = 1; mem <= m; mem++)
    {
        for (int i = head[mem]; i != -1; i = edges[i].nxt)
            if (edges[i].to > m && edges[i].weight == 0)
                printf("%d ", edges[i].to - m);
        printf("\n");
    }
    return 0;
}