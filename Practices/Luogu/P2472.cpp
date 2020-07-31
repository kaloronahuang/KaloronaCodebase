// P2472.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010, INF = 0x3f3f3f3f;

int n, m, d, head[MAX_N], current, dep[MAX_N], cur[MAX_N];
int start_pos, end_pos, ptot, height[MAX_N][MAX_N];
char mp[MAX_N][MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N * MAX_N << 2];

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
        memcpy(cur, head, sizeof(head));
        while (int di = dfs(start_pos, INF))
            ret += di;
    }
    return ret;
}

int getId(int x, int y) { return 1LL * (x - 1) * m + y; }

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &m, &d), start_pos = (2 * n * m) + 1, end_pos = start_pos + 1;
    for (int i = 1; i <= n; i++)
        scanf("%s", mp[i] + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            height[i][j] = mp[i][j] - '0';
    for (int i = 1; i <= n; i++)
        scanf("%s", mp[i] + 1);
    int sum = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            if (mp[i][j] == 'L')
                addtube(start_pos, getId(i, j), 1), sum++;
            if (height[i][j] > 0)
            {
                addtube(getId(i, j), getId(i, j) + n * m, height[i][j]);
                if (i <= d || j <= d || i + d > n || j + d > m)
                    addtube(getId(i, j) + n * m, end_pos, INF);
            }
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (height[i][j] > 0)
                for (int a = 1; a <= n; a++)
                    for (int b = 1; b <= m; b++)
                        if (height[a][b] > 0)
                            if (make_pair(i, j) != make_pair(a, b) && 1LL * d * d >= (i - a) * (i - a) + (j - b) * (j - b))
                                addtube(getId(i, j) + n * m, getId(a, b), INF);
    printf("%d\n", sum - dinic());
    return 0;
}