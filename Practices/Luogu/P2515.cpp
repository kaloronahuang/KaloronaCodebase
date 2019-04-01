// P2515.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 2100, MAX_M = 1050, MAX_S = 1010;
ll dp[MAX_N][MAX_S], vi[MAX_N], wi[MAX_N], n, m;
int head[MAX_N], current, dfn[MAX_N], low[MAX_N], st[MAX_N], stcur, colortot, color[MAX_N], tot, tmpx, root, indeg[MAX_N];
bool inst[MAX_N];
struct edge
{
    int to, nxt;
} edges[MAX_N << 2];
void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}
void tarjan(int u)
{
    dfn[u] = low[u] = ++tot, inst[u] = true, st[++stcur] = u;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (dfn[edges[i].to] != 0)
            tarjan(edges[i].to), low[u] = min(low[u], low[edges[i].to]);
        else if (inst[edges[i].to])
            low[u] = min(low[u], dfn[edges[i].to]);
    if (dfn[u] == low[u])
    {
        int col = ++colortot;
        do
        {
            color[st[stcur]] = col, inst[st[stcur]] = false;
        } while (st[stcur--] != u);
    }
}
void dfs(int u)
{
    for (int j = wi[u]; j <= m; j++)
        dp[u][j] = vi[u];
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        int to = edges[i].to;
        dfs(to);
        for (int j = m - wi[u]; j >= 0; j--)
            for (int q = 0; q <= j; q++)
                dp[u][j + wi[u]] = max(dp[u][j + wi[u]], dp[u][j + wi[u] - q] + dp[to][q]);
    }
}
int main()
{
    memset(head, -1, sizeof(head));
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &wi[i]);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &vi[i]);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &tmpx);
        if (tmpx != 0)
            addpath(tmpx, i);
    }
    colortot = n;
    for (int i = 1; i <= n; i++)
        if (dfn[i] == 0)
            tarjan(i);
    for (int pt = 1; pt <= n; pt++)
    {
        int col = color[pt];
        for (int i = head[pt]; i != -1; i = edges[i].nxt)
            if (color[pt] != color[edges[i].to])
                addpath(color[pt], color[edges[i].to]), indeg[color[edges[i].to]]++;
        vi[col] += vi[pt], wi[col] += wi[pt];
    }
    root = colortot + 1;
    for (int i = n + 1; i <= colortot; i++)
        if (indeg[i] == 0)
            addpath(root, i);
    dfs(root);
    printf("%lld", dp[root][m]);
    return 0;
}