// exLucas.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

typedef long long ll;

ll n, m, mod, fac[MAX_N];

ll fpow(ll bas, ll tim, ll cmod)
{
    ll ret = 1;
    bas %= cmod;
    while (tim)
    {
        if (tim & 1)
            ret = 1LL * ret * bas % cmod;
        bas = 1LL * bas * bas % cmod;
        tim >>= 1;
    }
    return ret;
}

ll exgcd(ll a, ll b, ll &x, ll &y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, x, y), tmp = x;
    x = y, y = tmp - (a / b) * y;
    return d;
}

ll getInv(ll u, ll cmod)
{
    ll x, y;
    exgcd(u, cmod, x, y);
    return (0LL + x % cmod + cmod) % cmod;
}

ll factorial(ll upper, ll p, ll pr)
{
    if (upper == 0)
        return 1;
    ll ret = 1LL * fpow(fac[pr], upper / pr, pr) * fac[upper % pr] % pr;
    return 1LL * ret * factorial(upper / p, p, pr) % pr;
}

ll binomial(ll upper, ll k, ll p, ll pr)
{
    if (upper < k)
        return 0;
    ll p1 = factorial(upper, p, pr), p2 = factorial(k, p, pr), p3 = factorial(upper - k, p, pr), rem = 0;
    for (ll i = upper; i; i /= p)
        rem += i / p;
    for (ll i = k; i; i /= p)
        rem -= i / p;
    for (ll i = upper - k; i; i /= p)
        rem -= i / p;
    return 1LL * p1 * getInv(p2, pr) % pr * getInv(p3, pr) % pr * fpow(p, rem, pr) % pr;
}

ll exLucas(ll upper, ll k, ll p, ll pr)
{
    for (ll i = fac[0] = 1; i <= pr; i++)
        if (i % p == 0)
            fac[i] = fac[i - 1];
        else
            fac[i] = 1LL * fac[i - 1] * i % pr;
    return 1LL * binomial(upper, k, p, pr) * (mod / pr) % mod * getInv(mod / pr, pr) % mod;
}

int main()
{
    scanf("%lld%lld%lld", &n, &m, &mod);
    ll acc = mod, ans = 0;
    for (int i = 2; 1LL * i * i <= acc; i++)
        if (acc % i == 0)
        {
            ll p = i, pr = 1;
            while (acc % i == 0)
                pr *= i, acc /= i;
            ans = (0LL + ans + exLucas(n, m, p, pr)) % mod;
        }
    if (acc > 1)
        ans = (0LL + ans + exLucas(n, m, acc, acc)) % mod;
    printf("%lld\n", ans);
    return 0;
}