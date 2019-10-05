// CF3B14.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 2020, MAX_V = 330;
const double INF = 1e17 + 5;
int n, m, v, e, ci[MAX_N], di[MAX_N], dist[MAX_V][MAX_V], tmpx, tmpy, tmpz;
double pi[MAX_N], dp[MAX_N][MAX_N][2];
int main()
{
    memset(dist, 63, sizeof(dist));
    scanf("%d%d%d%d", &n, &m, &v, &e);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ci[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &di[i]);
    for (int i = 1; i <= n; i++)
        scanf("%lf", &pi[i]);
    for (int i = 1; i <= e; i++)
        scanf("%d%d%d", &tmpx, &tmpy, &tmpz), dist[tmpx][tmpy] = min(dist[tmpx][tmpy], tmpz), dist[tmpy][tmpx] = dist[tmpx][tmpy];
    for (register int k = 1; k <= v; k++)
        for (register int i = 1; i <= v; i++)
            for (register int j = 1; j <= v; j++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    for (int i = 1; i <= v; i++)
        dist[i][i] = dist[0][i] = dist[i][0] = 0;
    memset(dp, 127, sizeof(dp));
    dp[1][0][0] = dp[1][1][1] = 0;
    for (int i = 2; i <= n; i++)
    {
        dp[i][0][0] = dp[i - 1][0][0] + dist[ci[i - 1]][ci[i]];
        for (int j = 1; j <= min(i, m); j++)
        {
            int C1 = ci[i - 1], C2 = di[i - 1], C3 = ci[i], C4 = di[i];
            dp[i][j][0] = min(dp[i][j][0], min(dp[i - 1][j][0] + dist[C1][C3], dp[i - 1][j][1] + dist[C1][C3] * (1 - pi[i - 1]) + dist[C2][C3] * pi[i - 1]));
            dp[i][j][1] = min(dp[i][j][1], min(dp[i - 1][j - 1][0] + dist[C1][C3] * (1 - pi[i]) + dist[C1][C4] * pi[i], dp[i - 1][j - 1][1] + dist[C2][C4] * pi[i] * pi[i - 1] + dist[C2][C3] * pi[i - 1] * (1 - pi[i]) + dist[C1][C4] * (1 - pi[i - 1]) * pi[i] + dist[C1][C3] * (1 - pi[i - 1]) * (1 - pi[i])));
        }
    }
    double ans = INF;
    for (register int i = 0; i <= m; i++)
        ans = min(ans, min(dp[n][i][0], dp[n][i][1]));
    printf("%.2lf", ans);
    return 0;
}