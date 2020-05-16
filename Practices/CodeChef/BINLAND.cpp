// BINLAND.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 22, MAX_Q = 3e5 + 200, mod = 1e9 + 7;

int n, q, dp[2][MAX_Q][MAX_N][MAX_N], end_pos[2];
char content[2][MAX_Q][MAX_N], cmdlet[MAX_N];

void push_back(int idx)
{
    int &tail = end_pos[idx];
    if (tail >= 2)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
                dp[idx][tail][i][j] = 0;
            for (int j = i - 1; j <= i + 1; j++)
                if (1 <= j && j <= n && content[idx][tail][i] == content[idx][tail - 1][j])
                    for (int k = 1; k <= n; k++)
                        dp[idx][tail][i][k] = (0LL + dp[idx][tail][i][k] + dp[idx][tail - 1][j][k]) % mod;
        }
    }
    else
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                dp[idx][1][i][j] = (i == j);
}

int main()
{
    scanf("%d%d", &n, &q);
    while (q--)
    {
        scanf("%s", cmdlet + 1);
        if (cmdlet[1] == 'a')
            scanf("%s", content[1][++end_pos[1]] + 1), push_back(1);
        else if (cmdlet[1] == 'r')
        {
            if (end_pos[0] == 0)
                while (end_pos[1])
                    memcpy(content[0][++end_pos[0]], content[1][end_pos[1]--], sizeof(content[1][1])), push_back(0);
            end_pos[0]--;
        }
        else
        {
            int x, y, ans = 0;
            scanf("%d%d", &x, &y);
            if (end_pos[1] == 0)
                printf("%d\n", dp[0][end_pos[0]][x][y]);
            else if (end_pos[0] == 0)
                printf("%d\n", dp[1][end_pos[1]][y][x]);
            else
            {
                for (int i = 1; i <= n; i++)
                    for (int j = i - 1; j <= i + 1; j++)
                        if (1 <= j && j <= n && content[0][1][i] == content[1][1][j])
                            ans = (0LL + ans + 1LL * dp[0][end_pos[0]][x][i] * dp[1][end_pos[1]][y][j] % mod) % mod;
                printf("%d\n", ans);
            }
        }
    }
    return 0;
}