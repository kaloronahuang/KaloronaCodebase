// P2331.cpp
#include <bits/stdc++.h>

using namespace std;

int prefix[200][200], n, m, req, dp[220][110][20];

int getRect(int x, int y, int a, int b) { return prefix[a][b] - prefix[x - 1][b] - prefix[a][y - 1] + prefix[x - 1][y - 1]; }

int main()
{
    scanf("%d%d%d", &n, &m, &req);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &prefix[i][j]);
    for (int j = 1; j <= m; j++)
        for (int i = 1; i <= n; i++)
            prefix[i][j] += prefix[i - 1][j];
    if (m == 1)
    {
        // subsequence with biggest weight;
        for (int k = 1; k <= req; k++)
            for (int i = 1; i <= n; i++)
            {
                dp[i][1][k] = dp[i - 1][1][k];
                for (int j = i; j >= 1; j--)
                    dp[i][1][k] = max(dp[i][1][k], prefix[i][1] - prefix[j - 1][1] + dp[j - 1][1][k - 1]);
            }
        printf("%d\n", dp[n][1][req]);
    }
    else
    {
        for (int k = 1; k <= req; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                {
                    dp[i][j][k] = max(dp[i - 1][j][k], dp[i][j - 1][k]);
                    for (int l = 1; l <= i; l++)
                        dp[i][j][k] = max(dp[i][j][k], dp[l - 1][j][k - 1] + prefix[i][1] - prefix[l - 1][1]);
                    for (int l = 1; l <= j; l++)
                        dp[i][j][k] = max(dp[i][j][k], dp[i][l - 1][k - 1] + prefix[j][2] - prefix[l - 1][2]);
                    if (i == j)
                        for (int l = 1; l <= i; l++)
                            dp[i][j][k] = max(dp[i][j][k], dp[l - 1][l - 1][k - 1] + prefix[i][1] - prefix[l - 1][1] + prefix[i][2] - prefix[l - 1][2]);
                }
        printf("%d\n", dp[n][n][req]);
    }
    return 0;
}