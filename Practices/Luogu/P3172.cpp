// P3172.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAX_N = 1e6 + 2000, mod = 1000000007, INF = 0x3f3f3f3f;
ll mu[MAX_N], n, k, l, r, prime[MAX_N], tot, inv2;
bool vis[MAX_N];
unordered_map<ll, ll> ump;

void preprocess()
{
    mu[1] = 1;
    for (ll i = 2; i < MAX_N; i++)
    {
        if (!vis[i])
            prime[++tot] = i, mu[i] = -1;
        for (ll j = 1; j <= tot && prime[j] * i < MAX_N; j++)
        {
            vis[prime[j] * i] = true;
            if (i % prime[j] == 0)
            {
                mu[i * prime[j]] = 0;
                break;
            }
            mu[i * prime[j]] = -mu[i];
        }
    }
    for (int i = 2; i < MAX_N; i++)
        mu[i] += mu[i - 1];
}

ll quick_pow(ll bas, ll tim)
{
    ll ans = 1;
    while (tim)
    {
        if (tim & 1)
            ans = bas * ans % mod;
        bas = bas * bas % mod;
        tim >>= 1;
    }
    return ans;
}

ll sieve(ll num)
{
    if (num < MAX_N)
        return mu[num];
    if (ump.count(num))
        return ump[num];
    ll ans = 1;
    for (ll i = 2, gx; i <= num; i = gx + 1)
    {
        gx = (num / (num / i));
        ans = (ans - (gx - i + 1) % mod * sieve(num / i) % mod + mod) % mod;
    }
    return ump[num] = ans;
}

int main()
{
    scanf("%lld%lld%lld%lld", &n, &k, &l, &r);
    l = (l - 1) / k, r /= k, inv2 = quick_pow(2, mod - 2);
    preprocess();
    ll ans = 0;
    for (ll i = 1, gx; i <= r; i = gx + 1)
    {
        gx = min(l / i ? l / (l / i) : INF, r / (r / i));
        ans = (ans + (sieve(gx) - sieve(i - 1) + mod) % mod * quick_pow(r / i - l / i, n) % mod) % mod;
    }
    printf("%lld", (ans + mod) % mod);
    return 0;
}