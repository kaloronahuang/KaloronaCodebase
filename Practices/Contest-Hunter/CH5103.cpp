// CH5103.cpp
// Lower Complexity;
#include <iostream>
#include <cstdio>
using namespace std;
const int MX_N = 55;
int dp[(MX_N << 1)][MX_N][MX_N], n, m, arr[MX_N][MX_N];
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &arr[i][j]);
    dp[0][1][1] = arr[1][1];
    for (int i = 1; i <= n + m - 2; i++)
        for (int x1 = 1; x1 <= n && i - x1 + 2 >= 1; x1++)
            for (int x2 = 1; x2 <= n && i - x2 + 2 >= 1; x2++)
            {
                int y1 = i - x1 + 2, y2 = i - x2 + 2;
                dp[i][x1][x2] = max(
                                    max(
                                        max(
                                            dp[i - 1][x1][x2], dp[i - 1][x1 - 1][x2]),
                                        dp[i - 1][x1][x2 - 1]),
                                    dp[i - 1][x1 - 1][x2 - 1]) +
                                arr[x1][y1];
                if (x1 != x2)
                    dp[i][x1][x2] += arr[x2][y2];
            }
    printf("%d", dp[n + m - 2][n][n]);
    return 0;
}