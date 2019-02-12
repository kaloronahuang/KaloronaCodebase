// P4174.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 96000, INF = 0x3f3f3f3f;
int n, m, s, t, head[MAX_N], current, tmpx, tmpy, dep[MAX_N], cur[MAX_N], tmpz;
struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 2];
void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}
void add(int src, int dst, int weight) { addpath(src, dst, weight), addpath(dst, src, 0); }
bool bfs()
{
    memset(dep, 0, sizeof(dep));
    queue<int> q;
    q.push(s), dep[s] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (edges[i].weight > 0 && !dep[edges[i].to])
                q.push(edges[i].to), dep[edges[i].to] = dep[u] + 1;
    }
    return dep[t] != 0;
}
int dfs(int u, int flow)
{
    if (u == t || flow == 0)
        return flow;
    for (int &i = cur[u]; i != -1; i = edges[i].nxt)
        if (dep[edges[i].to] == dep[u] + 1 && edges[i].weight > 0)
        {
            int to = edges[i].to, fl = dfs(edges[i].to, min(edges[i].weight, flow));
            if (fl > 0)
            {
                edges[i].weight -= fl, edges[i ^ 1].weight += fl;
                return fl;
            }
        }
    return 0;
}
int dinic()
{
    int ans = 0;
    while (bfs())
    {
        for (int i = 1; i <= m + n + 2; i++)
            cur[i] = head[i];
        while (int fl = dfs(s, INF))
            ans += fl;
    }
    return ans;
}
int main()
{
    scanf("%d%d", &n, &m);
    s = n + m + 1, t = s + 1;
    memset(head, -1, sizeof(head));
    for (int i = 1; i <= n; i++)
        scanf("%d", &tmpx), add(i + m, t, tmpx);
    int ans = 0;
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &tmpx, &tmpy, &tmpz), ans += tmpz, add(s, i, tmpz), add(i, tmpx + m, INF), add(i, tmpy + m, INF);
    ans -= dinic();
    printf("%d", ans);
    return 0;
}