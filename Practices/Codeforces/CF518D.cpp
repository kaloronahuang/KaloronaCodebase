// CF518D.cpp
#include <bits/stdc++.h>
using namespace std;
int n, t;
double p, dp[2020][2020], ans;
int main()
{
    scanf("%d%lf%d", &n, &p, &t);
    dp[0][0] = 1;
    for (int i = 0; i < t; i++)
    {
        dp[i + 1][n] += dp[i][n];
        for (int j = 0; j < n; j++)
            dp[i + 1][j + 1] += dp[i][j] * p, dp[i + 1][j] += dp[i][j] * (1 - p);
    }
    for (int j = 0; j <= n; j++)
        ans += dp[t][j] * j;
    printf("%.6lf", ans);
    return 0;
}