// P5904.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

typedef long long ll;

int n, head[MAX_N], current, height[MAX_N], son[MAX_N], org[MAX_N];
ll pool[MAX_N << 2], *dp[MAX_N], *g[MAX_N], *cur, ans;

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u, int fa)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dfs(edges[i].to, u);
            if (height[son[u]] < height[edges[i].to])
                son[u] = edges[i].to;
        }
    height[u] = height[son[u]] + 1;
}

void calc(int u, int fa)
{
    if (son[u])
        dp[son[u]] = dp[u] + 1, g[son[u]] = g[u] - 1, calc(son[u], u);
    dp[u][0] = 1, ans += g[u][0];
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && edges[i].to != son[u])
        {
            dp[edges[i].to] = cur, cur += height[edges[i].to] << 1, g[edges[i].to] = cur, cur += height[edges[i].to] << 1;
            calc(edges[i].to, u);
            for (int j = 0; j < height[edges[i].to]; j++)
            {
                if (j > 0)
                    ans += dp[u][j - 1] * g[edges[i].to][j];
                ans += g[u][j + 1] * dp[edges[i].to][j];
            }
            for (int j = 0; j < height[edges[i].to]; j++)
            {
                g[u][j + 1] += dp[u][j + 1] * dp[edges[i].to][j];
                if (j > 0)
                    g[u][j - 1] += g[edges[i].to][j];
                dp[u][j + 1] += dp[edges[i].to][j];
            }
        }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dfs(1, 0), dp[1] = cur = pool, cur += height[1] << 1, g[1] = cur, cur += height[1] << 1;
    calc(1, 0), printf("%lld\n", ans);
    return 0;
}