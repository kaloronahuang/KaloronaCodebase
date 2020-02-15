// P3653.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

typedef long long ll;
typedef long double ld;

ll primes[MAX_N], ptot, mu[MAX_N], fac[MAX_N], l, r;
bool vis[MAX_N];

void sieve()
{
    for (int i = 2; i < MAX_N; i++)
    {
        if (!vis[i])
            primes[++ptot] = i;
        for (int j = 1; j <= ptot && 1LL * primes[j] * i < MAX_N; j++)
        {
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
}

ll quick_mul(ll A, ll B, ll mod)
{
    ll ret = A * B - ((ll)((ld)A / mod * B + 0.5)) * mod;
    return ret < 0 ? ret + mod : ret;
}

ll quick_pow(ll bas, ll tim, ll mod)
{
    ll ret = 1;
    while (tim)
    {
        if (tim & 1LL)
            ret = quick_mul(ret, bas, mod);
        bas = quick_mul(bas, bas, mod);
        tim >>= 1;
    }
    return ret;
}

ll unifiedRand(ll l, ll r)
{
    static mt19937_64 seed(time(NULL) * (ll)(new int));
    return uniform_int_distribution<ll>(l, r)(seed);
}

bool millerRabin(ll n)
{
    if (n == 2)
        return true;
    if (n == 1 || n == 0)
        return false;
    ll p = n - 1, m = 0;
    while (~p & 1)
        p >>= 1, m++;
    for (int test_case = 5; test_case >= 0; test_case--)
    {
        ll tnum = quick_pow(unifiedRand(1, n - 1), p, n), cur = tnum;
        for (int i = 1; i <= m; i++)
        {
            cur = quick_mul(cur, cur, n);
            if (cur == 1 && tnum != 1 && tnum != n - 1)
                return false;
            tnum = cur;
        }
        if (cur != 1)
            return false;
    }
    return true;
}

int main()
{
    sieve(), scanf("%lld%lld", &l, &r);
    for (ll i = l; i <= r; i++)
        mu[i - l] = 1, fac[i - l] = i;
    for (int i = 1; i <= ptot && 1LL * primes[i] * primes[i] <= r; i++)
    {
        ll p = primes[i];
        for (ll x = (p - l % p) % p; x <= r - l; x += p)
        {
            int cnt = 0;
            while (fac[x] % p == 0)
                cnt++, fac[x] /= p;
            if (cnt > 1)
                mu[x] = 0;
            else
                mu[x] = -mu[x];
        }
    }
    ll ans = 0;
    for (int i = 0; i <= r - l; i++)
    {
        if (fac[i] != 1)
        {
            ll rem = fac[i], sq = sqrt(rem);
            if (sq * sq == rem)
                mu[i] = 0;
            else if (millerRabin(rem))
                mu[i] = -mu[i];
        }
        ans += mu[i];
    }
    printf("%lld\n", ans);
    return 0;
}