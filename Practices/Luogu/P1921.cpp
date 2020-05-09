// P1921.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 55, MAX_M = 1010;

int n, m, q, oi[MAX_M];
double pi[MAX_N], ai[MAX_N][MAX_N], bi[MAX_N][MAX_N], dp[MAX_M][MAX_N];

int main()
{
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; i++)
        scanf("%lf", &pi[i]);
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < q; j++)
            scanf("%lf", &ai[i][j]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%lf", &bi[i][j]);
    for (int i = 1; i <= m; i++)
        scanf("%d", &oi[i]);
    for (int i = 1; i <= n; i++)
        dp[1][i] = pi[i] * ai[i][oi[1]];
    for (int i = 2; i <= m; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= n; k++)
                dp[i][j] += dp[i - 1][k] * bi[k][j] * ai[j][oi[i]];
    double ans = 0;
    for (int i = 1; i <= n; i++)
        ans += dp[m][i];
    printf("%.4lf\n", ans);
    return 0;
}