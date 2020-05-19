// subsequence.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4040;

int n, m, k, nxt[2][MAX_N][MAX_N], sA[MAX_N], sB[MAX_N], dp[MAX_N][MAX_N];

int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &sA[i]);
    for (int i = 1; i <= m; i++)
        scanf("%d", &sB[i]);
    for (int c = 1; c <= k; c++)
        nxt[0][n][c] = n + 1, nxt[1][m][c] = m + 1, nxt[0][n + 1][c] = n + 1, nxt[1][m + 1][c] = m + 1;
    for (int i = n - 1; i >= 0; i--)
    {
        for (int c = 1; c <= k; c++)
            nxt[0][i][c] = nxt[0][i + 1][c];
        nxt[0][i][sA[i + 1]] = i + 1;
    }
    for (int i = m - 1; i >= 0; i--)
    {
        for (int c = 1; c <= k; c++)
            nxt[1][i][c] = nxt[1][i + 1][c];
        nxt[1][i][sB[i + 1]] = i + 1;
    }
    memset(dp, -1, sizeof(dp)), dp[0][0] = 0;
    for (int i = 0; i <= min(n, m); i++)
    {
        for (int j = 0; j <= n; j++)
            if (dp[i][j] != -1)
            {
                for (int c = 1; c <= k; c++)
                    dp[i + 1][nxt[0][j][c]] = max(dp[i + 1][nxt[0][j][c]], nxt[1][dp[i][j]][c]);
            }
        if (dp[i + 1][n + 1] == m + 1)
            printf("%d\n", i + 1), exit(0);
    }
    return 0;
}