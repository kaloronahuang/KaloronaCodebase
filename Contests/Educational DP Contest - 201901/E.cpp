// E.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#define ll long long
using namespace std;
const int MX_N = 1e5 + 200;
ll n, wi[101], vi[101], dp[MX_N], W;
int main()
{
    scanf("%lld%lld", &n, &W);
    int tot = 0;
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;
    for (int i = 1; i <= n; i++)
        scanf("%lld%lld", &wi[i], &vi[i]), tot += vi[i];
    for (int i = 1; i <= n; i++)
        for (int cv = tot; cv >= vi[i]; cv--)
            dp[cv] = min(dp[cv], dp[cv - vi[i]] + wi[i]);
    ll ans = 0;
    for (int i = tot; i >= 0; i--)
        if (dp[i] <= W)
            printf("%d", i), exit(0);
    printf("%lld", ans);
    return 0;
}
