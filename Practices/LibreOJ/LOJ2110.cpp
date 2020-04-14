// LOJ2110.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3030, INF = 0x3f3f3f3f;

int n, m, p, head[MAX_N], current, dp[MAX_N][1 << 10], cseq[15], color[15], colorSet, id[MAX_N], g[1 << 10], f[1 << 10];
bool vis[MAX_N];
queue<int> q;

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void spfa(int stat)
{
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), vis[u] = false;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dp[edges[i].to][stat] > dp[u][stat] + edges[i].weight)
            {
                dp[edges[i].to][stat] = dp[u][stat] + edges[i].weight;
                if (!vis[edges[i].to])
                    q.push(edges[i].to), vis[edges[i].to] = true;
            }
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &m, &p);
    for (int i = 1, u, v, w; i <= m; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
    for (int i = 1, c; i <= p; i++)
        scanf("%d%d", &c, &cseq[i]), id[cseq[i]] = i, color[c] |= (1 << (i - 1)), colorSet |= 1 << (c - 1);
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 1; i <= n; i++)
    {
        if (id[i] != 0)
            dp[i][1 << (id[i] - 1)] = 0;
        dp[i][0] = 0;
    }
    for (int stat = 1; stat < (1 << p); stat++)
    {
        for (int subset = stat & (stat - 1); subset; subset = (subset - 1) & stat)
            for (int i = 1; i <= n; i++)
                if (dp[i][subset] < INF && dp[i][stat ^ subset] < INF)
                    dp[i][stat] = min(dp[i][stat], dp[i][subset] + dp[i][stat ^ subset]);
        for (int i = 1; i <= n; i++)
        {
            vis[i] = false;
            if (dp[i][stat] != INF)
                q.push(i), vis[i] = true;
        }
        spfa(stat);
        g[stat] = INF;
        for (int i = 1; i <= n; i++)
            g[stat] = min(g[stat], dp[i][stat]);
    }
    for (int stat = colorSet; stat; stat = (stat - 1) & colorSet)
    {
        int S = 0;
        for (int i = 0; i < p; i++)
            if (stat & (1 << i))
                S |= color[i + 1];
        f[stat] = g[S];
    }
    for (int stat = 1; stat <= colorSet; stat++)
        for (int subset = (stat - 1) & stat; subset; subset = (subset - 1) & stat)
            f[stat] = min(f[stat], f[subset] + f[stat ^ subset]);
    printf("%d\n", f[colorSet]);
    return 0;
}