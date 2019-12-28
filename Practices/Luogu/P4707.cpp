// P4707.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010, mod = 998244353;

int n, k, m, inv[MAX_N * 10], dp[20][MAX_N * 10];

int quick_pow(int bas, int tim)
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
    scanf("%d%d%d", &n, &k, &m), k = n - k + 1;
    for (int i = 1; i <= m; i++)
        inv[i] = quick_pow(i, mod - 2);
    for (int i = 1; i <= k; i++)
        dp[i][0] = mod - 1;
    for (int i = 1, pi; i <= n; i++)
    {
        scanf("%d", &pi);
        for (int j = m; j >= pi; j--)
            for (int s = k; s >= 1; s--)
                dp[s][j] = (1LL * dp[s][j] + (0LL + dp[s - 1][j - pi] + mod - dp[s][j - pi])) % mod;
    }
    int ans = 0;
    for (int i = 1; i <= m; i++)
        ans = (1LL * ans + 1LL * dp[k][i] * inv[i] % mod) % mod;
    printf("%lld\n", 1LL * ans * m % mod);
    return 0;
}