// P2513.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010, mod = 10000;

int dp[MAX_N][MAX_N], n, k, prefix[MAX_N][MAX_N];

int main()
{
    dp[0][0] = 1;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
    {
        prefix[i - 1][0] = dp[i - 1][0];
        for (int j = 1; j <= k; j++)
            prefix[i - 1][j] = (prefix[i - 1][j - 1] + dp[i - 1][j]) % mod;
        for (int j = 0; j <= k; j++)
            dp[i][j] = (prefix[i - 1][j] + mod - (j - i >= 0 ? prefix[i - 1][j - i] : 0)) % mod;
    }
    printf("%d\n", dp[n][k]);
    return 0;
}