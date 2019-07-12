// A.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 5020;

int n, m;
ll dp[MAX_N][MAX_N];

int main()
{
    scanf("%d%d", &n, &m);
    dp[1][1] = 1, dp[1][0] = 1, dp[0][1] = 0;
    for (int i = 2; i <= n; i++)
    {
        dp[i][0] = 1;
        for (int j = 1; j <= min(i, m); j++)
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
    }
    printf("%lld", dp[n][m]);
    return 0;
}