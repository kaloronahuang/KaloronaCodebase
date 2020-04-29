// GuOJ1128.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100010, mod = 998244353;

int n, m, k, rdcnt[MAX_N], fac[MAX_N], fac_inv[MAX_N], ai[MAX_N], bi[MAX_N];

int fpow(int bas, int tim)
{
    int ret = 1;
    while (tim)
    {
        if (tim & 1)
            ret = 1LL * ret * bas % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ret;
}

int binomial(int n_, int k_) { return n_ >= k_ ? 1LL * fac[n_] * fac_inv[k_] % mod * fac_inv[n_ - k_] % mod : 0; }

int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= m; i++)
        scanf("%d", &ai[i]);
    for (int i = 1; i <= m; i++)
        scanf("%d", &bi[i]);
    for (int i = fac[0] = 1; i <= n; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    fac_inv[0] = fac_inv[1] = 1;
    for (int i = 2; i <= n; i++)
        fac_inv[i] = 1LL * (mod - mod / i) * fac_inv[mod % i] % mod;
    for (int i = 2; i <= n; i++)
        fac_inv[i] = 1LL * fac_inv[i - 1] * fac_inv[i] % mod;
    for (int i = 1, ktot, val; i <= n; i++)
    {
        scanf("%d", &ktot);
        while (ktot--)
            scanf("%d", &val), rdcnt[val]++;
    }
    int ans = 0, inv = fpow(binomial(n, k), mod - 2);
    for (int i = 1; i <= m; i++)
    {
        int prob = 1LL * binomial(n - rdcnt[i], k) * inv % mod;
        ans = (0LL + ans + 1LL * prob * bi[i] % mod + 1LL * (1 + mod - prob) % mod * ai[i] % mod) % mod;
    }
    printf("%d\n", ans);
    return 0;
}