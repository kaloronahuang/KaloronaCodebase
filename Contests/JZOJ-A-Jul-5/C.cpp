// C.cpp
#include <bits/stdc++.h>
#define ll long long

const ll MAX_N = 130300, mod = 1004535809;

using namespace std;

ll level[MAX_N], inv_level[MAX_N], n, dp[MAX_N];

ll quick_pow(ll bas, ll tim)
{
    ll ans = 1;
    bas %= mod;
    while (tim)
    {
        if (tim & 1)
            ans = ans * bas % mod;
        bas = bas * bas % mod;
        tim >>= 1;
    }
    return ans;
}

ll comb(ll n_, ll k_) { return level[n_] * inv_level[n_ - k_] % mod * inv_level[k_] % mod; }

int main()
{
    scanf("%d", &n), level[0] = 1;
    for (ll i = 1; i <= n; i++)
        level[i] = level[i - 1] * i % mod;
    inv_level[n] = quick_pow(level[n], mod - 2);
    for (ll i = n - 1; i >= 1; i--)
        inv_level[i] = inv_level[i + 1] * (i + 1) % mod;
    inv_level[0] = inv_level[1];

    dp[1] = 1;
    for (ll i = 2; i <= n; i++)
    {
        dp[i] = quick_pow(2, (i * (i - 1)) >> 1);
        for (ll k = 1; k <= i - 1; k++)
            dp[i] -= dp[k] * comb(i - 1, k - 1) % mod * quick_pow(2, ((i - k) * (i - k - 1)) >> 1) % mod, dp[i] = (dp[i] + mod) % mod;
    }
    printf("%lld", dp[n]);
    return 0;
}