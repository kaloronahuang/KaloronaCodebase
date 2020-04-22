// P3530.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 660;

int n, m1, m2, head[MAX_N], current, dist[MAX_N][MAX_N], dfn[MAX_N], low[MAX_N], stk[MAX_N], tail, ptot, aff[MAX_N], ncnt, dp[MAX_N];
bool inst[MAX_N];
vector<int> sccs[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[int(2e5 + 200)];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++ptot, stk[++tail] = u, inst[u] = true;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (dfn[edges[i].to] == 0)
            tarjan(edges[i].to), low[u] = min(low[u], low[edges[i].to]);
        else if (inst[edges[i].to])
            low[u] = min(low[u], dfn[edges[i].to]);
    if (dfn[u] == low[u])
    {
        ncnt++;
        do
        {
            aff[stk[tail]] = ncnt, inst[stk[tail]] = false, sccs[ncnt].push_back(stk[tail]);
        } while (stk[tail--] != u);
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    memset(dist, 0x3f, sizeof(dist));
    scanf("%d%d%d", &n, &m1, &m2);
    for (int i = 1; i <= n; i++)
        dist[i][i] = 0;
    for (int i = 1, u, v; i <= m1; i++)
    {
        scanf("%d%d", &u, &v), addpath(u, v, -1), addpath(v, u, 1);
        dist[u][v] = min(dist[u][v], -1), dist[v][u] = min(dist[v][u], 1);
    }
    for (int i = 1, u, v; i <= m2; i++)
    {
        scanf("%d%d", &u, &v), addpath(u, v, 0);
        dist[u][v] = min(dist[u][v], 0);
    }
    for (int i = 1; i <= n; i++)
        if (dfn[i] == 0)
            tarjan(i);
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            if (aff[k] == aff[i] && dist[i][k] != 0x3f3f3f3f)
                for (int j = 1; j <= n; j++)
                    if (aff[j] == aff[i] && dist[k][j] != 0x3f3f3f3f)
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    bool flag = true;
    for (int i = 1; i <= n; i++)
        flag &= dist[i][i] >= 0;
    if (!flag)
        puts("NIE"), exit(0);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (aff[i] == aff[j])
                dp[aff[i]] = max(dp[aff[i]], dist[i][j]);
    int ans = 0;
    for (int i = 1; i <= ncnt; i++)
        ans += dp[i];
    printf("%d\n", ans + ncnt);
    return 0;
}