// P4607.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll multiply(ll x, ll y, ll cmod)
{
    ll tmp = (x * y - (ll)((long double)x / cmod * y + 1.0e-8) * cmod) % cmod;
    return tmp < 0 ? tmp + cmod : tmp;
}

ll fpow(ll bas, ll tim, ll cmod)
{
    ll ret = 1;
    while (tim)
    {
        if (tim & 1)
            ret = multiply(ret, bas, cmod);
        bas = multiply(bas, bas, cmod);
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
    for (ll test_case = 5; test_case >= 0; test_case--)
    {
        ll tnum = fpow(unifiedRand(1, n - 1), p, n), cur = tnum;
        for (ll i = 1; i <= m; i++)
        {
            cur = multiply(cur, cur, n);
            if (cur == 1 && tnum != 1 && tnum != n - 1)
                return false;
            tnum = cur;
        }
        if (cur != 1)
            return false;
    }
    return true;
}

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

ll pollardRho(ll n)
{
    if (n % 2 == 0)
        return 2;
    if (n % 3 == 0)
        return 3;
    ll x = 0, y = 0, c = rand() % (n - 1) + 1, bas = 1, unit = (1 << 7), factor = 1;
    for (ll step = 2;; step <<= 1, y = x, bas = 1)
    {
        for (ll i = 1; i <= step; i++)
        {
            x = (multiply(x, x, n) + c) % n;
            bas = multiply(bas, abs(x - y), n);
            if (i % unit == 0)
            {
                factor = gcd(bas, n);
                if (factor > 1)
                    return factor;
            }
        }
        if (factor > 1 || ((factor = gcd(bas, n)) > 1))
            return factor;
    }
    return n;
}

ll T, n, k, p;
vector<ll> primes;

void factorize(ll x)
{
    if (x == 1)
        return;
    if (millerRabin(x))
        return (void)(primes.push_back(x));
    ll p = x;
    while (p == x)
        p = pollardRho(x);
    while (x % p == 0)
        x /= p;
    factorize(p), factorize(x);
}

ll fpow(ll bas, ll tim)
{
    ll ret = 1;
    bas %= p;
    while (tim)
    {
        if (tim & 1)
            ret = 1LL * ret * bas % p;
        bas = 1LL * bas * bas % p;
        tim >>= 1;
    }
    return ret;
}

vector<ll> box;
unordered_map<ll, ll> ump;

void dfs(ll pos, ll acc, ll acct)
{
    if (pos == primes.size())
        return (void)(box.push_back(acc), ump[acc] = acct);
    dfs(pos + 1, acc, acct), acct = 1LL * acct * ((1LL + p - primes[pos] % p) % p) % p;
    for (ll idx = primes[pos];; idx *= primes[pos])
    {
        dfs(pos + 1, 1LL * idx * acc, acct);
        if ((n / idx) % primes[pos] != 0)
            break;
    }
}

int main()
{
    scanf("%lld", &T), srand(time(NULL));
    while (T--)
    {
        scanf("%lld%lld%lld", &n, &k, &p), primes.clear(), box.clear(), ump.clear(), k %= p;
        factorize(n), sort(primes.begin(), primes.end()), primes.erase(unique(primes.begin(), primes.end()), primes.end()), dfs(0, 1, 1);
        ll ret = 0;
        for (auto u : box)
        {
            ll d1 = u;
            if (d1 % 2 == 1 && (n / d1) % 2 == 0)
                continue;
            ret = (0LL + ret + 1LL * (d1 % 2 == 0 ? d1 / 2 : d1) % p * fpow(k, (d1 + 1) >> 1, p) % p * ump[n / u] % p) % p;
            // puts("FUCK");
        }
        printf("%lld\n", ret);
    }
    return 0;
}