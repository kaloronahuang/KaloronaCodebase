// F.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 1e6 + 2000, mod = 1e9 + 7;
ll level[MAX_N], level_rev[MAX_N], n, m, tmpx, tmpy;

ll quick_pow(ll bas, ll tim)
{
    if (tim < 0)
        return quick_pow(bas, tim + mod - 1);
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

ll P(ll a, ll b)
{
    return level[a] * level_rev[a - b] % mod;
}

ll comb(ll a, ll b)
{
    return level[a] * level_rev[b] % mod * level_rev[a - b] % mod;
}

int main()
{
    scanf("%lld%lld%lld%lld", &n, &m, &tmpx, &tmpy);
    ll ans = 0;
    // preprocessing;
    level[1] = level_rev[1] = level[0] = level_rev[0] = 1;
    for (int i = 2; i < MAX_N; i++)
        level[i] = level[i - 1] * i % mod;
    level_rev[MAX_N - 1] = quick_pow(level[MAX_N - 1], mod - 2);
    for (int i = MAX_N - 1; i >= 3; i--)
        level_rev[i - 1] = level_rev[i] * i % mod;
    // start to calc!
    for (int i = 0; i <= min(m - 1, n - 2); i++)
        ans = (ans + P(n - 2, i) * comb(m - 1, i) % mod * quick_pow(m, n - 2 - i) % mod * quick_pow(n, n - 3 - i) % mod * (i + 2) % mod) % mod;
    printf("%lld", ans);
    return 0;
}