// BZ3622.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 2020, mod = 1e9 + 9;

ll n, k, ai[MAX_N], bi[MAX_N], ti[MAX_N], dp[MAX_N][MAX_N], fac[MAX_N], fac_inv[MAX_N];

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

ll comb(ll a, ll b) { return fac[a] * fac_inv[a - b] % mod * fac_inv[b] % mod; }

int main()
{
    scanf("%d%d", &n, &k);
    k = (n + k) >> 1;
    for (int i = 1; i <= n; i++)
        scanf("%lld", &ai[i]);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &bi[i]);
    sort(ai + 1, ai + 1 + n), sort(bi + 1, bi + 1 + n);

    fac[0] = fac_inv[0] = 1;
    for (int i = 1; i <= n; i++)
        fac[i] = fac[i - 1] * i % mod;
    fac_inv[n] = quick_pow(fac[n], mod - 2);
    for (int i = n - 1; i >= 1; i--)
        fac_inv[i] = fac_inv[i + 1] * (i + 1) % mod;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (ai[i] > bi[j])
                ti[i]++;
    for (int i = 0; i <= n; i++)
        dp[i][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++)
            dp[i][j] = (dp[i - 1][j] + dp[i - 1][j - 1] * max(0LL, ti[i] - (j - 1)) % mod) % mod;

    ll ans = 0;
    for (int i = k, opt = 1; i <= n; i++, opt = -opt)
        ans = (ans + (opt * comb(i, k) % mod * (dp[n][i] * fac[n - i] % mod) % mod) + mod) % mod;
    while (ans < 0)
        ans += mod;
    ans %= mod;
    printf("%lld", ans);
    return 0;
} // BZ3622.cpp