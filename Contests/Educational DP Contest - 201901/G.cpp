// G.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
using namespace std;
const int MX_N = 1e5 + 200;
int n, m, head[MX_N], m_current, tmpx, tmpy, deg[MX_N], ans, dp[MX_N];
struct edge
{
    int to, nxt;
} edges[MX_N];
void addpath(int src, int dst)
{
    edges[m_current].to = dst, edges[m_current].nxt = head[src];
    head[src] = m_current++;
}
void dfs(int u)
{
    dp[u] = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        if (dp[edges[i].to] == -1)
            dfs(edges[i].to);
        dp[u] = max(dp[u], dp[edges[i].to] + 1);
    }
    ans = max(dp[u], ans);
}
int main()
{
    memset(head, -1, sizeof(head)), memset(dp, -1, sizeof(dp));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
        scanf("%d%d", &tmpx, &tmpy), addpath(tmpx, tmpy), deg[tmpy]++;
    for (int i = 1; i <= n; i++)
        if (deg[i] == 0)
            dfs(i);
    printf("%d", ans);
    return 0;
}