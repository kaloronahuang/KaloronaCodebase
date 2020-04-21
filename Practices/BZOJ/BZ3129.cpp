// BZ3129.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MAX_N = 1e5 + 200;

ll T, mod, n, n1, n2, m, fac[MAX_N], primes[MAX_N], cnts[MAX_N], tot, ai[MAX_N];

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

void initialize(ll pbase, ll p)
{
    for (ll i = fac[0] = 1; i <= p; i++)
        if (i % pbase == 0)
            fac[i] = fac[i - 1];
        else
            fac[i] = 1LL * fac[i - 1] * i % p;
}

ll getFac(ll n_, ll p, ll pr)
{
    if (n_ == 0)
        return 1;
    ll seg = fpow(fac[pr], n_ / pr, pr), rem = n_ % pr;
    seg = 1LL * seg * fac[rem] % pr;
    return 1LL * getFac(n_ / p, p, pr) * seg % pr;
}

ll binomial(ll n_, ll k_, ll p, ll pr)
{
    if (n_ < k_)
        return 0;
    initialize(p, pr);
    ll x = getFac(n_, p, pr), y = getFac(n_ - k_, p, pr), z = getFac(k_, p, pr), cnt = 0;
    for (ll i = n_; i; i /= p)
        cnt += i / p;
    for (ll i = k_; i; i /= p)
        cnt -= i / p;
    for (ll i = n_ - k_; i; i /= p)
        cnt -= i / p;
    ll tmp = 1LL * x * getInv(y, pr) % pr * getInv(z, pr) % pr * fpow(p, cnt, pr) % pr;
    return tmp * (mod / pr) % mod * getInv(mod / pr, pr) % mod;
}

ll exlucas(ll n_, ll k_)
{
    ll ret = 0;
    for (ll i = 1; i <= tot; i++)
        ret = (0LL + ret + binomial(n_, k_, primes[i], cnts[i])) % mod;
    return ret;
}

int main()
{
    scanf("%lld%lld", &T, &mod);
    ll acc = mod;
    for (ll i = 2; 1LL * i * i <= acc; i++)
        if (acc % i == 0)
        {
            primes[++tot] = i, cnts[tot] = 1;
            while (acc % i == 0)
                cnts[tot] *= i, acc /= i;
        }
    if (acc != 1)
        primes[++tot] = acc, cnts[tot] = acc;
    while (T--)
    {
        scanf("%lld%lld%lld%lld", &n, &n1, &n2, &m);
        for (ll i = 1; i <= n1 + n2; i++)
            scanf("%lld", &ai[i]);
        ll rem = m - n;
        for (ll i = 1; i <= n2; i++)
            rem -= ai[n1 + i] - 1;

        ll ans = 0;
        for (ll stat = 0; stat < (1 << n1); stat++)
        {
            ll opt = 0, crem = rem;

            for (ll i = 0; i < n1; i++)
                if (stat & (1 << i))
                    opt++, crem -= ai[i + 1];
            ans = (0LL + ans + mod + 1LL * ((opt % 2) ? -1 : 1) * exlucas(crem + n - 1, n - 1) % mod) % mod;
        }
        printf("%lld\n", ans);
    }
    return 0;
}