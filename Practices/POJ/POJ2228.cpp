// POJ2228.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;
int n, limit, ui[40000], dp[2][4000][2];
int main()
{
    scanf("%d%d", &n, &limit);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ui[i]);
    if (limit == 0)
        printf("0"), exit(0);
    memset(dp, -0x3f, sizeof(dp));
    dp[1][0][0] = dp[1][1][1] = 0;
    for (int i = 2; i <= n; i++)
        for (int j = 0; j <= limit; j++)
        {
            if (j >= 1)
                dp[i & 1][j][1] = max(dp[(i - 1) & 1][j - 1][0], dp[(i - 1) & 1][j - 1][1] + ui[i]);
            dp[i & 1][j][0] = max(dp[(i - 1) & 1][j][0], dp[(i - 1) & 1][j][1]);
        }
    int ans = max(dp[n & 1][limit][1], dp[n & 1][limit][0]);
    memset(dp, -0x3f, sizeof(dp));
    dp[1][1][1] = ui[1];
    for (int i = 2; i <= n; i++)
        for (int j = 0; j <= limit; j++)
        {
            if (j >= 1)
                dp[i & 1][j][1] = max(dp[(i - 1) & 1][j - 1][0], dp[(i - 1) & 1][j - 1][1] + ui[i]);
            dp[i & 1][j][0] = max(dp[(i - 1) & 1][j][0], dp[(i - 1) & 1][j][1]);
        }
    ans = max(ans, dp[n & 1][limit][1]);
    printf("%d", ans);
    return 0;
}