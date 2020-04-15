// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

int n, m, head[MAX_N], current, dfn[MAX_N], low[MAX_N], siz[MAX_N], dp[MAX_N], aff[MAX_N];
int deg[MAX_N], ncnt, ptot, topoidx[MAX_N], tot, stk[MAX_N], tail;
bool inst[MAX_N];
vector<int> G[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++ptot, inst[u] = true, stk[++tail] = u;
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
            aff[stk[tail]] = ncnt, inst[stk[tail]] = false, siz[ncnt]++;
        } while (stk[tail--] != u);
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), addpath(u, v);
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            tarjan(i);
    for (int u = 1; u <= n; u++)
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (aff[u] != aff[edges[i].to])
                G[aff[u]].push_back(aff[edges[i].to]), deg[aff[edges[i].to]]++;
    queue<int> q;
    for (int i = 1; i <= ncnt; i++)
        if (deg[i] == 0)
            q.push(i);
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), topoidx[++tot] = u;
        for (int v : G[u])
            if (--deg[v] == 0)
                q.push(v);
    }
    int ans = 0;
    for (int id = tot; id >= 1; id--)
    {
        int u = topoidx[id];
        for (int v : G[u])
            dp[u] = max(dp[u], dp[v]);
        dp[u] += siz[u];
        ans = max(ans, dp[u]);
    }
    printf("%d\n", ans);
    return 0;
}