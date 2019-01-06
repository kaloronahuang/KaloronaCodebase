// C.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
using namespace std;
const int MX_N = 1e5 + 200;
ll n, ai[MX_N], bi[MX_N], ci[MX_N], dp[MX_N][3];
int main()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld%lld%lld", &ai[i], &bi[i], &ci[i]);
    for (int i = 1; i <= n; i++)
    {
        dp[i][0] = max(dp[i - 1][1] + ai[i], dp[i - 1][2] + ai[i]);
        dp[i][1] = max(dp[i - 1][0] + bi[i], dp[i - 1][2] + bi[i]);
        dp[i][2] = max(dp[i - 1][1] + ci[i], dp[i - 1][0] + ci[i]);
    }
    printf("%lld", max(dp[n][0], max(dp[n][1], dp[n][2])));
    return 0;
}