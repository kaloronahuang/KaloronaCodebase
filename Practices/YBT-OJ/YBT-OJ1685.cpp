// YBT-OJ1685.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 20, dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};

int n, m, mat[MAX_N][MAX_N], dp[(1 << 16) + 200][MAX_N], tot;
int posx[MAX_N], posy[MAX_N], pos[MAX_N][MAX_N];

int main()
{
    scanf("%d%d", &n, &m), tot = n * m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            scanf("%d", &mat[i][j]);
            int id = (i - 1) * m + j;
            posx[id] = i, posy[id] = j, pos[i][j] = id;
        }
    memset(dp, 128, sizeof(dp)), dp[0][0] = 0;
    int ans = 0;
    for (int stat = 0; stat < (1 << tot); stat++)
    {
        for (int i = 1; i <= tot; i++)
        {
            if (dp[stat][i] < 0)
                continue;
            ans = max(ans, dp[stat][i]);
            int x = posx[i], y = posy[i];
            for (int dir = 0; dir < 4; dir++)
            {
                int dstx = x + dx[dir], dsty = y + dy[dir];
                if (dstx <= n && dstx >= 1 && dsty <= m && dsty >= 1 && (!(stat & (1 << (pos[dstx][dsty] - 1)))))
                    dp[stat | (1 << (pos[dstx][dsty] - 1))][pos[dstx][dsty]] =
                        max(dp[stat | (1 << (pos[dstx][dsty] - 1))][pos[dstx][dsty]],
                            dp[stat][i] + (__builtin_popcount(stat) + 1) * mat[dstx][dsty]);
            }
            if (x == 1 || x == n || y == 1 || y == m)
                dp[stat][0] = max(dp[stat][0], dp[stat][i]);
        }
        ans = max(ans, dp[stat][0]);
        if (dp[stat][0] >= 0)
        {
            for (int i = 1; i <= m - 1; i++)
            {
                if (stat & (1 << (pos[1][i] - 1)))
                    continue;
                dp[stat | (1 << (pos[1][i] - 1))][pos[1][i]] = max(dp[stat | (1 << (pos[1][i] - 1))][pos[1][i]], dp[stat][0] + (__builtin_popcount(stat) + 1) * mat[1][i]);
            }
            for (int i = 2; i <= m; i++)
            {
                if (stat & (1 << (pos[n][i] - 1)))
                    continue;
                dp[stat | (1 << (pos[n][i] - 1))][pos[n][i]] = max(dp[stat | (1 << (pos[n][i] - 1))][pos[n][i]], dp[stat][0] + (__builtin_popcount(stat) + 1) * mat[n][i]);
            }
            for (int i = 1; i <= n - 1; i++)
            {
                if (stat & (1 << (pos[i][m] - 1)))
                    continue;
                dp[stat | (1 << (pos[i][m] - 1))][pos[i][m]] = max(dp[stat | (1 << (pos[i][m] - 1))][pos[i][m]], dp[stat][0] + (__builtin_popcount(stat) + 1) * mat[i][m]);
            }
            for (int i = 2; i <= n; i++)
            {
                if (stat & (1 << (pos[i][1] - 1)))
                    continue;
                dp[stat | (1 << (pos[i][1] - 1))][pos[i][1]] = max(dp[stat | (1 << (pos[i][1] - 1))][pos[i][1]], dp[stat][0] + (__builtin_popcount(stat) + 1) * mat[i][1]);
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}