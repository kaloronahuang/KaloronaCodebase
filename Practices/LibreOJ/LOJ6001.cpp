// LOJ6001.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 2000, INF = 0x3f3f3f3f;
int m, n, s, t, head[MAX_N], current, cur[MAX_N], dep[MAX_N], tmpx;
bool vis[MAX_N];
string tmp;
struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 2];
void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}
bool bfs()
{
    memset(dep, 0, sizeof(dep)), memset(vis, 0, sizeof(vis));
    queue<int> q;
    q.push(s), dep[s] = 1;
    do
    {
        int u = q.front();
        q.pop(), vis[u] = true;
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
            int to = edges[i].to, fl = dfs(to, min(flow, edges[i].weight));
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
        for (int i = 1; i <= n + m + 2; i++)
            cur[i] = head[i];
        while (int flow = dfs(s, INF))
            ans += flow;
    }
    return ans;
}
int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d\n", &m, &n);
    s = n + m + 1, t = s + 1;
    int ans = 0;
    for (int i = 1; i <= m; i++)
    {
        getline(cin, tmp);
        stringstream ss;
        ss << tmp, ss >> tmpx;
        addpath(s, i, tmpx), addpath(i, s, 0);
        ans += tmpx;
        while (ss >> tmpx)
            addpath(i, tmpx + m, INF), addpath(tmpx + m, i, 0);
    }
    for (int i = 1; i <= n; i++)
        scanf("%d", &tmpx), addpath(i + m, t, tmpx), addpath(t, i + m, 0);
    ans -= dinic();
    queue<int> q;
    for (int i = 1; i <= m; i++)
        if (vis[i])
            q.push(i);
    while (!q.empty())
    {
        int pt = q.front();
        q.pop(), printf("%d", pt);
        if (!q.empty())
            printf(" ");
    }
    puts("");
    for (int i = 1; i <= n; i++)
        if (vis[i + m])
            q.push(i);
    while (!q.empty())
    {
        int pt = q.front();
        q.pop(), printf("%d", pt);
        if (!q.empty())
            printf(" ");
    }
    puts("");
    printf("%d", ans);
    return 0;
}