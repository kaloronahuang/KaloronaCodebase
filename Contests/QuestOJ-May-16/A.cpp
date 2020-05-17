// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 22;

typedef long long ll;

int n, m, mp[MAX_N][MAX_N], colstk[MAX_N], tot;
ll dp[MAX_N][MAX_N];
vector<int> G[MAX_N];

void dfs(int u, int fa)
{
    for (int v : G[u])
        if (v != fa)
            dfs(v, u);
    for (int cid = 1; cid <= tot; cid++)
    {
        int c = colstk[cid];
        dp[u][c] = 1;
        for (int v : G[u])
            if (v != fa)
            {
                ll tmp = 0;
                for (int k = 1; k <= tot; k++)
                    tmp += mp[c][colstk[k]] * dp[v][colstk[k]];
                dp[u][c] *= tmp;
            }
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), mp[u][v] = mp[v][u] = 1;
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), G[u].push_back(v), G[v].push_back(u);
    ll ans = 0;
    for (int stat = 0; stat < (1 << n); stat++)
    {
        tot = 0;
        for (int i = 0; i < n; i++)
            if (stat & (1 << i))
                colstk[++tot] = i + 1;
        dfs(1, 0);
        ll pans = 0;
        for (int i = 1; i <= n; i++)
            if (stat & (1 << (i - 1)))
                pans += dp[1][i];
        ans += (((n - __builtin_popcount(stat)) & 1) ? -1 : 1) * pans;
    }
    printf("%lld\n", ans);
    return 0;
}