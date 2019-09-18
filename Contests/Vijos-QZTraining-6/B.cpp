// B.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 100100, mod = 1e9 + 7;

int n, color[MAX_N], fa[MAX_N], current, head[MAX_N], dp[MAX_N][2];

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
    ll t0, t1;
    dp[u][color[u]] = 1, dp[u][color[u] ^ 1] = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        dfs(edges[i].to);
        t0 = dp[u][0], t1 = dp[u][1];
        dp[u][0] = (1LL * t0 * dp[edges[i].to][0] % mod + 1LL * t0 * dp[edges[i].to][1] % mod) % mod;
        dp[u][1] = (1LL * t0 * dp[edges[i].to][1] % mod + 1LL * t1 * dp[edges[i].to][0] + 1LL * t1 * dp[edges[i].to][1]) % mod;
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 2; i <= n; i++)
        scanf("%d", &fa[i]), fa[i]++, addpath(fa[i], i);
    for (int i = 1; i <= n; i++)
        scanf("%d", &color[i]);
    dfs(1);
    printf("%d", dp[1][1] % mod);
    return 0;
}