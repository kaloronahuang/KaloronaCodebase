// D.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 3e5 + 2000;
int head[MAX_N], current, n, k, fa[MAX_N], deg[MAX_N], dp[MAX_N];
bool mark[MAX_N];
struct edge
{
    int to, nxt;
} edges[MAX_N << 1];
void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}
void dfs(int u)
{
    if (u != 1 && deg[u] == 1)
    {
        k++, dp[u] = 1;
        return;
    }
    if (mark[u])
        dp[u] = 0x3f3f3f3f;
    else
        dp[u] = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        dfs(edges[i].to);
        if (mark[u])
            dp[u] = min(dp[u], dp[edges[i].to]);
        else
            dp[u] += dp[edges[i].to];
    }
}
int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &mark[i]);
    for (int i = 2; i <= n; i++)
        scanf("%d", &fa[i]), addpath(fa[i], i), deg[fa[i]]++, deg[i]++;
    dfs(1);
    printf("%d", k - dp[1] + 1);
    return 0;
}