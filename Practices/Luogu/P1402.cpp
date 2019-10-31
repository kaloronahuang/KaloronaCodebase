// P1402.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010, INF = 0x3f3f3f3f;

int head[MAX_N], current, n, p, q, dep[MAX_N], st, ed, cur[MAX_N], hotel_cnt[MAX_N], ht[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N * 200];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void addtube(int src, int dst, int weight)
{
    addpath(src, dst, weight), addpath(dst, src, 0);
}

bool bfs()
{
    memset(dep, 0, sizeof(dep));
    queue<int> q;
    q.push(st), dep[st] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (edges[i].weight > 0 && dep[edges[i].to] == 0)
                dep[edges[i].to] = dep[u] + 1, q.push(edges[i].to);
    }
    return dep[ed] != 0;
}

int dfs(int u, int flow)
{
    if (u == ed || flow == 0)
        return flow;
    for (int &i = cur[u]; i != -1; i = edges[i].nxt)
        if (dep[edges[i].to] == dep[u] + 1 && edges[i].weight > 0)
            if (int di = dfs(edges[i].to, min(flow, edges[i].weight)))
            {
                edges[i].weight -= di, edges[i ^ 1].weight += di;
                return di;
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

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &p, &q);
    st = p + q + n + n + 1, ed = st + 1;
    for (int i = 1; i <= p; i++)
        addtube(st, i, 1);
    for (int i = 1; i <= q; i++)
        addtube(i + n + n + p, ed, 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1, tmp; j <= p; j++)
        {
            scanf("%d", &tmp);
            if (tmp == 1)
                addtube(j, i + p, 1);
        }
    for (int i = 1; i <= n; i++)
        addtube(i + p, i + p + n, 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1, tmp; j <= q; j++)
        {
            scanf("%d", &tmp);
            if (tmp == 1)
                addtube(i + p + n, j + p + n + n, 1);
        }
    printf("%d", dinic());
    return 0;
}