// P4187.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200, mod = 1e9 + 7;

int dp[MAX_N], prefix[MAX_N], n, m, k;

int quick_pow(int bas, int tim)
{
    int ret = 1;
    bas %= mod;
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
    scanf("%d%d%d", &n, &m, &k);
    int ans = quick_pow(m, n);
    dp[0] = prefix[0] = 1;
    for (int i = 1; i < min(n, k); i++)
        dp[i] = 1LL * dp[i - 1] * m % mod, prefix[i] = (1LL * prefix[i - 1] + 1LL * dp[i]) % mod;
    for (int i = min(n, k); i <= n; i++)
        dp[i] = 1LL * (1LL * prefix[i - 1] + mod - prefix[i - k]) % mod * (m - 1) % mod, prefix[i] = (1LL * prefix[i - 1] + 1LL * dp[i]) % mod;
    ans = (1LL * ans + mod - dp[n]) % mod;
    printf("%d", ans);
    return 0;
}