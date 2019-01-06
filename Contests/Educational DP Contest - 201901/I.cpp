// I.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
int n;
double dp[3000][3000], pro[3000];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lf", &pro[i]);
    for(int i = 0;i<=n;i++)
        dp[0][i] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= (int)((i - 1) / 2) + 1; j++)
            dp[i][j] = dp[i - 1][j] * (1 - pro[i]) + dp[i - 1][j - 1] * pro[i];
    double ans = 0;
    for (int j = 1; j <= (int)((n - 1) / 2) + 1; j++)
        ans += dp[n][j];
    printf("%lf", ans);
    return 0;
}