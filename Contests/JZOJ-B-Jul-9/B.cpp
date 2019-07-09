// B.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int limit = 1e5, mod = 1000000007;

ll x, ans;

ll quick_pow(ll bas, ll tim)
{
    ll ans = 1;
    while (tim)
    {
        if (tim & 1)
            ans = ans * bas % mod;
        bas = bas * bas % mod;
        tim >>= 1;
    }
    return ans;
}

int main()
{
    scanf("%lld", &x);
    ll remain = mod, inv4 = quick_pow(4, mod - 2), inv8 = quick_pow(8, mod - 2);

    while (remain != x)
    {
        bool flag = false;
        ll re = remain;
        for (int tim = 1; tim <= 2; tim++)
        {
            re = (re - 3 + mod) % mod * inv4 % mod;
            if (re == x)
            {
                ans += tim, flag = true;
                break;
            }
        }
        if (flag)
            break;
        remain = (remain - 7 + mod) % mod * inv8 % mod;
        ans++;
    }
    printf("%lld", ans);
    return 0;
}