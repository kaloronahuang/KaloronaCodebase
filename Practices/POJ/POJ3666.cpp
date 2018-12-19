// POJ3666.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MX_P = 201;
int tablec[MX_P][MX_P], l, n;
int dp[1001][MX_P][MX_P], poses[1001];
int cost(int i, int j) { return tablec[i][j]; }
int main()
{
    scanf("%d%d", &l, &n);
    for (int i = 1; i <= l; i++)
        for (int j = 1; j <= l; j++)
            scanf("%d", &tablec[i][j]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &poses[i]);
    memset(dp, 0x3f, sizeof(dp));
    dp[0][1][2] = cost(3, poses[1]);
    dp[0][1][3] = cost(2, poses[1]);
    dp[0][2][3] = cost(1, poses[1]);
    for (int i = 1; i <= n; i++)
        for (int x = 1; x <= l; x++)
            for (int y = 1; y <= l; y++)
            {
                if (x == poses[i - 1] || y == poses[i - 1] || x == y)
                    continue;
                dp[i][x][y] = min(dp[i][x][y], dp[i - 1][x][y] + cost(poses[i - 1], poses[i]));
                dp[i][x][poses[i - 1]] = min(dp[i][x][poses[i - 1]], dp[i - 1][x][y] + cost(y, poses[i]));
                dp[i][poses[i - 1]][y] = min(dp[i][poses[i - 1]][y], dp[i - 1][x][y] + cost(x, poses[i]));
            }
    int ans = 0x7fffffff;
    for (int i = 1; i <= l; i++)
        for (int j = 1; j <= l; j++)
            ans = min(ans, dp[n][i][j]);
    printf("%d", ans);
    return 0;
}