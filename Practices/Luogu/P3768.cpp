// P3768.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const ll MAX_N = 5e6 + 2000;
ll n, mod, phi[MAX_N], prime[MAX_N], tot, inv2, inv6;
bool vis[MAX_N];
unordered_map<ll, ll> ump;

ll getPreQuad(ll num)
{
    num %= mod;
    return num * (num + 1) % mod * inv2 % mod;
}

ll getPreThird(ll num)
{
    num %= mod;
    return num * (num + 1) % mod * (num + num + 1) % mod * inv6 % mod;
}

void phi_sieve()
{
    phi[1] = 1;
    for (ll i = 2; i < MAX_N; i++)
    {
        if (!vis[i])
            prime[++tot] = i, phi[i] = i - 1;
        for (ll j = 1; j <= tot && 1ll * prime[j] * i < MAX_N; j++)
        {
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0)
            {
                phi[i * prime[j]] = phi[i] * prime[j] % mod;
                break;
            }
            phi[i * prime[j]] = phi[i] * phi[prime[j]] % mod;
        }
    }
    for (ll i = 2; i < MAX_N; i++)
        phi[i] = (phi[i] * i % mod * i % mod + phi[i - 1]) % mod;
}

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

ll sieve(ll num)
{
    if (num < MAX_N)
        return phi[num];
    if (ump[num])
        return ump[num];
    ll ans = getPreQuad(num);
    ans = ans * ans % mod;
    for (ll i = 2, gx; i <= num; i = gx + 1)
    {
        gx = num / (num / i);
        ll fact = (getPreThird(gx) - getPreThird(i - 1) + mod) % mod;
        ans = (ans - fact * sieve(num / i) % mod + mod) % mod;
    }
    return ump[num] = (ans + mod) % mod;
}

signed main()
{
    scanf("%lld%lld", &mod, &n);
    inv2 = quick_pow(2, mod - 2), inv6 = quick_pow(6, mod - 2);
    phi_sieve();
    ll ans = 0;
    for (ll i = 1, gx; i <= n; i = gx + 1)
    {
        gx = n / (n / i);
        ll fact = getPreQuad(n / i);
        fact = fact * fact % mod;
        ll bfact = (sieve(gx) - sieve(i - 1) + mod) % mod;
        ans = (ans + bfact * fact % mod) % mod;
    }
    printf("%lld", (ans + mod) % mod);
    return 0;
}