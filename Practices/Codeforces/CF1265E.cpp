// CF1265E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, mod = 998244353;

int n, pi[MAX_N], dp[MAX_N];

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
    const int inv100 = quick_pow(100, mod - 2);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &pi[i]), pi[i] = 1LL * pi[i] * inv100 % mod;
    for (int i = 1; i <= n; i++)
        dp[i] = 1LL * ((1LL * dp[i - 1] + 1) % mod) * quick_pow(pi[i], mod - 2) % mod;
    printf("%d", dp[n]);
    return 0;
}