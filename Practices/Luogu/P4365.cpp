// P4365.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1680, mod = 64123;

int n, k, W, di[MAX_N], head[MAX_N], current, weights[MAX_N], dp[MAX_N][MAX_N], siz[MAX_N];

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
    for (int i = 1; i <= k; i++)
        dp[u][i] = 0;
    dp[u][siz[u] = weights[u]] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dfs(edges[i].to, u);
            for (int j = siz[u]; j >= 0; j--)
            {
                int p = dp[u][j];
                for (int v = siz[edges[i].to]; v >= 0; v--)
                    dp[u][min(j + v, k)] = (0LL + dp[u][min(j + v, k)] + 1LL * p * dp[edges[i].to][v] % mod) % mod;
            }
            siz[u] = min(siz[u] + siz[edges[i].to], k);
        }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &k, &W);
    for (int i = 1; i <= n; i++)
        scanf("%d", &di[i]);
    for (int i = 1, u, v; i < n; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    int ans = 0;
    for (int i = 1; i <= W; i++)
    {
        int acc = 0;
        for (int j = 1; j <= n; j++)
            acc += (weights[j] = (di[j] >= i));
        if (acc < k)
            continue;
        dfs(1, 0);
        for (int j = 1; j <= n; j++)
            ans = (0LL + ans + dp[j][k]) % mod;
    }
    printf("%d\n", ans);
    return 0;
}