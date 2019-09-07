// P1430.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010;

int dp[MAX_N][MAX_N], prefix[MAX_N], lft[MAX_N][MAX_N], rig[MAX_N][MAX_N], seq[MAX_N], n, T;

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        memset(lft, 0x3f, sizeof(lft)), memset(rig, 0x3f, sizeof(rig));
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d", &seq[i]), prefix[i] = seq[i] + prefix[i - 1];
        for (int j = 1; j <= n; j++)
            for (int i = j; i >= 1; i--)
            {
                dp[i][j] = prefix[j] - prefix[i - 1];
                dp[i][j] = max(dp[i][j], prefix[j] - prefix[i - 1] - lft[i][j - 1]);
                dp[i][j] = max(dp[i][j], prefix[j] - prefix[i - 1] - rig[i + 1][j]);
                if (i == j)
                    lft[i][j] = rig[i][j] = dp[i][j];
                else
                {
                    lft[i][j] = min(lft[i][j - 1], dp[i][j]);
                    rig[i][j] = min(rig[i + 1][j], dp[i][j]);
                }
            }
        printf("%d\n", dp[1][n]);
    }
    return 0;
}

