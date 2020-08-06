// BZ2655.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010;

int A, n, mod, dp[MAX_N][MAX_N];

int fpow(int bas, int tim)
{
    int ret = 1;
    while (tim)
    {
        if (tim & 1)
            ret = 1LL * ret * bas % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ret;
}

int main()
{
    scanf("%d%d%d", &A, &n, &mod), dp[0][0] = 1;
    for (int i = 1; i <= 2 * n + 1; i++)
    {
        dp[i][0] = dp[i - 1][0];
        for (int j = 1; j <= n; j++)
            dp[i][j] = (0LL + dp[i - 1][j] + 1LL * dp[i - 1][j - 1] * i % mod) % mod;
    }
    int ans = 0;
    if (A <= 2 * n + 1)
        ans = dp[A][n];
    else
        for (int i = 1; i <= 2 * n + 1; i++)
        {
            // yi[i] = f[i][n];
            int pans = 1;
            for (int j = 1; j <= 2 * n + 1; j++)
                if (i != j)
                    pans = 1LL * pans * ((0LL + A + mod - j) % mod) % mod * fpow((0LL + i + mod - j) % mod, mod - 2) % mod;
            ans = (0LL + ans + 1LL * dp[i][n] * pans % mod) % mod;
        }
    for (int i = 1; i <= n; i++)
        ans = 1LL * ans * i % mod;
    printf("%lld\n", ans);
    return 0;
}