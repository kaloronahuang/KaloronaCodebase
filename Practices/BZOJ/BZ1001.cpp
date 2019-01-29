// BZ1001.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 1e6 + 10, INF = 0x3f3f3f3f;
int n, m, head[MAX_N], tmp, current, dep[MAX_N], s, t, cur[MAX_N];
struct edge
{
    int to, nxt, weight;
} edges[MAX_N * 6];
inline int read()
{
    int s = 0, w = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            w = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
        s = s * 10 + ch - '0', ch = getchar();
    return s * w;
}
void addpath(int u, int v, int w)
{
    edges[current].to = v, edges[current].nxt = head[u];
    edges[current].weight = w, head[u] = current++;
}
bool bfs()
{
    memset(dep, 0, sizeof(dep));
    queue<int> q;
    q.push(s), dep[s] = 1;
    do
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (edges[i].weight > 0 && !dep[edges[i].to])
                dep[edges[i].to] = dep[u] + 1, q.push(edges[i].to);

    } while (!q.empty());
    return dep[t] != 0;
}
int dfs(int u, int flow)
{
    if (u == t || flow == 0)
        return flow;
    for (int &i = cur[u]; i != -1; i = edges[i].nxt)
        if (dep[edges[i].to] == dep[u] + 1 && edges[i].weight > 0)
        {
            int to = edges[i].to;
            int di = dfs(to, min(flow, edges[i].weight));
            if (di > 0)
            {
                edges[i].weight -= di, edges[i ^ 1].weight += di;
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
        for (int i = 1; i <= n * m; i++)
            cur[i] = head[i];
        while (int di = dfs(s, INF))
            ans += di;
    }
    return ans;
}
int getPt(int x, int y) { return (x - 1) * m + y; }
int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    s = getPt(1, 1), t = getPt(n, m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m - 1; j++)
            tmp = read(), addpath(getPt(i, j), getPt(i, j + 1), tmp), addpath(getPt(i, j + 1), getPt(i, j), tmp);
    for (int i = 1; i <= n - 1; i++)
        for (int j = 1; j <= m; j++)
            tmp = read(), addpath(getPt(i, j), getPt(i + 1, j), tmp), addpath(getPt(i + 1, j), getPt(i, j), tmp);
    for (int i = 1; i <= n - 1; i++)
        for (int j = 1; j <= m - 1; j++)
            tmp = read(), addpath(getPt(i, j), getPt(i + 1, j + 1), tmp), addpath(getPt(i + 1, j + 1), getPt(i, j), tmp);
    printf("%d", dinic());
    return 0;
}