// CF1338C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

typedef long long ll;

int T;
ll n;

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%lld", &n);
        ll x = n / 3, y = n % 3;
        if (y == 0)
            x--, y = 3;
        if (x == 0)
        {
            printf("%lld\n", y);
            continue;
        }
        ll a = 0, b = 0, d = 0;
        while (a <= x)
            a += (1LL << d), d += 2;
        ll pos = x - (a - (1LL << (d - 2)));
        a = (1LL << (d - 2)) + (x - (a - (1LL << (d - 2))));
        if (y == 1)
            printf("%lld\n", a);
        else
        {
            b = 1LL << (d - 1);
            for (int i = 0; i < d - 2; i += 2)
            {
                ll res = pos % (1LL << (i + 2));
                if (res < (1LL << i))
                    continue;
                else if (res < (1LL << (i + 1)))
                    b |= 2LL << i;
                else if (res < (1LL << i) + (1LL << (i + 1)))
                    b |= 3LL << i;
                else
                    b |= 1LL << i;
            }
            printf("%lld\n", (y == 2) ? b : (a ^ b));
        }
    }
    return 0;
}