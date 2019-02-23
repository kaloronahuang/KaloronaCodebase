// POJ1061.cpp
#include <cstdio>
#include <iostream>
#define ll long long
using namespace std;
ll exgcd(ll a, ll b, ll &x, ll &y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, x, y);
    ll z = x;
    x = y, y = z - (a / b) * y;
    return d;
}
ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }
int main()
{
    ll x, y, m, n, L;
    scanf("%lld%lld%lld%lld%lld", &x, &y, &m, &n, &L);
    if (m > n)
        swap(n, m), swap(x, y);
    ll a = n - m, t, s;
    ll sol = exgcd(a, L, t, s);
    if ((x - y) % sol == 0)
    {
        t = t * (x - y) / sol;
        while (t < 0)
            t += L;
        t %= L;
        printf("%lld\n", t);
    }
    else
        puts("Impossible");
    return 0;
}