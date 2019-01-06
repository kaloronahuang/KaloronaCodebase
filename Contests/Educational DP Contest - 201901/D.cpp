// D.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
using namespace std;
const int MX_N = 1e5 + 200;
ll n, wi[120], vi[120], dp[2][MX_N], W;

int main()
{
    scanf("%lld%lld", &n, &W);
    for (int i = 1; i <= n; i++)
        scanf("%lld%lld", &wi[i], &vi[i]);
    for (int i = 1; i <= n; i++)
        for (int cv = 0; cv <= W; cv++)
        {
            dp[i & 1][cv] = dp[i & 1 ^ 1][cv];
            if (cv >= wi[i])
                dp[i & 1][cv] = max(dp[i & 1][cv], dp[i & 1 ^ 1][cv - wi[i]] + vi[i]);
        }
    printf("%lld", dp[n & 1][W]);
    return 0;
}