// POJ2891.cpp
#include <cstdio>
#include <iostream>

using namespace std;

typedef long long ll;

int n;

ll fmul(ll a, ll b, ll cmod)
{
    ll ret = 0;
    for (; b; b >>= 1, a = (a + a) % cmod)
        if (b & 1)
            ret = (ret + a) % cmod;
    return ret;
}

ll exgcd(ll a, ll b, ll &x, ll &y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, x, y), tmp = x;
    x = y, y = tmp - (a / b) * y;
    return d;
}

int main()
{
    while (scanf("%d", &n) != EOF)
    {
        ll Mod, ans;
        bool flag = false;
        scanf("%lld%lld", &Mod, &ans);
        for (int i = 2; i <= n; i++)
        {
            ll a, b, d, x, y;
            scanf("%lld%lld", &a, &b);
            if (flag)
                continue;
            ll delta = ((b - ans) % a + a) % a;
            d = exgcd(Mod, a, x, y);
            if (delta % d != 0)
            {
                flag = true;
                continue;
            }
            x = fmul(x, delta / d, a);
            ans += x * Mod, Mod *= a / d, ans = (ans + Mod) % Mod;
        }
        if (flag)
            puts("-1");
        else
            printf("%lld\n", ans);
    }
    return 0;
}