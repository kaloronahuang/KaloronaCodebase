// M.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 110, MAX_K = 1e5 + 200, MOD = 1e9 + 7;
ll n, limit[MAX_N], dp[MAX_N][MAX_K], k, mxk, prefix[MAX_K];
int main()
{
    scanf("%lld%lld", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &limit[i]), dp[i][0] = 1;
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++)
    {
        prefix[i] = 0;
        for (int j = 1; j <= k + 1; j++)
            prefix[j] = prefix[j - 1] + dp[i - 1][j - 1];
        for (int j = 1; j <= k; j++)
        {
            dp[i][j] = dp[i - 1][j] + prefix[j] - prefix[max(0LL, j - limit[i])];
            dp[i][j] %= MOD;
        }
    }
    printf("%d", dp[n][k]);
    return 0;
}