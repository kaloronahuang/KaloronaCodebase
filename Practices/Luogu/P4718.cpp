// P4718.cpp
#include <bits/stdc++.h>
#define ll __int128
using namespace std;
const ll bases[6] = {2, 3, 7, 11, 61, 24251};
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll quick_power(ll base, ll tim, ll p)
{
    ll tmp = 1;
    while (tim)
    {
        if (tim & 1)
            tmp = base * tmp % p;
        base = base * tmp % p;
        tim >>= 1;
    }
    return tmp;
}
ll millerRabin(ll p)
{
    ll x = p - 1, t = 0;
    while (!(x & 1))
        x >>= 1, t++;
    for (int i = 0, j; i < 4; i++)
    {
        if (p == bases[i])
            return true;
        ll bas = bases[i], unit = quick_power(bases[i], x, p);
        if (unit == 1 || unit == p - 1)
            continue;
        for (j = 0; j < t; j++)
        {
            unit = unit * unit % p;
            if (unit == p - 1)
                break;
        }
        if (j >= t)
            return false;
    }
    return true;
}
ll pollardRho(ll n, ll c)
{
    ll i = 1, k = 2, x = rand() % (n - 1) + 1, y = x;
    while (true)
    {
        i++, x = (x * x % n + c) % n;
        ll d = gcd(y - x, n);
        if (d > 1 && d < n)
            return d;
        if (y == x)
            return n;
        if (i == k)
            y = x, k <<= 1;
    }
}
ll pr = 0;
void find(ll n, ll c)
{
    if (n == 1 || n <= pr)
        return;
    if (millerRabin(n))
    {
        pr = max(pr, n);
        return;
    }
    ll p = n;
    while (p == n)
        p = pollardRho(n, c--);
    while (n % p == 0)
        n /= p;
    find(p, c), find(n, c);
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        long long n;
        scanf("%lld", &n);
        ll inp = (ll)n;
        find(inp, 19260817);
        long long ans = pr;
        if (ans == n)
            printf("Prime\n");
        else
            printf("%lld\n", ans);
        pr = 0;
    }
    return 0;
}