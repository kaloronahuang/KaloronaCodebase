// D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2020, base = MAX_N;

int n, mod, dp[MAX_N * 3][MAX_N * 4];

int main()
{
    scanf("%d%d", &n, &mod), dp[0][base] = 1;
    for (int i = 0; i < 3 * n; i++)
        for (int j = -n; j <= 3 * n; j++)
        {
            dp[i + 1][j + 1 + base] = (0LL + dp[i + 1][j + 1 + base] + dp[i][j + base]) % mod;
            dp[i + 2][j - 1 + base] = (0LL + dp[i + 2][j - 1 + base] + 1LL * dp[i][j + base] * (i + 1) % mod) % mod;
            dp[i + 3][j + base] = (0LL + dp[i + 3][j + base] + 1LL * dp[i][j + base] * (i + 2) % mod * (i + 1) % mod) % mod;
        }
    int ans = 0;
    for (int i = 0; i <= 3 * n; i++)
        ans = (0LL + ans + dp[3 * n][i + base]) % mod;
    printf("%d\n", ans);
    return 0;
}