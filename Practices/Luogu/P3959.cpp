// P3959.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 20, INF = 0x3f3f3f3f;

int dist[MAX_N][MAX_N], n, m, dp[1 << MAX_N][MAX_N], dist_mask[1 << MAX_N];

int main()
{
    memset(dist, 0x3f, sizeof(dist));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v, w; i <= m; i++)
        scanf("%d%d%d", &u, &v, &w), u--, v--, dist[u][v] = dist[v][u] = min(dist[u][v], w);
    for (int i = 1; i < (1 << n); i++)
        for (int j = 0; j < n; j++)
            if (i & (1 << j))
            {
                dist[j][j] = 0;
                for (int k = 0; k < n; k++)
                    if (dist[j][k] != INF)
                        dist_mask[i] |= (1 << k);
            }
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 0; i < n; i++)
        dp[1 << i][0] = 0;
    for (int stat = 2; stat < (1 << n); stat++)
        for (int subset = stat - 1; subset; subset = (subset - 1) & stat)
            if ((dist_mask[subset] | stat) == dist_mask[subset])
            {
                int sum = 0, from = subset ^ stat;
                for (int k = 0; k < n; k++)
                    if (from & (1 << k))
                    {
                        int tmp = INF;
                        for (int idx = 0; idx < n; idx++)
                            if (subset & (1 << idx))
                                tmp = min(tmp, dist[idx][k]);
                        sum += tmp;
                    }
                for (int i = 1; i < n; i++)
                    if (dp[subset][i - 1] != INF)
                        dp[stat][i] = min(dp[stat][i], sum * i + dp[subset][i - 1]);
            }
    int ans = INF;
    for (int i = 0; i < n; i++)
        ans = min(ans, dp[(1 << n) - 1][i]);
    printf("%d", ans);
    return 0;
}