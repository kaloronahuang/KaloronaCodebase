// UOJ311.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 440, mod = 998244353;

int n, m, wi[MAX_N][MAX_N], dp[MAX_N][MAX_N];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &wi[1][i]), wi[0][i] = 1;
        for (int j = 2; j <= m; j++)
            wi[j][i] = 1LL * wi[j - 1][i] * wi[1][i] % mod;
    }
    for (int i = 0; i <= n; i++)
        dp[0][i] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            dp[i][j] = dp[i][j - 1];
            for (int k = 1; k <= i; k++)
            {
                int tmp = 1LL * dp[k - 1][j] * dp[i - k][j - 1] % mod;
                int idx = max(0, min(k, i - m + 1) - max(1, k - m + 1) + 1);
                // int idx = min({m, max(0, i - m + 1), k, i - k + 1});
                tmp = 1LL * tmp * wi[idx][j] % mod;
                dp[i][j] = (0LL + dp[i][j] + tmp) % mod;
            }
        }
    printf("%d\n", dp[n][n]);
    return 0;
}