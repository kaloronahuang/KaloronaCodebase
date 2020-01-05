// C.cpp
#include <bits/stdc++.h>

using namespace std;

int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + (ch - '0'), ch = getchar();
    return x * f;
}

const int MAX_N = 110, INF = 0x3f3f3f3f;

int n, seq[MAX_N], c[2], dp[MAX_N][MAX_N][2], prefix[MAX_N];
bool vis[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i]), vis[seq[i]] = true, prefix[i] = prefix[i - 1] + (seq[i] == 0);
    for (int i = 1; i <= n; i++)
        if (vis[i] == false)
            c[i % 2]++;
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0][0] = dp[0][0][1] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= min(prefix[i], c[1]); j++)
        {
            int k = prefix[i] - j;
            if (k <= c[0])
            {
                if (seq[i] == 0)
                {
                    if (k > 0)
                        dp[i][j][0] = min(dp[i - 1][j][0], dp[i - 1][j][1] + 1);
                    if (j > 0)
                        dp[i][j][1] = min(dp[i - 1][j - 1][1], dp[i - 1][j - 1][0] + 1);
                }
                else
                    dp[i][j][seq[i] % 2] = min(dp[i - 1][j][seq[i] % 2], dp[i - 1][j][1 - seq[i] % 2] + 1);
            }
        }
    printf("%d\n", min(dp[n][c[1]][0], dp[n][c[1]][1]));
    return 0;
}