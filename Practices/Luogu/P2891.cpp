// P2891.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 1000, MAX_M = 10000, INF = 0x3f3f3f3f;
int head[MAX_N], current, n, f, d, tot, dep[MAX_N], s, t, tmp;
struct edge
{
    int to, nxt, weight;
} edges[MAX_M << 1];
void addpath(int u, int v, int w)
{
    edges[current].to = v, edges[current].nxt = head[u];
    edges[current].weight = w, head[u] = current++;
}
void add(int u, int v, int w) { addpath(u, v, w), addpath(v, u, 0); }
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
    for (int i = head[u]; i != -1; i = edges[i].nxt)
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
        while (int di = dfs(s, INF))
            ans += di;
    return ans;
}
int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &f, &d);
    s = 0, t = n * 2 + f + d + 1;
    for (int i = 1; i <= f; i++)
        add(s, i, 1);
    for (int i = 1; i <= n; i++)
        add(i + f, i + f + n, 1);
    for (int i = 1; i <= d; i++)
        add(i + 2 * n + f, t, 1);
    for (int i = 1; i <= n; i++)
    {
        int fm, dm;
        scanf("%d%d", &fm, &dm);
        while (fm--)
            scanf("%d", &tmp), add(tmp, i + f, 1);
        while (dm--)
            scanf("%d", &tmp), add(f + i + n, tmp + 2 * n + f, 1);
    }
    printf("%d", dinic());
    return 0;
}