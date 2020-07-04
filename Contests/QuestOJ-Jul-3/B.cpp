// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010, mod = 1e9 + 7;

int n, len, p, threshold, dp[MAX_N * MAX_N], pre[MAX_N * MAX_N];

int main()
{
    scanf("%d%d%d", &n, &len, &p);
    threshold = 1;
    for (int i = len + 1; i <= n; i++)
        threshold += min(i - len + 1, len);
    if (p > threshold)
        puts("0"), exit(0);
    dp[1] = 1;
    for (int i = 1; i <= len; i++)
        dp[1] = 1LL * dp[1] * i % mod;
    threshold = 1;
    for (int i = len + 1; i <= n; i++)
    {
        int delta = min(i - len + 1, len);
        threshold += delta;
        for (int j = 1; j <= threshold && j <= p; j++)
            pre[j] = (0LL + pre[j - 1] + dp[j]) % mod;
        for (int j = min(p, threshold); j >= 1; j--)
        {
            dp[j] = 2LL * (pre[j - 1] + mod - pre[j > delta ? j - delta : 0]) % mod;
            if (j >= delta)
                dp[j] = (0LL + dp[j] + 1LL * (i - 2LL * (delta - 1)) * dp[j - delta] % mod) % mod;
        }
    }
    printf("%d\n", dp[p]);
    return 0;
}