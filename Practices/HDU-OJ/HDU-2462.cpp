// HDU-2462.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 2e5 + 200;
ll n;
ll mul(ll a, ll b, ll mod)
{
    ll tmp = 0;
    while (b)
    {
        if (b & 1)
            tmp = (tmp + a) % mod;
        a = (a << 1) % mod;
        b >>= 1;
    }
    return tmp;
}
ll quick_power(ll base, ll tim, ll mod)
{
    ll tmp = 1 % mod;
    base %= mod;
    while (tim)
    {
        if (tim & 1)
            tmp = mul(tmp, base, mod);
        base = mul(base, base, mod);
        tim >>= 1;
    }
    return tmp;
}
ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }
ll phi(ll num)
{
    ll ans = num;
    for (int i = 2; i * i <= num; i++)
        if (num % i == 0)
        {
            ans = ans / i * (i - 1);
            while (num % i == 0)
                num /= i;
        }
    if (num > 1)
        ans = ans / num * (num - 1);
    return ans;
}
ll number()
{
    ll d = gcd(n, 8), k = 9 * n / d;
    if (gcd(k, 10) != 1)
        return 0;
    ll p = phi(k);
    for (ll i = 1; i * i <= p; i++)
        if (p % i == 0 && quick_power(10, i, k) == 1)
            return i;
    for (ll i = sqrt(p) - 1; i; i--)
        if (p % i == 0 && quick_power(10, p / i, k) == 1)
            return p / i;
    return 0;
}
int main()
{
    int idx = 1;
    while (scanf("%lld", &n) && n != 0)
        printf("Case %d: %lld\n", idx++, number());
    return 0;
}