// P2825.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, INF = 0x3f3f3f3f;

int n, m, head[MAX_N], current, dep[MAX_N], cur[MAX_N], mem[MAX_N], start_pos, end_pos;
char mp[55][55];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

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

int getId(int x, int y) { return (x - 1) * m + y; }

int find(int x) { return mem[x] == x ? x : mem[x] = find(mem[x]); }

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

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", mp[i] + 1);
        for (int j = 1; j <= m; j++)
            mem[getId(i, j)] = getId(i, j);
    }
    // columns;
    start_pos = 3 * n * m + 1, end_pos = start_pos + 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (mp[i - 1][j] == '*' || mp[i - 1][j] == 'x')
                mem[getId(i, j)] = find(getId(i - 1, j));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            if (find(getId(i, j)) == getId(i, j))
                addtube(start_pos, getId(i, j), 1);
            if (mp[i][j] == '*')
                addtube(find(getId(i, j)), getId(i, j) + n * m, 1);
        }
    // rows;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            mem[getId(i, j)] = getId(i, j);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (mp[i][j - 1] == '*' || mp[i][j - 1] == 'x')
                mem[getId(i, j)] = find(getId(i, j - 1));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            if (find(getId(i, j)) == getId(i, j))
                addtube(getId(i, j) + 2LL * n * m, end_pos, 1);
            if (mp[i][j] == '*')
                addtube(getId(i, j) + n * m, find(getId(i, j)) + 2LL * n * m, 1);
        }
    printf("%d\n", dinic());
    return 0;
}