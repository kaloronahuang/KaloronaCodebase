// LOJ6229.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const ll MAX_N = 1010000, mod = 1e9 + 7;

unordered_map<ll, ll> ump;
ll phi[MAX_N], tot, prime[MAX_N], inv2, inv6;
bool vis[MAX_N];

unsigned ll pow(unsigned ll num) { return num * num % mod; }

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

void preprocess()
{
    phi[1] = 1;
    for (ll i = 2; i < MAX_N; i++)
    {
        if (!vis[i])
            prime[++tot] = i, phi[i] = i - 1;
        for (ll j = 1; j <= tot && 1ll * i * prime[j] < MAX_N; j++)
        {
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0)
            {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
            phi[i * prime[j]] = phi[i] * phi[prime[j]];
        }
    }
    for (ll i = 1; i < MAX_N; i++)
        phi[i] = (phi[i - 1] + phi[i] * i % mod * i % mod) % mod;
}

ll getPre2(ll n)
{
    n %= mod;
    return inv6 * n % mod * (n + 1) % mod * (2 * n + 1) % mod;
}

ll sieve(ll n)
{
    if (n < MAX_N)
        return phi[n];
    if (ump[n])
        return ump[n];
    ll ans = n * (n + 1) / 2 % mod;
    ans = ans * ans % mod;
    for (ll i = 2, gx; i <= n; i = gx + 1)
    {
        gx = (n / (n / i));
        ans = (ans - (getPre2(gx) - getPre2(i - 1) + mod) % mod * sieve(n / i) % mod + mod) % mod;
    }
    return ump[n] = ans;
}

int main()
{
    ll n;
    preprocess();
    scanf("%lld", &n);
    inv2 = quick_pow(2, mod - 2), inv6 = quick_pow(6, mod - 2);
    ll ans = 0, last = 0, curt;
    for (ll i = 1, gx; i <= n; i = gx + 1)
    {
        gx = (n / (n / i));
        curt = sieve(gx);
        ans = (ans + (curt - last) * (n / i));
        last = curt;
    }
    ans = (ans + n) % mod * inv2 % mod;
    printf("%lld", (ans + mod) % mod);
    return 0;
}