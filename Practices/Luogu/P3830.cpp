// P3830.cpp
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 110;
int n, q;
double dp[MAX_N], f[MAX_N][MAX_N];

int main()
{
    scanf("%d%d", &q, &n);
    if (q == 1)
    {
        dp[1] = 0;
        for (int i = 2; i <= n; i++)
            dp[i] = dp[i - 1] + 2.0 / double(i);
        printf("%.6lf", dp[n]);
    }
    else
    {
        for (int i = 1; i <= n; i++)
            f[i][0] = 1;
        for (int i = 2; i <= n; i++)
            for (int j = 1; j < i; j++)
            {
                for (int k = 1; k <= i - 1; k++)
                    f[i][j] += f[k][j - 1] + f[i - k][j - 1] - f[k][j - 1] * f[i - k][j - 1];
                f[i][j] /= i - 1;
            }
        double ans = 0;
        for (int i = 1; i <= n - 1; i++)
            ans += f[n][i];
        printf("%.6lf", ans);
    }
    return 0;
}