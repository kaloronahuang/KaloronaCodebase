// FOJ6353.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5050, mod = 998244353;

int dp[MAX_N << 1][MAX_N], n, m;

int main()
{
    freopen("ca.in", "r", stdin);
    freopen("ca.out", "w", stdout);
    scanf("%d%d", &m, &n);

    dp[1][0] = 1;

    for (int i = 1; i < (n << 1) - 1; i++)
    {
        for (int j = 0; j < min(m, i); j++)
        {
            dp[i + 1][j - 1] = (1LL * dp[i + 1][j - 1] + dp[i][j]) % mod;
            dp[i + 1][j + 1] = (1LL * dp[i + 1][j + 1] + dp[i][j]) % mod;
        }
    }
    for (int i = 1; i <= n; i++)
        printf("%d\n", dp[(i << 1) - 1][0]);
    return 0;
}