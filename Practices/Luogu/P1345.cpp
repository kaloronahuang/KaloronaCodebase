// P1345.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010, INF = 0x3f3f3f3f;

int head[MAX_N], current, n, m, c1, c2, dep[MAX_N], cur[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N * MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void addtube(int src, int dst, int weight)
{
    addpath(src, dst, weight);
    addpath(dst, src, 0);
}

bool bfs()
{
    memset(dep, 0, sizeof(dep));
    queue<int> q;
    q.push(c1), dep[c1] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dep[edges[i].to] == 0 && edges[i].weight > 0)
                dep[edges[i].to] = dep[u] + 1, q.push(edges[i].to);
    }
    return dep[c2] != 0;
}

int dfs(int u, int flow)
{
    if (u == c2 || flow == 0)
        return flow;
    for (int &i = cur[u]; i != -1; i = edges[i].nxt)
        if (dep[edges[i].to] == dep[u] + 1 && edges[i].weight > 0)
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

int dinic()
{
    int ans = 0;
    while (bfs())
    {
        memcpy(cur, head, sizeof(head));
        while (int di = dfs(c1, INF))
            ans += di;
    }
    return ans;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d%d", &n, &m, &c1, &c2);
    c1 += n;
    for (int i = 1; i <= n; i++)
        addtube(i, i + n, 1);
    for (int i = 1, u, v; i <= m; i++)
    {
        scanf("%d%d", &u, &v);
        addtube(u + n, v, INF);
        addtube(v + n, u, INF);
    }
    printf("%d", dinic());
    return 0;
}