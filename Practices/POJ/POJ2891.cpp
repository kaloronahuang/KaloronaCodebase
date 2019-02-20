// POJ2891.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 1e6 + 200;
ll exgcd(ll a, ll b, ll &x, ll &y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, x, y), z = x;
    x = y, y = z - (a / b) * y;
    return d;
}
int main()
{
    ll n;
    while (~scanf("%lld", &n))
    {
        ll x, y, a, b, k;
        scanf("%lld%lld", &a, &b);
        ll lcm = a, ans = b;
        bool flag = true;
        n--;
        while (n--)
        {
            scanf("%lld%lld", &a, &b);
            b = (b - ans % a + a) % a;
            ll d = exgcd(lcm, a, x, y);
            if (b % d)
                flag = false;
            else
                k = x * (b / d);
            ans += k * lcm;
            lcm = lcm / d * a;
            ans = (ans % lcm + lcm) % lcm;
        }
        if (flag)
            printf("%lld\n", ans);
        else
            puts("-1");
    }
    return 0;
}