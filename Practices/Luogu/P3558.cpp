// P3558.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200, INF = 0x3f3f3f3f;

int seq[MAX_N], n, dp[MAX_N][3];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i]);
    dp[1][0] = dp[1][1] = dp[1][2] = INF;
    dp[1][seq[1] + 1] = 0;
    for (int i = 2; i <= n; i++)
    {
        if (seq[i] == -1)
        {
            // -1 situation;
            dp[i][0] = dp[i - 1][0];
            if (seq[i - 1] == 1)
                dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]) + 1;
            else
                dp[i][1] = INF;
            if (seq[i - 1] == 1)
                dp[i][2] = min(dp[i - 1][0], min(dp[i - 1][1], dp[i - 1][2])) + 2;
            else
                dp[i][2] = dp[i - 1][2] + 2;
        }
        else if (seq[i] == 0)
        {
            dp[i][0] = dp[i - 1][0] + 1;
            dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]);
            if (seq[i - 1] == 1)
                dp[i][2] = min(min(dp[i - 1][0], dp[i - 1][1]), dp[i - 1][2]) + 1;
            else
                dp[i][2] = dp[i - 1][2] + 1;
        }
        else if (seq[i] == 1)
        {
            dp[i][0] = dp[i - 1][0] + 2;
            if (seq[i - 1] == -1)
                dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]) + 1;
            else
                dp[i][1] = dp[i - 1][0] + 1;
            dp[i][2] = min(dp[i - 1][0], min(dp[i - 1][1], dp[i - 1][2]));
        }
    }
    int ans = min(dp[n][0], min(dp[n][1], dp[n][2]));
    if (ans >= INF)
        printf("BRAK");
    else
        printf("%d\n", ans);
    return 0;
}