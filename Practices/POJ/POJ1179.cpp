// POJ1179.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
struct tup
{
    int num;
    char op;
} tps[110];
int n, dp[2][110][110];
int main()
{
    scanf("%d", &n);
    memset(dp[1], 0x3f, sizeof(dp[1]));
    memset(dp[0], -0x3f, sizeof(dp[0]));
    for (int i = 1; i <= n; i++)
    {
        cin >> tps[i].op >> tps[i].num, tps[i + n] = tps[i];
        dp[0][i][i] = dp[1][i][i] = tps[i].num;
        dp[0][i + n][i + n] = dp[1][i + n][i + n] = tps[i].num;
    }
    for (int len = 1; len <= n; len++)
        for (int i = 1; i + len - 1 <= 2 * n; i++)
        {
            int j = i + len - 1;
            for (int k = i; k < j; k++)
            {
                if (tps[k + 1].op == 't')
                {
                    dp[0][i][j] = max(dp[0][i][j], dp[0][i][k] + dp[0][k + 1][j]);
                    dp[1][i][j] = min(dp[1][i][j], dp[1][i][k] + dp[1][k + 1][j]);
                }
                else
                {
                    dp[0][i][j] = max(dp[0][i][j], dp[0][i][k] * dp[0][k + 1][j]);
                    dp[0][i][j] = max(dp[0][i][j], dp[1][i][k] * dp[1][k + 1][j]);
                    dp[1][i][j] = min(dp[1][i][j], dp[1][i][k] * dp[1][k + 1][j]);
                    dp[1][i][j] = min(dp[1][i][j], dp[0][i][k] * dp[1][k + 1][j]);
                    dp[1][i][j] = min(dp[1][i][j], dp[1][i][k] * dp[0][k + 1][j]);
                    dp[1][i][j] = min(dp[1][i][j], dp[0][i][k] * dp[0][k + 1][j]);
                }
            }
        }
    int ans = -0x3f3f3f3f;
    for (int i = 1; i <= n; i++)
        ans = max(ans, dp[0][i][i + n - 1]);
    printf("%d\n", ans);
    for (int i = 1; i <= n; i++)
        if (dp[0][i][i + n - 1] == ans)
            printf("%d ", i);
    return 0;
}