// COGS1517.cpp
#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n, k;
ll dp[12][110][(1 << 10) + 200];
bool vis[(1 << 10) + 10][(1 << 10) + 10], valid[(1 << 20) + 10];

int main()
{
    freopen("placeking.in", "r", stdin);
    freopen("placeking.out", "w", stdout);
    scanf("%d%d", &n, &k);
    memset(vis, true, sizeof(vis));
    memset(valid, true, sizeof(valid));
    for (int i = 0; i < (1 << n); i++)
        for (int k = 1; k < n - 1; k++)
            if ((i & (1 << k)))
                if ((i & (1 << (k - 1))) || (i & (1 << (k + 1))))
                    valid[i] = false;
    for (int i = 0; i < (1 << n); i++)
        for (int j = i; j < (1 << n); j++)
        {
            int stati = i, statj = j;
            for (int k = 1; k < n - 1; k++)
            {
                if (i & (1 << k))
                    stati |= (1 << (k - 1)) | (1 << (k + 1));
                if (j & (1 << k))
                    statj |= (1 << (k - 1)) | (1 << (k + 1));
            }
            if ((stati & j) || (statj & i))
                vis[i][j] = vis[j][i] = false;
        }
    dp[0][0][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= k; j++)
            for (int pre_stat = 0; pre_stat < (1 << n); pre_stat++)
                if (valid[pre_stat] && __builtin_popcount(pre_stat) <= j)
                    for (int stat = 0; stat < (1 << n); stat++)
                        if (valid[stat] && vis[pre_stat][stat] && __builtin_popcount(pre_stat) + __builtin_popcount(stat) <= j)
                            dp[i][j][stat] += dp[i - 1][j - __builtin_popcount(stat)][pre_stat];
    ll ans = 0;
    for (int stat = 0; stat < (1 << n); stat++)
        ans += dp[n][k][stat];
    printf("%lld", ans);
    return 0;
}