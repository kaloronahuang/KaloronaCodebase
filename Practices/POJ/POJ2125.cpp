// POJ2125.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

const int MAX_N = 2e5 + 200, INF = 0x3f3f3f3f;

using namespace std;

int n, m, head[MAX_N], current, dep[MAX_N], cur[MAX_N], st, ed;
bool mark[MAX_N];

struct edge
{
    int to, nxt, flow;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].flow = weight, head[src] = current++;
}

void addtube(int src, int dst, int flow)
{
    addpath(src, dst, flow);
    addpath(dst, src, 0);
}

bool bfs()
{
    memset(dep, 0, sizeof(dep));
    dep[st] = 1;
    queue<int> q;
    q.push(st);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (edges[i].flow > 0 && dep[edges[i].to] == 0)
                dep[edges[i].to] = dep[u] + 1, q.push(edges[i].to);
    }
    return dep[ed] != 0;
}

int dfs(int u, int flw)
{
    if (u == ed || flw == 0)
        return flw;
    for (int &i = cur[u]; i != -1; i = edges[i].nxt)
        if (edges[i].flow > 0 && dep[edges[i].to] == dep[u] + 1)
        {
            int di = dfs(edges[i].to, min(flw, edges[i].flow));
            if (di > 0)
            {
                edges[i].flow -= di, edges[i ^ 1].flow += di;
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
        while (int di = dfs(st, INF))
            ans += di;
    }
    return ans;
}

void dfs_helper(int u)
{
    mark[u] = true;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].flow > 0 && !mark[edges[i].to])
            dfs_helper(edges[i].to);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m), st = (n << 1) | 1, ed = st + 1;
    for (int i = 1, tmpy; i <= n; i++)
        scanf("%d", &tmpy), addtube(i + n, ed, tmpy);
    for (int i = 1, tmpx; i <= n; i++)
        scanf("%d", &tmpx), addtube(st, i, tmpx);
    for (int i = 1, tmpx, tmpy; i <= m; i++)
        scanf("%d%d", &tmpx, &tmpy), addtube(tmpx, tmpy + n, INF);
    printf("%d\n", dinic());
    dfs_helper(st);
    int ans = 0;
    for (int i = 1; i <= n; i++)
        if (!mark[i])
            ans++;
    for (int i = n + 1; i <= 2 * n; i++)
        if (mark[i])
            ans++;
    printf("%d\n", ans);
    for (int i = 1; i <= n; i++)
        if (!mark[i])
            printf("%d -\n", i);
    for (int i = n + 1; i <= 2 * n; i++)
        if (mark[i])
            printf("%d +\n", i - n);
    return 0;
}