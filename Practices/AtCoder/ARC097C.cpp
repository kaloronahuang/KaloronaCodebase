// ARC097C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2020;

int n, tablewb[MAX_N][MAX_N], tablebw[MAX_N][MAX_N], dp[MAX_N][MAX_N], wid[MAX_N], bid[MAX_N];
char cmdlet[20];

int main()
{
    scanf("%d", &n);
    for (int i = 1, x; i <= (n << 1); i++)
    {
        scanf("%s%d", cmdlet + 1, &x);
        if (cmdlet[1] == 'W')
            wid[x] = i;
        else
            bid[x] = i;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j < i; j++)
            if (wid[i] < wid[j])
                tablewb[i][0]++;
        for (int j = 1; j <= n; j++)
            tablewb[i][j] = tablewb[i][j - 1] + (wid[i] < bid[j]);
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j < i; j++)
            if (bid[i] < bid[j])
                tablebw[0][i]++;
        for (int j = 1; j <= n; j++)
            tablebw[j][i] = tablebw[j - 1][i] + (bid[i] < wid[j]);
    }
    int prew = 0, preb = 0;
    for (int i = 1; i <= n; i++)
        prew += tablewb[i][0], dp[i][0] = prew, preb += tablebw[0][i], dp[0][i] = preb;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            dp[i][j] = min(dp[i - 1][j] + tablewb[i][j], dp[i][j - 1] + tablebw[i][j]);
    printf("%d\n", dp[n][n]);
    return 0;
}