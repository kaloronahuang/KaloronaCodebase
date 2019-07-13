// C.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 60;

ll dp[2][MAX_N], n, m;

int main()
{
    scanf("%lld%lld", &n, &m);
    dp[0][0] = 1, dp[1][0] = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = i; j >= 1; j--)
            dp[i & 1][j] += dp[i & 1][j - 1] * (i - j + 1);
        if (i < n)
            for (int j = i; j >= 1; j--)
                dp[i & 1][j] += dp[i & 1][j - 1] * (i - j + 1);
    }
    ll ans = 0;
    for (int i = 0; i <= m; i++)
        ans += dp[0][i] * dp[1][m - i];
    printf("%lld", ans);
    return 0;
}