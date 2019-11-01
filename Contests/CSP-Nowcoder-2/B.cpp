// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, MAX_E = 2e5 + 2000;

int head[MAX_N], current, n, m, limit, ncnt, dfn[MAX_N], low[MAX_N], ptot, stk[MAX_N], tail;
int SCC, aff[MAX_N], dist[MAX_N], loops[MAX_N], loop_cnt;

struct edge
{
    int to, nxt;
} edges[MAX_E << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void tarjan(int u, int fa)
{
    dfn[u] = low[u] = ++ptot, stk[++tail] = u;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            if (dfn[edges[i].to] == 0)
                tarjan(edges[i].to, u), low[u] = min(low[u], low[edges[i].to]);
            else
                low[u] = min(low[u], dfn[edges[i].to]);
    if (dfn[u] == low[u])
    {
        SCC++;
        do
        {
            aff[stk[tail]] = SCC;
        } while (stk[tail--] != u);
    }
}

void find_loop(int u, int fa)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            if (dist[edges[i].to] == 0)
            {
                dist[edges[i].to] = dist[u] + 1;
                find_loop(edges[i].to, u);
            }
            else if (dist[edges[i].to] < dist[u] + 1)
                loops[++loop_cnt] = dist[u] - dist[edges[i].to] + 1;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &m, &limit);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    for (int i = 1; i <= n; i++)
        if (dfn[i] == 0)
            tarjan(i, 0), ncnt++;
    // get the non-loop component;
    ncnt = SCC - ncnt;
    if (limit <= ncnt)
        printf("%d\n", SCC + limit - ncnt), exit(0);
    limit -= ncnt;
    for (int i = 1; i <= n; i++)
        if (dist[i] == 0)
            dist[i] = 1, find_loop(i, 0);
    int ans = SCC;
    sort(loops + 1, loops + 1 + loop_cnt);
    reverse(loops + 1, loops + 1 + loop_cnt);
    for (int i = 1; i <= loop_cnt; i++)
    {
        limit--;
        ans += min(limit, loops[i] - 1);
        limit -= loops[i] - 1;
        if (limit < 0)
            break;
    }
    printf("%d\n", ans);
    return 0;
}