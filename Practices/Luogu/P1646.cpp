// P1646.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110, MAX_P = 6 * MAX_N * MAX_N, INF = 0x3f3f3f3f;

int n, m, art[MAX_N][MAX_N], stem[MAX_N][MAX_N], nrart[MAX_N][MAX_N];
int nrstem[MAX_N][MAX_N], ncart[MAX_N][MAX_N], ncstem[MAX_N][MAX_N];
int head[MAX_P], current, dep[MAX_P], start_pos, end_pos, cur[MAX_P], ptot;

struct edge
{
    int to, nxt, weight;
} edges[int(5e6 + 20000)];

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
            if (edges[i].weight > 0 && dep[edges[i].to] == 0)
                dep[edges[i].to] = dep[u] + 1, q.push(edges[i].to);
    }
    return dep[end_pos] != 0;
}

int dfs(int u, int flow)
{
    if (u == end_pos || flow == 0)
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
        memcpy(cur, head, sizeof(int) * (ptot + 5));
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
    start_pos = n * m + 1, ptot = end_pos = start_pos + 1;
    int ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            scanf("%d", &art[i][j]), ans += art[i][j];
            addtube(start_pos, getId(i, j), art[i][j]);
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            scanf("%d", &stem[i][j]), ans += stem[i][j];
            addtube(getId(i, j), end_pos, stem[i][j]);
        }
    for (int i = 1; i <= n - 1; i++)
        for (int j = 1; j <= m; j++)
        {
            scanf("%d", &nrart[i][j]), ans += nrart[i][j];
            addtube(start_pos, ++ptot, nrart[i][j]);
            addtube(ptot, getId(i, j), INF);
            addtube(ptot, getId(i + 1, j), INF);
        }
    for (int i = 1; i <= n - 1; i++)
        for (int j = 1; j <= m; j++)
        {
            scanf("%d", &nrstem[i][j]), ans += nrstem[i][j];
            addtube(++ptot, end_pos, nrstem[i][j]);
            addtube(getId(i, j), ptot, INF);
            addtube(getId(i + 1, j), ptot, INF);
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m - 1; j++)
        {
            scanf("%d", &ncart[i][j]), ans += ncart[i][j];
            addtube(start_pos, ++ptot, ncart[i][j]);
            addtube(ptot, getId(i, j), INF);
            addtube(ptot, getId(i, j + 1), INF);
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m - 1; j++)
        {
            scanf("%d", &ncstem[i][j]), ans += ncstem[i][j];
            addtube(++ptot, end_pos, ncstem[i][j]);
            addtube(getId(i, j), ptot, INF);
            addtube(getId(i, j + 1), ptot, INF);
        }
    printf("%d\n", ans - dinic());
    return 0;
}