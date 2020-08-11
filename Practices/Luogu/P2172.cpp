// P2172.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, MAX_M = 2e5 + 200, INF = 0x3f3f3f3f;

int n, m, head[MAX_N], current, cur[MAX_N], start_pos, end_pos, dep[MAX_N], r, c;
char mp[55][55];

struct edge
{
    int to, nxt, weight;
} edges[MAX_M << 2];

struct seg
{
    int u, v, w;
    bool operator<(const seg &rhs) const { return w < rhs.w; }
} segs[MAX_M];

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
    scanf("%d%d%d%d", &n, &m, &r, &c), start_pos = 2 * n * m + 1, end_pos = start_pos + 1;
    for (int i = 1; i <= n; i++)
        scanf("%s", mp[i] + 1);
    int sum = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            addtube(start_pos, getId(i, j), 1);
            addtube(getId(i, j) + n * m, end_pos, 1);
            sum += (mp[i][j] == 'x');
            if (mp[i][j] == '.')
                for (int a = i; a <= n; a++)
                    for (int b = 1; b <= m; b++)
                        if (mp[a][b] == '.')
                            if ((abs(a - i) == r && abs(b - j) == c) || (abs(a - i) == c && abs(b - j) == r))
                                addtube(getId(i, j), getId(a, b) + n * m, 1);
        }
    printf("%d\n", n * m - sum - dinic());
    return 0;
}