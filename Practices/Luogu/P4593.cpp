// P4593.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MAX_N = 60, mod = 1e9 + 7;

ll n, m, k, ai[MAX_N], T, stiring[MAX_N][MAX_N];

ll fpow(ll bas, ll tim)
{
    ll ret = 1;
    bas %= mod;
    while (tim)
    {
        if (tim & 1)
            ret = 1LL * ret * bas % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ret;
}

ll prefix_pow(ll upper)
{
    ll ret = 0;
    for (ll i = 0; i <= k; i++)
    {
        ll pans = 1;
        for (ll j = 0; j <= i; j++)
            pans = 1LL * pans * ((upper + 1 - j + mod) % mod) % mod;
        pans = 1LL * pans * fpow(i + 1, mod - 2) % mod;
        ret = (0LL + ret + 1LL * pans * stiring[k][i] % mod) % mod;
    }
    return ret;
}

int main()
{
    stiring[0][0] = 1;
    for (ll i = 1; i <= 55; i++)
        for (ll j = 1; j <= i; j++)
            stiring[i][j] = (0LL + stiring[i - 1][j - 1] + 1LL * stiring[i - 1][j] * j % mod) % mod;
    scanf("%lld", &T);
    while (T--)
    {
        scanf("%lld%lld", &n, &m), k = m + 1;
        for (ll i = 1; i <= m; i++)
            scanf("%lld", &ai[i]);
        sort(ai + 1, ai + 1 + m);
        ll ans = 0;
        for (ll i = 0; i <= m; i++)
        {
            ans = (0LL + ans + prefix_pow((n - ai[i]) % mod)) % mod;
            for (ll j = i + 1; j <= m; j++)
                ans = (0LL + ans + mod - fpow((ai[j] - ai[i]) % mod, k)) % mod;
        }
        printf("%lld\n", ans);
    }
    return 0;
}