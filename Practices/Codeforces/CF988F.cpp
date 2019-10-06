// CF988F.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2020, INF = 0x3f3f3f3f;

int dp[MAX_N][MAX_N], n, seg[MAX_N], L, m, ubx[MAX_N], ubp[MAX_N];

int main()
{
    scanf("%d%d%d", &L, &n, &m), L++;
    for (int i = 1, lft, rig; i <= n; i++)
        scanf("%d%d", &lft, &rig), seg[lft + 1]++, seg[rig + 1]--;
    for (int i = 1; i <= L; i++)
        seg[i] += seg[i - 1];
    ubp[0] = INF;
    for (int i = 1, x; i <= m; i++)
    {
        scanf("%d%d", &x, &ubp[i]);
        if (ubp[ubx[x]] > ubp[i])
            ubx[x] = i;
    }
    memset(dp, 0x3f, sizeof(dp));
    int drop = INF, alter = INF;
    dp[0][0] = dp[0][ubx[0]] = 0;
    if (ubx[0] != 0)
        drop = 0, alter = ubp[ubx[0]];
    for (int i = 1; i <= L; i++)
    {
        if (seg[i] == 0)
            dp[i][0] = min(dp[i][0], min(drop, dp[i - 1][0]));
        else if (seg[i + 1] == 0)
            dp[i][0] = min(dp[i][0], alter);
        for (int j = 1; j <= m; j++)
        {
            dp[i][j] = min(dp[i][j], dp[i - 1][j] + ubp[j]);
            if (ubx[i] == j)
                if (seg[i] == 0)
                    dp[i][j] = min(dp[i][j], min(dp[i - 1][0], drop));
                else
                    dp[i][j] = min(dp[i][j], alter);
        }
        drop = INF, alter = INF;
        for (int j = 1; j <= m; j++)
            drop = min(drop, dp[i][j]), alter = min(alter, dp[i][j] + ubp[j]);
    }
    int ans = INF;
    for (int i = 0; i <= m; i++)
        ans = min(ans, dp[L][i]);
    if (ans == INF)
        puts("-1");
    else
        printf("%d", ans);
    return 0;
}