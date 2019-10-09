// P2157.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010, INF = 0x3f3f3f3f;

int T, n, ti[MAX_N], bi[MAX_N], dp[MAX_N][1 << 8][22];

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d%d", &ti[i], &bi[i]);
        memset(dp, 0x3f, sizeof(dp)), dp[1][0][7] = 0;
        for (int i = 1; i <= n; i++)
            for (int stat = 0; stat < (1 << 8); stat++)
                for (int k = -8; k <= 7; k++)
                    if (dp[i][stat][k + 8] != INF)
                        if (stat & 1)
                            dp[i + 1][stat >> 1][k - 1 + 8] = min(dp[i + 1][stat >> 1][k - 1 + 8], dp[i][stat][k + 8]);
                        else
                        {
                            int ptr = INF;
                            for (int h = 0; h < 8; h++)
                                if ((stat & (1 << h)) == 0)
                                {
                                    if (i + h > ptr)
                                        break;
                                    ptr = min(ptr, i + bi[i + h] + h);
                                    dp[i][stat | (1 << h)][h + 8] = min(dp[i][stat | (1 << h)][h + 8], dp[i][stat][k + 8] + (i + k != 0 ? ti[i + h] ^ ti[i + k] : 0));
                                }
                        }
        int res = INF;
        for (int k = 0; k <= 8; k++)
            res = min(res, dp[n + 1][0][k]);
        printf("%d\n", res);
    }
    return 0;
}