// B.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 2e7 + 200, mod = 998244353;

ll x, T, n, idx[3], tot, inv2;
int f[MAX_N], g[MAX_N], fac[MAX_N];

ll quick_pow(ll bas, ll tim)
{
    ll ans = 1;
    bas %= mod;
    while (tim)
    {
        if (tim & 1)
            ans = 1LL * ans * bas % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ans;
}

int main()
{
    inv2 = quick_pow(2, mod - 2);
    scanf("%lld%lld", &x, &T);

    ll tmp = x;
    for (ll i = 2; i * i <= tmp; i++)
        if (tmp % i == 0)
        {
            ll bitnum = 0;
            while (tmp % i == 0)
                tmp /= i, bitnum++;
            idx[bitnum]++;
        }
    if (tmp > 1)
        idx[1]++;

    g[1] = fac[0] = fac[1] = 1;
    for (int i = 2; i < MAX_N; i++)
    {
        fac[i] = 1LL * fac[i - 1] * i % mod;
        g[i] = 1LL * (1LL * g[i - 1] + 1LL * f[i - 1]) * i % mod;
        f[i] = 1LL * i * (i - 1) % mod * (2LL * f[i - 1] % mod + g[i - 1]) % mod * inv2 % mod;
    }
    while (T--)
        scanf("%lld", &n), printf("%lld\n", quick_pow(f[n] + g[n], idx[2]) * quick_pow(2, (n - 1) * (n - 1) % (mod - 1)) % mod * quick_pow(fac[n], idx[1]) % mod);
    return 0;
}