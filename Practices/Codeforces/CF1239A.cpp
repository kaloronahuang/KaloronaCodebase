// CF1239A.cpp
#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7, MAX_N = 1e5 + 200;

int n, m, dp[MAX_N][2][2];

int main()
{
    scanf("%d%d", &n, &m);
    dp[1][1][0] = dp[1][0][0] = 1;
    for (int i = 2; i <= max(n, m); i++)
    {
        // white settings;
        // both white;
        dp[i][0][1] = dp[i - 1][0][0];
        // the prev one is black or double black;
        dp[i][0][0] = (1LL * dp[i - 1][1][0] + 1LL * dp[i - 1][1][1]) % mod;
        // black settings;
        // both black;
        dp[i][1][1] = dp[i - 1][1][0];
        // double or single;
        dp[i][1][0] = (1LL * dp[i - 1][0][0] + 1LL * dp[i - 1][0][1]) % mod;
    }
    int ans = 0;
    for (int i = 0; i <= 1; i++)
        for (int j = 0; j <= 1; j++)
            ans = (1LL * ans + 1LL * dp[n][i][j] + 1LL * dp[m][i][j]) % mod;
    ans -= 2;
    while (ans < 0)
        ans += mod;
    ans %= mod;
    printf("%d", ans);
    return 0;
}