// D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 330, mod = 998244353;

int n, dp[MAX_N][MAX_N][MAX_N], vis[MAX_N][MAX_N][MAX_N];
bool verdict[MAX_N][MAX_N][MAX_N];
char str[MAX_N];

int main()
{
    scanf("%s", str + 1), n = strlen(str + 1);
    dp[n][0][0] = 1;
    for (int i = n; i >= 1; i--)
        for (int j = 0; j + (n - i) <= n - 1; j++)
            for (int k = 0; j + k + (n - i) <= n - 1; k++)
                if (str[i] == '0')
                {
                    dp[i - 1][j][k] = (0LL + dp[i - 1][j][k] + dp[i][j][k]) % mod;
                    dp[i][j][k + 1] = (0LL + dp[i][j][k + 1] + dp[i][j][k]) % mod;
                }
                else
                {
                    dp[i - 1][j][k] = (0LL + dp[i - 1][j][k] + dp[i][j][k]) % mod;
                    dp[i][j + 1][k] = (0LL + dp[i][j + 1][k] + dp[i][j][k]) % mod;
                }
    memset(vis, -1, sizeof(vis)), vis[0][0][0] = 0;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= (i >> 1); j++)
            for (int k = 0; j + k <= (i >> 1); k++)
                if (vis[i][j][k] != -1)
                {
                    int c = vis[i][j][k];
                    if (i + 1 <= n && c != 0)
                    {
                        if (str[i + 1] == '0')
                            vis[i + 1][j + 1][k] = max(vis[i + 1][j + 1][k], c - 1);
                        if (str[i + 1] == '1')
                            vis[i + 1][j][k + 1] = max(vis[i + 1][j][k + 1], c - 1);
                    }
                    if (i + 2 <= n)
                    {
                        if (str[i + 1] == '0' || str[i + 2] == '0')
                            vis[i + 2][j + 1][k] = max(vis[i + 2][j + 1][k], c);
                        if (str[i + 1] == '1' || str[i + 2] == '1')
                            vis[i + 2][j][k + 1] = max(vis[i + 2][j][k + 1], c);
                        vis[i + 2][j][k] = max(vis[i + 2][j][k], c + 1);
                    }
                }
    for (int i = 0; i <= n; i++)
        for (int j = n; j >= 0; j--)
            for (int k = n; k >= 0; k--)
            {
                verdict[i][j][k] = vis[i][j][k] != -1;
                if (i > 0)
                    verdict[i][j][k] |= verdict[i - 1][j][k];
                verdict[i][j][k] |= verdict[i][j + 1][k] || verdict[i][j][k + 1];
            }
    int ans = 0;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j + (n - i) <= n; j++)
            for (int k = 0; j + k + (n - i) <= n; k++)
                if (dp[i][j][k] && (n - i) + j + k != 0 && verdict[i][j][k])
                    ans = (0LL + ans + dp[i][j][k]) % mod;
    printf("%d\n", ans);
    return 0;
}