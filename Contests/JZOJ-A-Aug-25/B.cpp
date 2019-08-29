// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, mod = 1e9 + 7;

int head[MAX_N], current, dp[MAX_N], n, fa[MAX_N], answer[MAX_N];
bool subtask3flag = true;
struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

int quick_pow(int bas, int tim)
{
    int ans = 1;
    while (tim)
    {
        if (tim & 1)
            ans = 1LL * bas * ans % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ans;
}

void addpath(int src, int dst)
{
    edges[current].nxt = head[src], edges[current].to = dst;
    head[src] = current++;
}

void dfs(int u)
{
    dp[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa[u])
            fa[edges[i].to] = u, dfs(edges[i].to), dp[u] = 1LL * dp[u] * (dp[edges[i].to] + 1) % mod;
}

void dfs_change_root(int u)
{
    int tmp = dp[u], fat = fa[u];
    int second_tmp = dp[u] = 1LL * dp[u] * (dp[fat] + 1) % mod;
    answer[u] = second_tmp;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fat)
            dp[u] = 1LL * dp[u] * quick_pow(dp[edges[i].to] + 1, mod - 2) % mod, dfs_change_root(edges[i].to), dp[u] = second_tmp;
    dp[u] = tmp;
}

int main()
{
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 2, u; i <= n; i++)
        scanf("%d", &u), addpath(i, u), addpath(u, i);
    dfs(1), dfs_change_root(1);
    for (int i = 1; i <= n; i++)
        printf("%d ", answer[i]);
    return 0;
}

