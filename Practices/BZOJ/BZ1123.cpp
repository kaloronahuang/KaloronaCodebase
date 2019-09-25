// BZ1123.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAX_N = 100010, MAX_M = 500010;

struct edge
{
    int to, nxt;
} edges[MAX_M << 1];

int head[MAX_N], current, n, m, dfn[MAX_N], low[MAX_N], ptot, siz[MAX_N], root;
ll ans[MAX_N];
bool cut[MAX_N];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void tarjan(int u)
{
    ll flag = 0, sum = 0;
    dfn[u] = low[u] = ++ptot, siz[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (dfn[edges[i].to] == 0)
        {
            tarjan(edges[i].to), low[u] = min(low[edges[i].to], low[u]);
            siz[u] += siz[edges[i].to];
            if (low[edges[i].to] >= dfn[u])
            {
                flag++;
                ans[u] += 1LL * (n - siz[edges[i].to]) * siz[edges[i].to];
                // sum accumulated from cut;
                sum += siz[edges[i].to];
                if (u != 1 || flag > 1)
                    cut[u] = true;
            }
        }
        else
            low[u] = min(dfn[edges[i].to], low[u]);
    if (!cut[u])
        ans[u] = 2LL * (n - 1);
    else
        ans[u] += 1LL * (n - sum - 1) * (sum + 1) + (n - 1);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    tarjan(1);
    for (int i = 1; i <= n; i++)
        printf("%lld\n", ans[i]);
    return 0;
}