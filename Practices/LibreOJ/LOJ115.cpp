// LOJ115.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 220, MAX_E = 20400;

int n, m, head[MAX_N], current, di[MAX_N], start_pos, end_pos, dep[MAX_N], cur[MAX_N], idx[MAX_E], lowers[MAX_E];

struct edge
{
    int to, nxt, weight;
    bool tag;
} edges[MAX_E << 1];

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
    q.push(start_pos), dep[start_pos] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dep[edges[i].to] == 0 && edges[i].weight > 0)
                dep[edges[i].to] = dep[u] + 1, q.push(edges[i].to);
    }
    return dep[end_pos] != 0;
}

int dfs(int u, int flow)
{
    if (flow == 0 || u == end_pos)
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
    int ret = 0;
    while (bfs())
    {
        memcpy(cur, head, sizeof(head));
        while (int di = dfs(start_pos, 0x3f3f3f3f))
            ret += di;
    }
    return ret;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m), start_pos = n + 1, end_pos = n + 2;
    for (int i = 1, u, v, lower, upper; i <= m; i++)
    {
        scanf("%d%d%d%d", &u, &v, &lower, &upper);
        idx[i] = current, addtube(u, v, upper - lower), di[u] -= lower, di[v] += lower, lowers[i] = lower;
    }
    for (int i = 1; i <= n; i++)
        if (di[i] < 0)
            addtube(i, end_pos, -di[i]);
        else if (di[i] > 0)
            addtube(start_pos, i, di[i]);
    dinic();
    bool flag = true;
    for (int i = head[start_pos]; i != -1; i = edges[i].nxt)
        flag &= (edges[i].weight == 0);
    if (flag)
    {
        puts("YES");
        for (int i = 1; i <= m; i++)
            printf("%d\n", edges[idx[i] ^ 1].weight + lowers[i]);
    }
    else
        puts("NO");
    return 0;
}