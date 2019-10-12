// P2055.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110, INF = 0x3f3f3f3f;

int head[MAX_N], n, cur[MAX_N], current, dep[MAX_N], T, enablings[2][MAX_N], st, ed;

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
    memset(dep, 0, sizeof(dep)), dep[st] = 1;
    queue<int> q;
    q.push(st);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dep[edges[i].to] == 0 && edges[i].weight > 0)
                dep[edges[i].to] = dep[u] + 1, q.push(edges[i].to);
    }
    return dep[ed] != 0;
}

int dfs(int u, int flow)
{
    if (u == ed || flow == 0)
        return flow;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (dep[edges[i].to] == dep[u] + 1 && edges[i].weight)
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
    int ret = 0;
    while (bfs())
    {
        memcpy(cur, head, sizeof(cur));
        while (int di = dfs(st, INF))
            ret += di;
    }
    return ret;
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        memset(enablings, 0, sizeof(enablings));
        memset(head, -1, sizeof(head)), current = 0;
        scanf("%d", &n), st = n + n + 1, ed = st + 1;
        int cnt = 0;
        for (int i = 1; i <= n; i++)
            scanf("%d", &enablings[0][i]);
        for (int i = 1; i <= n; i++)
            scanf("%d", &enablings[1][i]);

        for (int i = 1; i <= n; i++)
            if (enablings[0][i] && !enablings[1][i])
                addtube(st, i, 1), cnt++;
            else if (!enablings[0][i])
                addtube(st, i, 1), cnt++;
        for (int i = 1; i <= n; i++)
            if (enablings[0][i])
                addtube(i + n, ed, 1);
        for (int i = 1; i <= n; i++)
            for (int j = 1, tmp; j <= n; j++)
            {
                scanf("%d", &tmp);
                if (tmp || i == j)
                    addtube(i, j + n, 1);
            }
        puts(dinic() == cnt ? "^_^" : "T_T");
    }
    return 0;
}