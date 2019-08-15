// C.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const ll MAX_N = 20000010, mod = 998244353;

ll T, fac[MAX_N], fac_inv[MAX_N], n;

ll quick_pow(ll bas, ll tim)
{
    ll ans = 1;
    bas %= mod;
    while (tim)
    {
        if (tim & 1)
            ans = 1LL * ans * bas % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ans;
}

ll comb(ll n_, ll k_) { return 1LL * fac[n_] * fac_inv[k_] % mod * fac_inv[n_ - k_] % mod; }

int main()
{
    /*
    freopen("tg.in", "r", stdin);
    freopen("tg.out", "w", stdout);
    */
    fac[0] = fac_inv[0] = 1;
    for (ll i = 1; i < MAX_N; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    fac_inv[MAX_N - 1] = quick_pow(fac[MAX_N - 1], mod - 2);
    for (ll i = MAX_N - 2; i >= 1; i--)
        fac_inv[i] = 1LL * fac_inv[i + 1] * (i + 1) % mod;
    scanf("%lld", &T);
    while (T--)
    {
        ll x, y;
        scanf("%lld%lld%lld", &n, &x, &y);
        if (x < y)
            swap(x, y);
        ll ans1 = (1LL * comb(y + x - 2, x - 1) - 1LL * comb(y + x - 2, x)) % mod;
        ll ans2 = (1LL * comb(n - y + n - x, n - x) - 1LL * comb(n - x + n - y, n - x - 1)) % mod;
        printf("%lld\n", (1LL * ans1 * ans2 % mod + mod) % mod);
    }
    return 0;
}