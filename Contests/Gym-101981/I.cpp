// I.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 5000, MAX_M = 2e6 + 2000, INF = 0x3f3f3f3f;
int head[MAX_N], current, n, m, k, s, t, cur[MAX_N], dep[MAX_N], witch;
struct edge
{
    int to, weight, nxt;
} edges[MAX_M];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void add(int src, int dst, int weight) { addpath(src, dst, weight), addpath(dst, src, 0); }

bool bfs()
{
    memset(dep, 0, sizeof(dep));
    queue<int> q;
    q.push(s), dep[s] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (edges[i].weight > 0 && dep[edges[i].to] == 0)
                dep[edges[i].to] = dep[u] + 1, q.push(edges[i].to);
    }
    return dep[t] != 0;
}

int dfs(int u, int flow)
{
    if (u == t || flow == 0)
        return flow;
    for (int &i = cur[u]; i != -1; i = edges[i].nxt)
        if (edges[i].weight > 0 && dep[edges[i].to] == dep[u] + 1)
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
        while (int di = dfs(s, INF))
            ans += di;
    }
    return ans;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &m, &k);
    t = n + m + 2, s = 0, witch = n + m + 1;
    add(s, witch, k);
    for (int i = 1; i <= n; i++)
        add(s, i, 1), add(witch, i, 1);

    for (int i = 1; i <= n; i++)
    {
        int num;
        scanf("%d", &num);
        for (int j = 1; j <= num; j++)
        {
            int v;
            scanf("%d", &v);
            add(i, v + n, 1);
        }
    }

    for (int i = 1; i <= m; i++)
        add(i + n, t, 1);
    printf("%d", dinic());
    return 0;
}