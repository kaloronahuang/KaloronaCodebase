// gcd.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, mod = 1e9 + 7;

typedef long long ll;
typedef pair<ll, ll> pll;

int n, q;
ll f[MAX_N];
vector<pll> g[MAX_N];

ll calc(pll u, ll x, ll y)
{
    ll ret = 0;
    if (x >= u.second && y >= u.first + u.second)
        ret = (0LL + ret + (y - u.first) / u.second) % mod;
    if (y >= u.second && x >= u.first + u.second)
        ret = (0LL + ret + (x - u.first) / u.second) % mod;
    return ret;
}

int main()
{
    f[0] = f[n = 1] = 1;
    while (f[n] <= 4e18)
        n++, f[n] = f[n - 1] + f[n - 2];
    for (int i = 1; i <= 2; i++)
        g[0].push_back(make_pair(0, i));
    for (int i = 0; i < n - 2; i++)
        for (auto u : g[i])
        {
            ll x = u.first, y = u.second;
            x += y;
            while (x <= f[i + 3] + f[i])
            {
                if (x > y)
                    g[i + 1].push_back(make_pair(y, x));
                x += y;
            }
        }
    scanf("%d", &q);
    while (q--)
    {
        ll x, y;
        scanf("%lld%lld", &x, &y);
        if (x < y)
            swap(x, y);
        ll ans = 1, sum = 0;
        for (; f[ans + 2] <= x && f[ans + 1] <= y; ans++)
            ;
        if (ans == 1)
            sum = 1LL * x * y % mod;
        else
            for (auto &u : g[ans - 1])
                sum = (0LL + sum + calc(u, x, y)) % mod;
        printf("%lld %lld\n", ans, sum);
    }
    return 0;
}