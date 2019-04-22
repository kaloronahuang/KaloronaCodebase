// P3239.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 300;
int T, n, r, di[MAX_N];
double pi[MAX_N], dp[MAX_N][MAX_N], f[MAX_N];

double quick_power(double bas, int tim)
{
    double ans = 1;
    while (tim)
    {
        if (tim & 1)
            ans = ans * bas;
        bas = bas * bas;
        tim >>= 1;
    }
    return ans;
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        memset(dp, 0, sizeof(dp)), memset(f, 0, sizeof(f));
        scanf("%d%d", &n, &r);
        for (int i = 1; i <= n; i++)
            scanf("%lf%d", &pi[i], &di[i]);
        dp[1][0] = quick_power(1 - pi[1], r);
        dp[1][1] = f[1] = 1 - dp[1][0];
        for (int i = 2; i <= n; i++)
        {
            f[i] = 0;
            for (int j = 0; j <= r; j++)
            {
                dp[i][j] = dp[i - 1][j] * quick_power(1 - pi[i], r - j);
                if (j > 0)
                    dp[i][j] += dp[i - 1][j - 1] * (1 - quick_power(1 - pi[i], r - j + 1));
                f[i] += dp[i - 1][j] * (1 - quick_power(1 - pi[i], r - j));
            }
        }
        double ans = 0;
        for (int i = 1; i <= n; i++)
            ans += f[i] * di[i];
        printf("%.10lf\n", ans);
    }
    return 0;
}