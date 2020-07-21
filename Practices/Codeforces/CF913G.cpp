// CF913G.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int T;

ll fmul(ll a, ll b, ll mod)
{
    ll ret = 0;
    while (b)
    {
        if (b & 1)
            ret = (0LL + ret + a) % mod;
        a = (0LL + a + a) % mod;
        b >>= 1;
    }
    return ret;
}

ll fpow(ll bas, ll tim, ll mod)
{
    ll ret = 1;
    while (tim)
    {
        if (tim & 1LL)
            ret = fmul(ret, bas, mod);
        bas = fmul(bas, bas, mod);
        tim >>= 1;
    }
    return ret;
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        ll ai, acc, n = 0, mbas = 1;
        scanf("%lld", &ai), acc = ai;
        while (acc)
            n++, acc /= 10;
        for (int m = 0;; ai *= 10, mbas *= 10, m++)
        {
            ll cmod = 1LL << (n + m);
            // ll bi = (-ai) & (cmod - 1);
            ll bi = ((cmod - 1LL * ai) % cmod + cmod) % cmod;
            if ((ai + bi) % 5 == 0)
                bi += cmod;
            if (bi >= mbas)
                continue;
            // x = 2^k,
            ll x = ai + bi, y = x >> (n + m);
            ll cidx = 0, phi = 4, bas = 5;
            for (int i = 0; i < 4; i++)
                if (fpow(2, i, 5) == y % 5)
                    cidx = i;
            // keep going;
            for (ll i = 2; i <= n + m; i++)
            {
                bas *= 5;
                for (int j = 0; j < 5; j++)
                    if (fpow(2, cidx + 1LL * j * phi, bas) == y % bas)
                    {
                        cidx += 1LL * j * phi;
                        break;
                    }
                phi *= 5;
            }
            printf("%lld\n", cidx + n + m);
            break;
        }
    }
    return 0;
}