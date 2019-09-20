// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010, mod = 2012;

int dp[MAX_N][MAX_N], n, k;

int main()
{
    scanf("%d%d", &n, &k);
    dp[1][0] = 1;
    for (int i = 2; i <= n; i++)
        for (int j = 0; j <= min(n - 1, k); j++)
            dp[i][j] = (1LL * dp[i - 1][j - 1] * (i - j) % mod + 1LL * dp[i - 1][j] * (j + 1) % mod) % mod;
    printf("%d", dp[n][k]);
    return 0;
}