// CH3301.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll gcd(ll a, ll b) { return (b == 0) ? a : gcd(b, a % b); }

ll exgcd(ll a, ll b, ll &x, ll &y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, x, y);
    ll z = x;
    x = y, y = z - y * (a / b);
    return d;
}

int main()
{
    ll a, b;
    scanf("%lld%lld", &a, &b);
    ll x, y, d = exgcd(a, b, x, y), ex = gcd(a, b);
    while (x < 0)
        x += b;
    printf("%lld", x % b);
    return 0;
}