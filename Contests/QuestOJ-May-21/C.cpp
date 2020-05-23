// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 350, mod = 998244353;

int n, m, X, dp[2][MAX_N][MAX_N], prod[2][MAX_N][MAX_N], g[MAX_N];

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
    scanf("%d%d%d", &n, &m, &X);
    if (n > m)
        puts("0"), exit(0);
    for (int i = 1; i <= n; i++)
        g[i] = fpow(i, X);
    dp[0][0][0] = 1;
    int i = 0;
    for (int u = 1; u <= m; u++)
    {
        // memset(dp[i ^ 1], 0, sizeof(dp[(i + 1) & 1]));
        for (int j = 0; j <= n; j++)
            for (int k = 0; k <= j; k++)
                if (dp[i][j][k] > 0 || prod[i][j][k] > 0)
                {
                    prod[i][j][k] = (0LL + prod[i][j][k] + 1LL * dp[i][j][k] * g[j - k] % mod) % mod;
                    for (int dj = 0; dj <= 1; dj++)
                        for (int dk = 0; dk <= 1; dk++)
                            if (j + dj >= k + dk)
                            {
                                dp[i ^ 1][j + dj][k + dk] = (0LL + dp[i ^ 1][j + dj][k + dk] + dp[i][j][k]) % mod;
                                prod[i ^ 1][j + dj][k + dk] = (0LL + prod[i ^ 1][j + dj][k + dk] + prod[i][j][k]) % mod;
                            }
                    dp[i][j][k] = prod[i][j][k] = 0;
                }
        i ^= 1;
    }
    printf("%d\n", prod[i][n][n]);
    return 0;
}