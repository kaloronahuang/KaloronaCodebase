// P3935.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int mod = 998244353;

ll calc(ll n)
{
    ll res = 0;
    for (ll x = 1, gx; x <= n; x = gx + 1)
        gx = n / (n / x), res = (1LL * res + 1LL * (gx - x + 1) * (n / x) % mod) % mod;
    return res;
}

int main()
{
    ll l, r;
    scanf("%lld%lld", &l, &r), printf("%lld", (0LL + calc(r) - calc(l - 1) + mod) % mod);
    return 0;
}