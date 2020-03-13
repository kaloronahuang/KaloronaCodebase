// LOJ2045.cpp
#include <bits/stdc++.h>

using namespace std;

const int base[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

typedef long long ll;

ll ans;

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

bool millerRabin(ll curt)
{
    for (auto cbase : base)
    {
        if (cbase == curt)
            return true;
        else if (cbase > curt)
            return false;
        ll x = fpow(cbase, curt - 1, curt), idx = curt - 1;
        if (x != 1)
            return false;
        while (x == 1 && idx % 2 == 0)
        {
            idx /= 2, x = fpow(cbase, idx, curt);
            if (x != 1 && x != curt - 1)
                return false;
        }
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

void factorize(ll x)
{
    if (x == 1 || x <= ans || ans > 1)
        return;
    if (millerRabin(x))
        return (void)(ans = max(ans, x));
    ll p = x;
    while (p == x)
        p = pollardRho(x);
    while (x % p == 0)
        x /= p;
    factorize(p), factorize(x);
}

ll exgcd(ll a, ll b, ll &x, ll &y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

int main()
{
    ll e, N, c, d;
    scanf("%lld%lld%lld", &e, &N, &c);
    factorize(N);
    ll p = ans, q = N / p, r = (p - 1) * (q - 1), tmp;
    exgcd(e, r, d, tmp);
    if (d < 0)
        d += ((r - d + 1) / r) * r;
    printf("%lld %lld\n", d, fpow(c, d, N));
    return 0;
}