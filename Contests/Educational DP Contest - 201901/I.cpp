// I.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 3030;
int n;
double prob[MAX_N], dp[MAX_N][MAX_N];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lf", &prob[i]);
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= i; j++)
        {
            int x = j, y = i - j;
            if (x)
                dp[x][y] += dp[x - 1][y] * prob[i];
            if (y)
                dp[x][y] += dp[x][y - 1] * (1 - prob[i]);
        }
    double ans = 0;
    for (int i = 0; n - i > i; i++)
        ans += dp[n - i][i];
    printf("%.10lf", ans);
    return 0;
}