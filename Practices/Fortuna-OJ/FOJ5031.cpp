// FOJ5031.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, mod = 1e9 + 7;

int T, n, k, f[MAX_N], coeff[MAX_N], g[MAX_N], fac[MAX_N], fac_inv[MAX_N];

int binomial(int n_, int k_) { return 1LL * fac[n_] * fac_inv[k_] % mod * fac_inv[n_ - k_] % mod; }

int main()
{
    
    freopen("b.in", "r", stdin);
    freopen("b.out", "w", stdout);
    
    scanf("%d", &T);
    for (int i = fac[0] = 1; i < MAX_N; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    fac_inv[0] = fac_inv[1] = 1;
    for (int i = 2; i < MAX_N; i++)
        fac_inv[i] = 1LL * (mod - mod / i) * fac_inv[mod % i] % mod;
    for (int i = 2; i < MAX_N; i++)
        fac_inv[i] = 1LL * fac_inv[i - 1] * fac_inv[i] % mod;
    while (T--)
    {
        scanf("%d%d", &n, &k);
        coeff[1] = 1;
        for (int x = 2; x < MAX_N; x++)
        {
            int ret = 1, acc = x;
            for (int i = 2; 1LL * i * i <= acc; i++)
                if (acc % i == 0)
                {
                    int cnt = 0;
                    while (acc % i == 0)
                        acc /= i, cnt++;
                    ret = 1LL * ret * binomial(k + cnt - 1, cnt) % mod;
                }
            if (acc > 1)
                ret = 1LL * ret * k % mod;
            coeff[x] = ret;
        }
        for (int i = 1; i <= n; i++)
            scanf("%d", &f[i]), g[i] = 0;
        for (int x = 1; x <= n; x++)
            for (int i = 1; 1LL * i * i <= x; i++)
                if (x % i == 0)
                {
                    g[x] = (0LL + g[x] + 1LL * f[i] * coeff[x / i] % mod) % mod;
                    if (x / i != i)
                        g[x] = (0LL + g[x] + 1LL * f[x / i] * coeff[i] % mod) % mod;
                }
        for (int i = 1; i <= n; i++)
            printf("%d ", g[i]);
        puts("");
    }
    return 0;
}