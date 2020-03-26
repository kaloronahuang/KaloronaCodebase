// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5050;

int n, ai[MAX_N], dp[MAX_N][MAX_N][3];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0][0] = 0;
    for (int i = 1; i <= n; i++)
    {
        dp[i][0][0] = 0;
        for (int j = 1; j <= (i + 1) >> 1; j++)
        {
            if (ai[i] > ai[i - 1])
                dp[i][j][1] = min(dp[i][j][1], dp[i - 1][j - 1][0]);
            if (i != 1)
            {
                if (ai[i] > ai[i - 2] - 1)
                    dp[i][j][1] = min(dp[i][j][1], dp[i - 1][j - 1][2]);
                else
                    dp[i][j][1] = min(dp[i][j][1], dp[i - 1][j - 1][2] + ai[i - 2] - 1 - ai[i] + 1);
            }
            if (ai[i] <= ai[i - 1])
                dp[i][j][1] = min(dp[i][j][1], dp[i - 1][j - 1][0] + ai[i - 1] - ai[i] + 1);
            // choose;
            dp[i][j][0] = min(dp[i][j][0], min(dp[i - 1][j][2], dp[i - 1][j][0]));
            if (ai[i] < ai[i - 1])
                dp[i][j][0] = min(dp[i][j][0], dp[i - 1][j][1]);
            if (ai[i] >= ai[i - 1])
                dp[i][j][2] = min(dp[i][j][2], min(dp[i - 1][j][1], dp[i - 1][j][0]) + ai[i] - ai[i - 1] + 1);
        }
    }
    for (int i = 1; i <= (n + 1) >> 1; i++)
        printf("%d ", min(dp[n][i][0], min(dp[n][i][1], dp[n][i][2])));
    puts("");
    return 0;
}