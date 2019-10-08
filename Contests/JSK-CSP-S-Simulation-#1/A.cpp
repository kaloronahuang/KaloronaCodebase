// A.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

ll n, m;

ll mul(ll a, ll b, ll mod)
{
    ll ans = 0;
    for (; b; b >>= 1, a = (a + a) % mod)
        if (b & 1)
            ans = (ans + a) % mod;
    return ans;
}

ll quick_pow(ll bas, ll tim, ll mod)
{
    ll ans = 1;
    while (tim)
    {
        if (tim & 1)
            ans = mul(ans, bas, mod);
        bas = mul(bas, bas, mod);
        tim >>= 1;
    }
    return ans;
}

int main()
{
    // ans = \sum_{}
    scanf("%lld%lld", &n, &m);
    if (n == 2)
        printf("%lld", 1 % m), exit(0);
    ll ans1 = mul(quick_pow(2, n - 1, m), n - 1, m);
    ll ans2 = quick_pow(2, n - 1, m) - 1;
    ll ans = ans1 - ans2;
    while (ans < 0)
        ans += m;
    ans %= m;
    printf("%lld", ans);
    return 0;
}