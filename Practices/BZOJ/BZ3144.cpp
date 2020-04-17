// BZ3144.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 45, MAX_NODE = MAX_N * MAX_N * MAX_N + 110, MAX_E = MAX_NODE * 12, INF = 0x3f3f3f3f;
const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};

int p, q, r, d, head[MAX_NODE], cur[MAX_NODE], current, dep[MAX_NODE], start_pos, end_pos, mat[MAX_N][MAX_N][MAX_N];
bool vis[MAX_NODE];

struct edge
{
    int to, nxt, weight;
} edges[MAX_E << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void addtube(int src, int dst, int weight) { addpath(src, dst, weight), addpath(dst, src, 0); }

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
            if (edges[i].weight > 0 && dep[edges[i].to] == 0)
                dep[edges[i].to] = dep[u] + 1, q.push(edges[i].to);
    }
    return dep[end_pos] != 0;
}

int dfs(int u, int flow)
{
    if (flow == 0 || u == end_pos)
        return flow;
    for (int &i = cur[u]; i != -1; i = edges[i].nxt)
        if (edges[i].weight > 0 && dep[edges[i].to] == dep[u] + 1)
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

int getId(int x, int y, int z) { return (x - 1) * p * q + (y - 1) * q + z; }

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d%d", &p, &q, &r, &d);
    start_pos = getId(r + 1, p, q) + 1, end_pos = start_pos + 1;
    for (int i = 1; i <= r; i++)
        for (int j = 1; j <= p; j++)
            for (int k = 1; k <= q; k++)
                scanf("%d", &mat[i][j][k]), addtube(getId(i, j, k), getId(i + 1, j, k), mat[i][j][k]);
    for (int j = 1; j <= p; j++)
        for (int k = 1; k <= q; k++)
            addtube(start_pos, getId(1, j, k), INF), addtube(getId(r + 1, j, k), end_pos, INF);
    for (int i = d + 1; i <= r + 1; i++)
        for (int j = 1; j <= p; j++)
            for (int k = 1; k <= q; k++)
                for (int dir = 0; dir < 4; dir++)
                    if (j + dx[dir] <= p && j + dx[dir] >= 1 && k + dy[dir] <= q && k + dy[dir] >= 1)
                        addtube(getId(i, j, k), getId(i - d, j + dx[dir], k + dy[dir]), INF);
    printf("%d\n", dinic());
    return 0;
}