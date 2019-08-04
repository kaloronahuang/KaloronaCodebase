// BZ4487.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 440, mod = 1000000007;

ll n, m, c, fac[MAX_N], fac_inv[MAX_N];

ll quick_pow(ll bas, ll tim)
{
    ll ans = 1;
    bas %= mod;
    while (tim)
    {
        if (tim & 1)
            ans = ans * bas % mod;
        bas = bas * bas % mod;
        tim >>= 1;
    }
    return ans;
}

ll C(ll a, ll b) { return fac[a] * fac_inv[b] % mod * fac_inv[a - b] % mod; }

int main()
{
    fac[0] = fac_inv[0] = 1;
    for (int i = 1; i < MAX_N; i++)
        fac[i] = fac[i - 1] * i % mod;
    fac_inv[MAX_N - 1] = quick_pow(fac[MAX_N - 1], mod - 2);
    for (int i = MAX_N - 2; i >= 1; i--)
        fac_inv[i] = fac_inv[i + 1] * (i + 1) % mod;
    scanf("%lld%lld%lld", &n, &m, &c);
    ll ans = 0;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++)
            for (int k = 0; k <= c; k++)
                (ans += 1LL * (((i + j + k) & 1) ? -1 : 1) * C(n, i) % mod * C(m, j) % mod * C(c, k) % mod * quick_pow(c - k + 1, (n - i) * (m - j)) % mod + mod) %= mod;
    printf("%lld", ans);
    return 0;
}