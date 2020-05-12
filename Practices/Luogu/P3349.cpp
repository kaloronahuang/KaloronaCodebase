// P3349.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 20;

typedef long long ll;

int head[MAX_N], current, mp[MAX_N][MAX_N], col[MAX_N], siz, n, m;
ll dp[MAX_N][MAX_N];

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
            dfs(edges[i].to, u);
    for (int i = 1; i <= siz; i++)
    {
        int cc = col[i];
        dp[u][cc] = 1;
        for (int j = head[u]; j != -1; j = edges[j].nxt)
            if (edges[j].to != fa)
            {
                ll sum = 0;
                for (int k = 1; k <= siz; k++)
                    sum += dp[edges[j].to][col[k]] * mp[cc][col[k]];
                dp[u][cc] *= sum;
            }
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), mp[u][v] = mp[v][u] = 1;
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    ll ans = 0;
    for (int stat = 0; stat < (1 << n); stat++)
    {
        siz = 0;
        for (int i = 0; i < n; i++)
            if (stat & (1 << i))
                col[++siz] = i + 1;
        dfs(1, 0);
        ll pans = 0;
        for (int i = 1; i <= siz; i++)
            pans += dp[1][col[i]];
        ans += (((n - __builtin_popcount(stat)) & 1) ? -1LL : 1LL) * pans;
    }
    printf("%lld\n", ans);
    return 0;
}