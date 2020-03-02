// land.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 30;

int n, m, prefix[MAX_N][MAX_N];
short dp[MAX_N][MAX_N][MAX_N][MAX_N];
char str[MAX_N];

void fileIO()
{
    freopen("land.in", "r", stdin);
    freopen("land.out", "w", stdout);
}

int calc(int x1, int y1, int x2, int y2) { return prefix[x2][y2] - prefix[x1 - 1][y2] - prefix[x2][y1 - 1] + prefix[x1 - 1][y1 - 1]; }

int main()
{
    fileIO();
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", str + 1);
        for (int j = 1; j <= m; j++)
            prefix[i][j] = prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1] + (str[j] == '#');
    }
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            for (int lower = 1; lower <= i; lower++)
                for (int lft = 1; lft <= j; lft++)
                {
                    int tmp = calc(lower, lft, i, j);
                    if (tmp == 0 || tmp == (i - lower + 1) * (j - lft + 1))
                        dp[lower][lft][i][j] = 0;
                }
    for (int leni = 1; leni <= n; leni++)
        for (int lenj = 1; lenj <= m; lenj++)
            for (int lower = 1; lower + leni - 1 <= n; lower++)
                for (int lft = 1; lft + lenj - 1 <= m; lft++)
                {
                    int i = lower + leni - 1, j = lft + lenj - 1;
                    for (int k = lower; k < i; k++)
                        dp[lower][lft][i][j] = min(short(max(dp[lower][lft][k][j], dp[k + 1][lft][i][j]) + 1), dp[lower][lft][i][j]);
                    for (int k = lft; k < j; k++)
                        dp[lower][lft][i][j] = min(short(max(dp[lower][lft][i][k], dp[lower][k + 1][i][j]) + 1), dp[lower][lft][i][j]);
                }
    printf("%d\n", dp[1][1][n][m]);
    return 0;
}