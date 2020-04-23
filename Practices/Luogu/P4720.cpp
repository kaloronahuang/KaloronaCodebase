// P4720.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

typedef long long ll;

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

ll getInv(ll u, ll p)
{
    ll x, y, d = exgcd(u, p, x, y);
    return d == 1 ? (0LL + x % p + p) % p : -1;
}

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

ll fac(ll x, ll pbase, ll pk)
{
    if (x == 0)
        return 1;
    ll ret = 1;
    for (ll i = 1; i <= pk; i++)
        if (i % pbase != 0)
            ret = ret * i % pk;
    ret = fpow(ret, x / pk, pk);
    for (ll i = 1; i <= x % pk; i++)
        if (i % pbase != 0)
            ret = ret * i % pk;
    return ret * fac(x / pbase, pbase, pk) % pk;
}

ll binomial(ll n_, ll m_, ll pbase, ll pk)
{
    if (n_ < m_)
        return 0;
    ll x = fac(n_, pbase, pk), y = fac(m_, pbase, pk), z = fac(n_ - m_, pbase, pk), cnt = 0;
    for (ll i = n_; i; i /= pbase)
        cnt += i / pbase;
    for (ll i = m_; i; i /= pbase)
        cnt -= i / pbase;
    for (ll i = n_ - m_; i; i /= pbase)
        cnt -= i / pbase;
    return 1LL * x * getInv(y, pk) % pk * getInv(z, pk) % pk * fpow(pbase, cnt, pk) % pk;
}

ll n, m, mod;

ll solve(ll pbase, ll pk) { return binomial(n, m, pbase, pk) * (mod / pk) % mod * getInv(mod / pk, pk) % mod; }

int main()
{
    scanf("%lld%lld%lld", &n, &m, &mod);
    ll acc = mod, ans = 0;
    for (int i = 2; 1LL * i * i <= acc; i++)
        if (acc % i == 0)
        {
            ll pk = 1;
            while (acc % i == 0)
                pk *= i, acc /= i;
            ans = (0LL + ans + solve(i, pk)) % mod;
        }
    if (acc != 1)
        ans = (0LL + ans + solve(acc, acc)) % mod;
    printf("%lld\n", ans);
    return 0;
}