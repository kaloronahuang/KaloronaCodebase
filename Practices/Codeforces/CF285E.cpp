// CF285E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010, mod = 1e9 + 7;

int n, k, dp[MAX_N][MAX_N][4], binomial[MAX_N][MAX_N], f[MAX_N], fac[MAX_N];

int main()
{
    scanf("%d%d", &n, &k);
    binomial[0][0] = 1;
    for (int i = fac[0] = 1; i <= n; i++)
    {
        fac[i] = 1LL * fac[i - 1] * i % mod;
        binomial[i][0] = binomial[i][i] = 1;
        for (int j = 1; j < i; j++)
            binomial[i][j] = (0LL + binomial[i - 1][j - 1] + binomial[i - 1][j]) % mod;
    }
    dp[0][0][1] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < i; j++)
            for (int S = 0; S < 4; S++)
            {
                dp[i][j][S >> 1] = (0LL + dp[i][j][S >> 1] + dp[i - 1][j][S]) % mod;
                if (~S & 1)
                    dp[i][j + 1][S >> 1] = (0LL + dp[i][j + 1][S >> 1] + dp[i - 1][j][S]) % mod;
                if (i != n)
                    dp[i][j + 1][(S >> 1) | 2] = (0LL + dp[i][j + 1][(S >> 1) | 2] + dp[i - 1][j][S]) % mod;
            }
    for (int i = 0; i <= n; i++)
        for (int stat = 0; stat < 4; stat++)
            f[i] = (0LL + f[i] + 1LL * dp[n][i][stat] * fac[n - i] % mod) % mod;
    int ans = 0;
    for (int i = k, opt = 1; i <= n; i++, opt = mod - opt)
        ans = (0LL + ans + 1LL * f[i] * binomial[i][k] % mod * opt % mod) % mod;
    printf("%d\n", ans);
    return 0;
}