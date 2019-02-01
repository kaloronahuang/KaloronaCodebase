// find.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll mod = 998244353, MAX_N = 1e5 + 200;
ll t, p, a, b;
double p_, a_, b_;
ll dp[MAX_N][2][2];
int main()
{
    freopen("find.in", "r", stdin);
    freopen("find.out", "w", stdout);
    scanf("%lld", &t);
    scanf("%lf%lf%lf", &p_, &a_, &b_);
    scanf("%lld%lld%lld", &p, &a, &b);
    if (p == 1)
    {
        ll subfail = (mod + 1 - (a % mod)) % mod;
        ll ans = 0, fail = 1;
        for (int i = 1; i <= t; i++)
            ans = (ans + a * i * fail) % mod, fail = fail * subfail % mod;
        printf("%lld", ans);
        return 0;
    }
    ll suba = mod + 1 - a, subb = mod + 1 - b, subp = mod + 1 - p;
    dp[0][0][0] = dp[0][1][0] = dp[0][1][1] = dp[0][0][1] = 1;
    for (int r = 1; r <= t; r++)
    {
        dp[r][0][0] = (dp[r - 1][0][0] * suba % mod * dp[r - 1][1][0] * subb % mod) % mod * suba;
        dp[r][0][1] = dp[r - 1][0][0] * dp[r - 1][1][0] * p * a % mod;
        dp[r][1][0] = (dp[r - 1][0][0] * suba % mod * dp[r - 1][1][0] * subb % mod) % mod * subb;
        dp[r][1][1] = dp[r - 1][0][0] * dp[r - 1][1][0] * subp * subb % mod;
    }
    ll ans = 0;
    for (int i = 1; i <= t; i++)
        ans = (ans + max(dp[i][0][1] * i, dp[i][1][1] * i) % mod) % mod;
    ans = (ans + (t + 1) * dp[t][0][0] * dp[t][1][0] % mod) % mod;
    printf("%lld", ans);
    return 0;
}