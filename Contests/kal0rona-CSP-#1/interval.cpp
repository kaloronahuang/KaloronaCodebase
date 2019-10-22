// interval.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 5100, mod = 998244353;

ll n, k, l, f[MAX_N << 1], level[MAX_N], level_rev[MAX_N];

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

ll comb(ll x, ll y)
{
    return level[x] * level_rev[x - y] % mod * level_rev[y] % mod;
}

int main()
{
    scanf("%lld%lld%lld", &n, &k, &l);
    // Get Ready for the f;
    f[0] = 1;
    for (int i = 1; i <= n; i++)
        f[2 * i] = f[2 * (i - 1)] * (2 * i - 1) % mod;

    // Get ready for the levels;
    level[1] = level[0] = level_rev[1] = level_rev[0] = 1;
    for (int i = 2; i < MAX_N; i++)
        level[i] = level[i - 1] * i % mod;
    level_rev[MAX_N - 1] = quick_pow(level[MAX_N - 1], mod - 2);
    for (int i = MAX_N - 1; i >= 3; i--)
        level_rev[i - 1] = level_rev[i] * i % mod;

    ll answer = 0;

    for (int h = 2; h <= 2 * n; h++)
    {
        int A = h - 1, B = 2 * n - h + 1;
        for (int i = k; i <= min(A, B); i++)
        {
            ll all = comb(A, i) * comb(B, i) % mod * level[i] % mod * f[A - i] % mod * f[B - i] % mod;
            answer = (answer + all) % mod;
        }
    }
    answer = answer * quick_pow(2 * n + 1, mod - 2) % mod * quick_pow(f[2 * n], mod - 2) % mod * l % mod;
    printf("%lld", answer);
    return 0;
}