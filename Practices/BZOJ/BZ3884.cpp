// BZ3884.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll mod;

ll fpow(ll bas, ll tim, ll cmod)
{
    ll ret = 1;
    while (tim)
    {
        if (tim & 1)
            ret = 1LL * ret * bas % cmod;
        bas = 1LL * bas * bas % cmod;
        tim >>= 1;
    }
    return ret;
}

ll phi(ll x)
{
    ll ret = x, base = x;
    for (ll i = 2; i * i <= base; i++)
        if (base % i == 0)
        {
            ret = ret / i * (i - 1);
            while (base % i == 0)
                base /= i;
        }
    if (base > 1)
        ret = ret / base * (base - 1);
    return ret;
}

ll f(ll x)
{
    if (x == 1)
        return 0;
    ll phi_val = phi(x);
    return fpow(2, f(phi_val) + phi_val, x);
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
        scanf("%d", &mod), printf("%d\n", f(mod));
    return 0;
}