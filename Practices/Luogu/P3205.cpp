// P3205.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010, mod = 19650827;

int dp[MAX_N][MAX_N][2], n, seq[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i]);
    for (int i = 1; i <= n; i++)
        dp[i][i][0] = 1;
    for (int len = 2; len <= n; len++)
    {
        for (int i = 1; i + len - 1 <= n; i++)
        {
            int j = i + len - 1;
            // right-oriented;
            if (seq[j] > seq[i])
                dp[i][j][1] = (1LL * dp[i][j - 1][0] + 1LL * dp[i][j][1]) % mod;
            if (seq[j] > seq[j - 1])
                dp[i][j][1] = (1LL * dp[i][j - 1][1] + 1LL * dp[i][j][1]) % mod;
            // left oriented;
            if (seq[i] < seq[j])
                dp[i][j][0] = (1LL * dp[i + 1][j][1] + 1LL * dp[i][j][0]) % mod;
            if (seq[i] < seq[i + 1])
                dp[i][j][0] = (1LL * dp[i + 1][j][0] + 1LL * dp[i][j][0]) % mod;
        }
    }
    printf("%d", (dp[1][n][0] + dp[1][n][1]) % mod);
    return 0;
}