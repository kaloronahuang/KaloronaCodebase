// P1935.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110 * 110 * 3, INF = 0x3f3f3f3f, dx[4] = {0, 0, -1, 1}, dy[4] = {1, -1, 0, 0};

int n, m, head[MAX_N], current, A[110][110], B[110][110], C[110][110];
int dep[MAX_N], start_pos, end_pos, cur[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[int(4e6 + 200)];

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

int getId(int x, int y) { return (x - 1) * m + y; }

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    int ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &A[i][j]), ans += A[i][j];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &B[i][j]), ans += B[i][j];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &C[i][j]);
    start_pos = n * m + 1, end_pos = start_pos + 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            if ((i + j) & 1)
            {
                addtube(start_pos, getId(i, j), A[i][j]);
                addtube(getId(i, j), end_pos, B[i][j]);
            }
            else
            {
                addtube(getId(i, j), end_pos, A[i][j]);
                addtube(start_pos, getId(i, j), B[i][j]);
            }
            for (int d = 0; d < 4; d++)
            {
                int dstx = i + dx[d], dsty = j + dy[d];
                if (dstx <= n && dstx >= 1 && dsty <= m && dsty >= 1)
                    addtube(getId(i, j), getId(dstx, dsty), C[i][j] + C[dstx][dsty]), ans += ((i + j) & 1) * (C[i][j] + C[dstx][dsty]);
            }
        }
    printf("%d\n", ans - dinic());
    return 0;
}