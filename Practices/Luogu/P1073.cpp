// P1073.cpp
#include <bits/stdc++.h>

using namespace std;

const int MX_N = 100200;

int n, m, cost[MX_N];

struct edge
{
    int to, nxt;
};

struct graph
{
    int head[MX_N], current = 0, D[MX_N];
    bool vis[MX_N];
    edge edges[500200 << 1];

    graph(char defaultValue = 0)
    {
        memset(head, -1, sizeof(head));
        memset(D, defaultValue, sizeof(D));
    }

    void addpath(int src, int dst)
    {
        edges[current].to = dst, edges[current].nxt = head[src];
        head[src] = current++;
    }

    void bfs_min(int u)
    {
        queue<int> q;
        q.push(u);
        vis[u] = true, D[u] = cost[u];
        while (!q.empty())
        {
            int curt = q.front();
            q.pop();
            vis[curt] = 0;
            for (int i = head[curt]; i != -1; i = edges[i].nxt)
            {
                int to = edges[i].to;
                if (D[to] > min(D[curt], cost[to]))
                {
                    D[to] = min(D[curt], cost[to]);
                    if (!vis[to])
                        vis[to] = true, q.push(to);
                }
            }
        }
    }

    void bfs_max(int u)
    {
        queue<int> q;
        q.push(u);
        vis[u] = true, D[u] = cost[u];
        while (!q.empty())
        {
            int curt = q.front();
            q.pop();
            vis[curt] = 0;
            for (int i = head[curt]; i != -1; i = edges[i].nxt)
            {
                int to = edges[i].to;
                if (D[to] < max(D[curt], cost[to]))
                {
                    D[to] = max(D[curt], cost[to]);
                    if (!vis[to])
                        vis[to] = true, q.push(to);
                }
            }
        }
    }
} * posG, *negG;

int main()
{
    posG = new graph(0x3f), negG = new graph(0);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &cost[i]);
    for (int i = 1; i <= m; i++)
    {
        int src, dst, mode;
        scanf("%d%d%d", &src, &dst, &mode);
        posG->addpath(src, dst), negG->addpath(dst, src);
        if (mode == 2)
            posG->addpath(dst, src), negG->addpath(src, dst);
    }
    posG->bfs_min(1);
    negG->bfs_max(n);
    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans = max(ans, negG->D[i] - posG->D[i]);
    printf("%d", ans);
    delete posG;
    delete negG;
    return 0;
}