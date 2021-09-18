// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, mod = 998244353;

int T, n, ai[MAX_N], fac[MAX_N], fac_inv[MAX_N];

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

int binomial(int n_, int k_) { return 1LL * fac[n_] * fac_inv[k_] % mod * fac_inv[n_ - k_] % mod; }

int main()
{
    scanf("%d", &T);
    for (int i = fac[0] = 1; i < MAX_N; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    fac_inv[MAX_N - 1] = fpow(fac[MAX_N - 1], mod - 2);
    for (int i = MAX_N - 2; i >= 0; i--)
        fac_inv[i] = 1LL * fac_inv[i + 1] * (i + 1) % mod;
    while (T--)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d", &ai[i]);
        sort(ai + 1, ai + 1 + n);
        if (ai[n] > ai[n - 1] + 1)
        {
            puts("0");
            continue;
        }
        if (ai[n] == ai[n - 1])
            printf("%d\n", fac[n]);
        else
        {
            int ans = 0, cnt = 0;
            for (int i = 1; i <= n; i++)
                cnt += (ai[i] == ai[n - 1]);
            ans = 1LL * cnt * ((0LL + ans + 1LL * fac[cnt] * fac[n - cnt - 1] % mod * binomial(n, n - cnt - 1) % mod) % mod) % mod;
            printf("%d\n", ans);
        }
    }
    return 0;
}