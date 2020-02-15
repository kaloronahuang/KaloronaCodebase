// LOJ143.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

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
    ll n;
    while (scanf("%lld", &n) != EOF)
        puts(millerRabin(n) ? "Y" : "N");
    return 0;
}