// bracket.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200;

int n, m, dp[2020][2020], mod = 1e9 + 7;
char str[MAX_N];

int main()
{
    freopen("bracket.in", "r", stdin);
    freopen("bracket.out", "w", stdout);
    scanf("%d%d%s", &n, &m, str + 1);
    dp[0][0] = 1;
    for (int i = 1; i <= n - m; i++)
        for (int j = 0; j <= i; j++)
        {
            if (j > 0)
                dp[i][j] = (dp[i][j] + dp[i - 1][j - 1]) % mod;
            if (j < i - 1)
                dp[i][j] = (dp[i][j] + dp[i - 1][j + 1]) % mod;
        }
    int res = 0, prefix = 0;
    for (int i = 1; i <= m; i++)
        prefix += (str[i] == '(') ? 1 : -1, res = min(res, prefix);
    int ans = 0;
    for (int i = -res; i <= n - m; i++)
        for (int j = -res; j <= i; j++)
            if (prefix + j <= n - m - i)
                ans = (1LL * ans + 1LL * dp[i][j] * dp[n - m - i][prefix + j] % mod) % mod;
    printf("%d", ans);
    return 0;
}