// E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 220, mod = 998244353;

typedef long long ll;

ll D, q;
int fac[MAX_N], inv[MAX_N], fac_inv[MAX_N];

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

const int base[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

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

vector<ll> p;

void factorize(ll x)
{
    if (x == 1)
        return;
    if (millerRabin(x))
        return (void)(p.push_back(x));
    ll p = x;
    while (p == x)
        p = pollardRho(x);
    while (x % p == 0)
        x /= p;
    factorize(p), factorize(x);
}

int main()
{
    for (int i = fac[0] = 1; i < 200; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    inv[0] = inv[1] = 1, fac_inv[0] = fac_inv[1] = 1;
    for (int i = 2; i < 200; i++)
        inv[i] = 1LL * (mod - mod / i) * inv[mod % i] % mod, fac_inv[i] = 1LL * fac_inv[i - 1] * inv[i] % mod;
    scanf("%lld%lld", &D, &q);
    for (ll i = 2; 1LL * i * i <= D; i++)
    {
        if (D % i == 0)
            p.push_back(i);
        while (D % i == 0)
            D /= i;
    }
    if (D > 1)
        p.push_back(D);
    while (q--)
    {
        ll u, v;
        scanf("%lld%lld", &u, &v);
        ll d = gcd(u, v);
        ll u_i = u / d, v_i = v / d;
        int ans_1 = 1, ans_2 = 1;
        ll tot = 0;
        for (ll x : p)
            if (x <= u_i)
            {
                ll pans = 0;
                while (u_i % x == 0)
                    pans++, u_i /= x;
                tot += pans, ans_1 = 1LL * ans_1 * fac_inv[pans] % mod;
            }
            else
                break;
        ans_1 = 1LL * ans_1 * fac[tot] % mod;
        tot = 0;
        for (ll x : p)
            if (x <= v_i)
            {
                ll pans = 0;
                while (v_i % x == 0)
                    pans++, v_i /= x;
                tot += pans, ans_2 = 1LL * ans_2 * fac_inv[pans] % mod;
            }
            else
                break;
        ans_2 = 1LL * ans_2 * fac[tot] % mod;
        int ans = 1LL * ans_1 * ans_2 % mod;
        printf("%d\n", ans);
    }
    return 0;
}