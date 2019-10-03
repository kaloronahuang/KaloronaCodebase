// P3275.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAX_N = 2e5 + 200;

int head[MAX_N], n, current, m, dfn[MAX_N], low[MAX_N], ncnt, ptot;
int stk[MAX_N], tail, aff[MAX_N], deg[MAX_N], dp[MAX_N], odeg[MAX_N], siz[MAX_N];
bool inst[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N * 50];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++ptot;
    stk[++tail] = u, inst[u] = true;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (dfn[edges[i].to] == 0)
            tarjan(edges[i].to), low[u] = min(low[u], low[edges[i].to]);
        else if (inst[edges[i].to])
            low[u] = min(low[u], dfn[edges[i].to]);
    if (dfn[u] == low[u])
    {
        int color = ++ncnt;
        do
        {
            aff[stk[tail]] = color, inst[stk[tail]] = false, siz[color]++;
        } while (stk[tail--] != u);
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m), ncnt = n;
    for (int i = 1, x, u, v; i <= m; i++)
    {
        scanf("%d%d%d", &x, &u, &v);
        switch (x)
        {
        case 1:
            addpath(u, v, 0), addpath(v, u, 0);
            break;
        case 2:
            addpath(u, v, 1);
            break;
        case 3:
            addpath(v, u, 0);
            break;
        case 4:
            addpath(v, u, 1);
            break;
        case 5:
            addpath(u, v, 0);
            break;
        }
    }
    for (int i = 1; i <= n; i++)
        addpath(0, i, 1);
    tarjan(0);
    // get the graph to judge if there is a loop with 1;
    for (int u = 0; u <= n; u++)
        for (int i = head[u]; i != -1; i = edges[i].nxt)
        {
            if (aff[u] == aff[edges[i].to] && edges[i].weight == 1)
                puts("-1"), exit(0);
            if (aff[u] != aff[edges[i].to])
                addpath(aff[u], aff[edges[i].to], edges[i].weight), deg[aff[edges[i].to]]++;
        }
    queue<int> q;
    for (int i = n + 1; i <= ncnt; i++)
        if (!deg[i])
            q.push(i);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edges[i].nxt)
        {
            dp[edges[i].to] = max(dp[edges[i].to], dp[u] + edges[i].weight);
            if (--deg[edges[i].to] == 0)
                q.push(edges[i].to);
        }
    }
    ll ans = 0;
    for (int i = n + 1; i <= ncnt; i++)
        ans += 1LL * dp[i] * siz[i];
    printf("%lld", ans);
    return 0;
}