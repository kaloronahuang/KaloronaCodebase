// P3174.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 303000;

int head[MAX_N], current, n, m, dp[MAX_N][3], deg[MAX_N], fat[MAX_N];

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
    fat[u] = fa;
    int prime_item = 0, second_item = 0, cnt = deg[u] - min(fa, 1);
    dp[u][1] = cnt + 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dfs(edges[i].to, u);
            if (dp[edges[i].to][1] > prime_item)
                swap(prime_item, second_item), prime_item = dp[edges[i].to][1];
            else if (dp[edges[i].to][1] > second_item)
                second_item = dp[edges[i].to][1];
            dp[u][1] = max(dp[u][1], dp[edges[i].to][1] + cnt);
        }
    if (second_item != 0)
        dp[u][2] = prime_item + second_item + cnt - 2 + 1;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u), deg[u]++, deg[v]++;
    dfs(1, 0);
    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans = max(ans, max(dp[i][1] + min(fat[i], 1), dp[i][2] + min(fat[i], 1)));
    printf("%d", ans);
    return 0;
}