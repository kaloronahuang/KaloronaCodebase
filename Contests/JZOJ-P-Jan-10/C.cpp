// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e4 + 200, MAX_E = 1e5 + 200;
typedef long long ll;

int head[MAX_N], current, n, m, dfn[MAX_N], low[MAX_N], ptot, tot[MAX_N];
ll ans[MAX_N];

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
    ll cnt = 0;
    dfn[u] = low[u] = ++ptot;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            if (dfn[edges[i].to] == 0)
            {
                tarjan(edges[i].to, u), low[u] = min(low[u], low[edges[i].to]);
                tot[u] += tot[edges[i].to];
                if (low[edges[i].to] >= dfn[u])
                {
                    ans[u] -= cnt * tot[edges[i].to], ans[u] += 1LL * (n - tot[edges[i].to] - 1) * tot[edges[i].to];
                    cnt += tot[edges[i].to];
                }
            }
            else
                low[u] = min(low[u], dfn[edges[i].to]);
    ans[u] += n - 1, tot[u]++;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++)
    {
        scanf("%d%d", &u, &v);
        if (u != v)
            addpath(u, v), addpath(v, u);
    }
    for (int i = 1; i <= n; i++)
        if (dfn[i] == 0)
            tarjan(i, 0);
    for (int i = 1; i <= n; i++)
        printf("%lld\n", ans[i]);
    return 0;
}