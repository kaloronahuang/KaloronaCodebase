// BZ2142.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

typedef long long ll;

ll n, m, mod, wi[MAX_N], primes[MAX_N], cnts[MAX_N], tot, fac[MAX_N];

ll fpow(ll bas, ll tim, ll cmod)
{
    ll ret = 1;
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
    ll d = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return d;
}

ll getInv(ll u, ll cmod)
{
    ll x, y, d = exgcd(u, cmod, x, y);
    return d == 1 ? (x + cmod) % cmod : -1;
}

void initialize(ll p, ll pr)
{
    for (ll i = fac[0] = 1; i <= pr; i++)
        if (i % p)
            fac[i] = 1LL * fac[i - 1] * i % pr;
        else
            fac[i] = fac[i - 1];
}

ll getFac(ll upper, ll p, ll pr)
{
    if (upper == 0)
        return 1;
    ll seg = fpow(fac[pr], upper / pr, pr), rem = upper % pr;
    seg = 1LL * seg * fac[rem] % pr;
    return 1LL * getFac(upper / p, p, pr) * seg % pr;
}

ll binomial(ll upper, ll choose, ll p, ll pr)
{
    if (upper < choose)
        return 0;
    initialize(p, pr);
    ll x = getFac(upper, p, pr), y = getFac(choose, p, pr), z = getFac(upper - choose, p, pr), cnt = 0;
    for (ll i = upper; i; i /= p)
        cnt += i / p;
    for (ll i = upper - choose; i; i /= p)
        cnt -= i / p;
    for (ll i = choose; i; i /= p)
        cnt -= i / p;
    ll tmp = 1LL * x * getInv(y, pr) % pr * getInv(z, pr) % pr * fpow(p, cnt, pr) % mod;
    return tmp * (mod / pr) % mod * getInv(mod / pr, pr) % mod;
}

ll exlucas(ll upper, ll choose)
{
    ll ret = 0;
    for (int i = 1; i <= tot; i++)
        ret = (0LL + ret + binomial(upper, choose, primes[i], cnts[i])) % mod;
    return ret;
}

int main()
{
    scanf("%lld%lld%lld", &mod, &n, &m);
    ll upper = 0;
    for (int i = 1; i <= m; i++)
        scanf("%lld", &wi[i]), upper += wi[i];
    if (upper > n)
        puts("Impossible"), exit(0);
    ll acc = mod;
    for (int i = 2; 1LL * i * i <= acc; i++)
        if (acc % i == 0)
        {
            ll p = i, pr = 1;
            while (acc % i == 0)
                pr *= i, acc /= i;
            primes[++tot] = p, cnts[tot] = pr;
        }
    if (acc > 1)
        primes[++tot] = acc, cnts[tot] = acc;
    ll ans = 1, sum = n;
    for (int i = 1; i <= m; i++)
        ans = 1LL * ans * exlucas(sum, wi[i]) % mod, sum -= wi[i];
    printf("%lld\n", ans);
    return 0;
}