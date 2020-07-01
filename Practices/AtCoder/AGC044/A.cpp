// A.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int base[] = {2, 3, 5};

int T;
ll n, prices[4];
map<ll, ll> dp;

ll dfs(ll u)
{
    if (dp.count(u))
        return dp[u];
    dp[u] = 0x7fffffffffffffff;
    for (int i = 0; i < 3; i++)
    {
        int x = base[i];
        ll lft = u / x, rig = (u + x - 1) / x;
        dp[u] = min(dp[u], dfs(lft) + prices[i] + 1LL * prices[3] * abs(u - 1LL * lft * x));
        dp[u] = min(dp[u], dfs(rig) + prices[i] + 1LL * prices[3] * abs(u - 1LL * rig * x));
    }
    if (u < dp[u] / prices[3])
        dp[u] = min(dp[u], 1LL * prices[3] * u);
    return dp[u];
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%lld%lld%lld%lld%lld", &n, &prices[0], &prices[1], &prices[2], &prices[3]), dp.clear(), dp[0] = 0, dp[1] = prices[3];
        printf("%lld\n", dfs(n));
    }
    return 0;
}