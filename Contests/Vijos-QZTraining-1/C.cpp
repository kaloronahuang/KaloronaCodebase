// C.cpp
#include <bits/stdc++.h>
#define ll unsigned long long

using namespace std;

const ll mod = 7528443412579576937;

ll quick_mul(ll x, ll y)
{
    ll res = 0;
    if (x < y)
        swap(x, y);
    while (y)
    {
        if (y & 1LL)
            res = (res + x < mod) ? (res + x) : (res + x - mod);
        x = (x + x < mod) ? (x + x) : (x + x - mod);
        y >>= 1LL;
    }
    return res;
}

ll quick_pow(ll bas, ll tim)
{
    ll ans = 1;
    while (tim)
    {
        if (tim & 1LL)
            ans = quick_mul(ans, bas);
        bas = quick_mul(bas, bas);
        tim >>= 1LL;
    }
    return ans;
}

int main()
{
    ll n, k;
    scanf("%lld%lld", &n, &k), printf("%lld", quick_pow(2, 1LL * n * k));
    return 0;
}