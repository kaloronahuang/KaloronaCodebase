// P1136.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 510;
int n, m, dp[MAX_N][110][110], interval[MAX_N];
char str[MAX_N];
int main()
{
    scanf("%d%d", &n, &m);
    scanf("%s", str + 1);
    memset(dp, ~0x3f, sizeof(dp));
    dp[0][0][0] = dp[1][0][0] = dp[1][str[1] == 'j'][str[1] == 'z'] = 0;
    for (int i = 2; i <= n; i++)
    {
        if (str[i - 1] == 'j' && str[i] == 'z')
            interval[i] = 1;
        interval[i] += interval[i - 1];
    }
    for (int i = 2; i <= n; i++)
        for (int j = 0; j <= m; j++)
            for (int k = 0; k <= m; k++)
            {
                dp[i][j][k] = dp[i - 1][j][k];
                if (str[i] == 'z' && str[i - 1] == 'j')
                    dp[i][j][k] = max(dp[i][j][k], dp[i - 2][j][k] + 1);
                if (k && str[i] == str[i - 1] && str[i] == 'z')
                    dp[i][j][k] = max(dp[i][j][k], dp[i - 2][j][k - 1] + 1);
                if (j && str[i] == str[i - 1] && str[i] == 'j')
                    dp[i][j][k] = max(dp[i][j][k], dp[i - 2][j - 1][k] + 1);
                if (j && k && str[i] == 'j' && str[i - 1] == 'z')
                    dp[i][j][k] = max(dp[i][j][k], dp[i - 2][j - 1][k - 1] + 1);
            }
    int ans = 0;
    for (int i = 0; i <= m; i++)
        ans = max(ans, dp[n][i][i]);
    printf("%d", ans);
    return 0;
}