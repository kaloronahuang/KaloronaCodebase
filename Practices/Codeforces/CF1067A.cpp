// CF1067A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, mod = 998244353;

int n, ai[MAX_N], dp[2][220][3];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    if (ai[1] == -1)
        for (int i = 1; i <= 200; i++)
            dp[1][i][0] = 1;
    else
        dp[1][ai[1]][0] = 1;
    for (int i = 2; i <= n; i++)
    {
        memset(dp[i & 1], 0, sizeof(dp[i & 1]));
        int sum = 0;
        for (int j = 1; j <= 200; j++)
        {
            dp[i & 1][j][0] = (ai[i] == -1 || ai[i] == j) ? sum : 0;
            sum = (0LL + sum + dp[!(i & 1)][j][0] + dp[!(i & 1)][j][1] + dp[!(i & 1)][j][2]) % mod;
        }
        for (int j = 1; j <= 200; j++)
            dp[i & 1][j][1] = (ai[i] == -1 || ai[i] == j) ? (0LL + dp[!(i & 1)][j][0] + dp[!(i & 1)][j][1] + dp[!(i & 1)][j][2]) % mod : 0;
        sum = 0;
        for (int j = 200; j >= 1; j--)
        {
            dp[i & 1][j][2] = (ai[i] == -1 || ai[i] == j) ? sum : 0;
            sum = (0LL + sum + dp[!(i & 1)][j][1] + dp[!(i & 1)][j][2]) % mod;
        }
    }
    int ans = 0;
    for (int i = 1; i <= 200; i++)
        ans = (0LL + ans + dp[n & 1][i][1] + dp[n & 1][i][2]) % mod;
    printf("%d\n", ans);
    return 0;
}