// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2020;

int white_pos[MAX_N], black_pos[MAX_N], n, m, black_mov[MAX_N][MAX_N], white_mov[MAX_N][MAX_N];
int dp[MAX_N][MAX_N];
char opt[5];

int main()
{
    scanf("%d", &n);
    for (int i = 1, tmp; i <= 2 * n; i++)
        scanf("%s%d", opt + 1, &tmp), (opt[1] == 'B' ? black_pos[tmp] : white_pos[tmp]) = i;
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
        {
            white_mov[i][n] += white_pos[j] < white_pos[i];
            black_mov[i][n] += black_pos[j] < black_pos[i];
        }
    for (int i = 1; i <= n; i++)
        for (int j = n - 1; j >= 0; j--)
        {
            white_mov[i][j] = white_mov[i][j + 1] + (black_pos[j + 1] < white_pos[i]);
            black_mov[i][j] = black_mov[i][j + 1] + (white_pos[j + 1] < black_pos[i]);
        }
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
        {
            if (i > 0)
                dp[i][j] = min(dp[i][j], dp[i - 1][j] + white_mov[i][j]);
            if (j > 0)
                dp[i][j] = min(dp[i][j], dp[i][j - 1] + black_mov[j][i]);
        }
    printf("%d", dp[n][n]);
    return 0;
}