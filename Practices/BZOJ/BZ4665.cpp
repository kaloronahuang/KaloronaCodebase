// BZ4665.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll MAX_N = 2020, mod = 1000000009;
ll n, arr[MAX_N], level[MAX_N], level_rev[MAX_N], dp[MAX_N][MAX_N], cnt[MAX_N];

ll quick_pow(ll bas, ll tim)
{
    ll ans = 1;
    while (tim)
    {
        if (tim & 1)
            ans = ans * bas % mod;
        bas = bas * bas % mod;
        tim >>= 1;
    }
    return ans;
}

ll comb(ll a, ll b)
{
    return level[a] * level_rev[a - b] % mod * level_rev[b] % mod;
}

int main()
{
    scanf("%lld", &n);
    for (ll i = 1; i <= n; i++)
        scanf("%lld", &arr[i]), cnt[arr[i]]++;

    level[0] = level[1] = level_rev[0] = level_rev[1] = 1;
    for (ll i = 2; i < MAX_N; i++)
        level[i] = level[i - 1] * i % mod;
    level_rev[MAX_N - 1] = quick_pow(level[MAX_N - 1], mod - 2);
    for (ll i = MAX_N - 1; i >= 3; i--)
        level_rev[i - 1] = level_rev[i] * i % mod;
    dp[0][0] = 1;
    for (ll i = 1; i <= n; i++)
        for (ll j = 0; j <= n; j++)
            for (ll k = 0; k <= cnt[i]; k++)
            {
                if (k > j)
                    break;
                dp[i][j] = (dp[i][j] + dp[i - 1][j - k] * comb(cnt[i], k) % mod * level[cnt[i]] % mod * level_rev[cnt[i] - k] % mod) % mod;
            }
    ll ans = 0;
    for (ll i = 0; i <= n; i++)
    {
        dp[n][i] = (dp[n][i] * level[n - i] % mod);
        if (i & 1)
            dp[n][i] = (dp[n][i] * (-1) + mod) % mod;
        ans = (ans + dp[n][i] + mod) % mod;
    }
    for (ll i = 1; i <= n; i++)
        ans = ans * level_rev[cnt[i]] % mod;
    printf("%lld", ans);
    return 0;
}