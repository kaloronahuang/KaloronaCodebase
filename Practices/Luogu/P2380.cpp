// P2380.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 600;
// 0 to west, 1 to north;
int n, m, west[MAX_N][MAX_N], north[MAX_N][MAX_N], dp[MAX_N][MAX_N][3];
int main()
{
    while (~scanf("%d%d", &n, &m) && n != 0 && m != 0)
    {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                scanf("%d", &west[i][j]);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                scanf("%d", &north[i][j]);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
            {
                dp[i][j][0] = dp[i][j - 1][0] + west[i][j];
                dp[i][j][1] = dp[i - 1][j][1] + north[i][j];
                dp[i][j][2] = max(dp[i - 1][j][2] + dp[i][j][0], dp[i][j - 1][2] + dp[i][j][1]);
            }
        printf("%d\n", dp[n][m][2]);
    }
    return 0;
}