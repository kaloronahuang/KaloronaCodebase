// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 210, mod = 1000007, primes[] = {0, 2, 3, 5, 7, 13, 17, 19, 29, 31, 41, 89, 97};

typedef long long ll;

int n, typ;
ll ai[MAX_N], table[MAX_N], loop[mod + 10], ans;

void fileIO()
{
    freopen("hash.in", "r", stdin);
    freopen("hash.out", "w", stdout);
}

ll multiply(ll x, ll y, ll cmod)
{
    long double tmp = (long double)x / cmod * y;
    return (x * y - ll(tmp) * cmod + cmod) % cmod;
}

ll quick_pow(ll bas, ll tim, ll cmod)
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

bool millerRabin(ll p, ll x)
{
    ll idx = quick_pow(x, p - 1, p);
    if (idx != 1)
        return false;
    ll phi = p - 1;
    while ((phi & 1) == 0)
    {
        ll tmp = quick_pow(x, phi / 2, p);
        if (tmp != p - 1 && tmp != 1)
            return false;
        if (tmp == p - 1)
            return true;
        phi /= 2;
    }
    return true;
}

bool isPrime(ll x)
{
    for (int i = 1; i <= 12; i++)
        if (x != primes[i] && !millerRabin(x, primes[i]))
            return false;
    return true;
}

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

ll pollardRho(ll cmod)
{
    while (true)
    {
        ll x = rand() % cmod, parameter = rand() % cmod;
        ll y = x, checker = 1, l = 0, r = 1;
        while (true)
        {
            x = (multiply(x, x, cmod) + parameter) % cmod;
            checker = multiply(checker, abs(x - y), cmod);
            // rho-loop;
            if (checker == 0 || x == y)
                break;
            if (l % 127 == 0 || l == r)
            {
                ll factor = gcd(checker, cmod);
                if (factor > 1)
                    return factor;
                if (l == r)
                    y = x, r = (r << 1);
            }
            l++;
        }
    }
}

ll addFish(ll x, ll len, ll upper)
{
    ll tot = 0, y = x % len;
    while (true)
    {
        bool flag = true;
        for (int i = 1; i < upper; i++)
            if (table[i] == y && ai[i] != x)
            {
                flag = false;
                break;
            }
        if (flag)
            break;
        else
            y = (y + 1) % len, tot++;
    }
    table[upper] = y;
    return tot;
}

ll check(ll threshold)
{
    ll ret = 0;
    for (int i = 1; i <= n; i++)
        ret += addFish(ai[i], threshold, i);
    return ret;
}

bool checkHash(ll x)
{
    ll y = x % mod;
    while (loop[y] != 0)
    {
        if (loop[y] == x)
            return true;
        y = (y + 1) % mod;
    }
    loop[y] = x;
    return false;
}

void update(ll x)
{
    if (checkHash(x))
        return;
    if (x <= 1LL * n * n)
        return;
    if (isPrime(x))
    {
        ans = max(ans, check(x));
        return;
    }
    ll factor = pollardRho(x);
    while (x % factor == 0)
        x /= factor;
    update(factor), update(x);
}

int main()
{
    fileIO();
    scanf("%d%d", &typ, &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &ai[i]);
    for (int i = n; i <= 1LL * n * n; i++)
        ans = max(ans, check(i));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j < i; j++)
        {
            ll diff = llabs(ai[i] - ai[j]);
            if (diff == 1)
                continue;
            update(diff);
        }
    printf("%lld\n", ans);
    return 0;
}