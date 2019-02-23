// B.cpp
#include <bits/stdc++.h>
#define pr pair<int, int>
using namespace std;
int n, m, arr[20], tmpx, tmpy;
struct edge
{
    int to, nxt, weight;
};
struct graph
{
    int head[20], current, dist[20][20], tot, loops[20];
    edge edges[20 * 19 / 2 + 200];
    bool vis[20];
    graph() { memset(head, -1, sizeof(head)); }
    void addpath(int src, int dst, int weight)
    {
        edges[current].to = dst, edges[current].nxt = head[src];
        edges[current].weight = weight, head[src] = current++;
    }
    void dijisktra(int u)
    {
        memset(dist[u], 0x3f, sizeof(dist[u]));
        memset(vis, false, sizeof(vis));
        priority_queue<pr> pq;
        pq.push(make_pair(0, u));
        dist[u][u] = 0;
        while (!pq.empty())
        {
            int curt = pq.top().second;
            pq.pop();
            if (vis[curt])
                continue;
            for (int i = head[curt]; i != -1; i = edges[i].nxt)
                if (dist[u][edges[i].to] > dist[u][curt] + edges[i].weight)
                    dist[u][edges[i].to] = dist[u][curt] + edges[i].weight, pq.push(make_pair(-dist[u][edges[i].to], edges[i].to));
        }
    }
    void getShortest()
    {
        for (int i = 1; i <= n; i++)
            dijisktra(i);
    }
    int dfs(int u, int fa, int di)
    {
        vis[u] = true;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (edges[i].to == u)
                return 1;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (edges[i].to != fa)
                return dfs(edges[i].to, u, edges[i].weight) + edges[i].weight;
        return di;
    }
    void getLoop()
    {
        memset(vis, false, sizeof(vis));
        for (int i = 1; i <= n; i++)
            if (!vis[i])
                loops[++tot] = dfs(i, 0, 0);
    }
} A, B;

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &arr[i]);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &tmpx, &tmpy);
        if (tmpx == tmpy)
            continue;
        A.addpath(tmpx, tmpy, 1), A.addpath(tmpy, tmpx, 1);
    }
    A.getShortest();
    for (int i = 1; i <= n; i++)
    {
        B.addpath(arr[i], i, max(A.dist[i][arr[i]], 1)), B.addpath(i, arr[i], max(A.dist[i][arr[i]], 1));
    }
    B.getLoop();
    int ans = 0;
    for (int i = 1; i <= B.tot; i++)
        ans += B.loops[i] - 1;
    printf("%d", ans);
    return 0;
}