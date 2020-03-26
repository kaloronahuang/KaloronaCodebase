// UOJ42.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll T, n, r;
double spart;

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

ll calc(ll a, ll b, ll c, ll n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return (a * spart + b) / c;
    ll d = gcd(gcd(a, b), c);
    a /= d, b /= d, c /= d;
    ll verdict = (a * spart + b) / c;
    if (verdict == 0)
    {
        // transform the axis system;
        ll rect_area = ll((a * spart + b) / c * n) * n;
        return rect_area - calc(a * c, -c * b, a * a * r - b * b, (a * spart + b) / c * n);
    }
    else
        return calc(a, b - c * verdict, c, n)  + verdict * n * (n + 1) / 2;
}

int main()
{
    scanf("%lld", &T);
    while (T--)
    {
        scanf("%lld%lld", &n, &r);
        spart = sqrt(r);
        if (ll(spart) * ll(spart) == r)
        {
            // calc;
            if (ll(spart) % 2 == 0)
                printf("%lld\n", n);
            else
                printf("%lld\n", n - 2 * ((n + 1) >> 1));
            continue;
        }
        printf("%lld\n", n - 2LL * calc(1, 0, 1, n) + 4LL * calc(1, 0, 2, n));
    }
    return 0;
}