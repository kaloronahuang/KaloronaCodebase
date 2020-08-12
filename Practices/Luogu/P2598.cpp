// P2598.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110 * 110, MAX_E = MAX_N * 10, INF = 0x3f3f3f3f, dx[4] = {0, 0, -1, 1}, dy[4] = {-1, 1, 0, 0};

int n, m, head[MAX_N], current, cur[MAX_N], dep[MAX_N], start_pos, end_pos, mp[110][110];

struct edge
{
    int to, nxt, weight;
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
    if (u == end_pos || flow == 0)
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
        memcpy(cur, head, sizeof(cur));
        while (int di = dfs(start_pos, INF))
            ret += di;
    }
    return ret;
}

int getId(int x, int y) { return (x - 1) * m + y; }

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m), start_pos = n * m + 1, end_pos = start_pos + 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &mp[i][j]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (mp[i][j] == 1)
                addtube(start_pos, getId(i, j), INF);
            else if (mp[i][j] == 2)
                addtube(getId(i, j), end_pos, INF);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            for (int d = 0; d < 4; d++)
            {
                int dstx = i + dx[d], dsty = j + dy[d];
                if (1 <= dstx && dstx <= n && 1 <= dsty && dsty <= m)
                    addtube(getId(i, j), getId(dstx, dsty), 1);
            }
    printf("%d\n", dinic());
    return 0;
}