// machine.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, mod = 998244353;

int n, f[MAX_N], m, fac[MAX_N], fac_inv[MAX_N];

int binomial(int n_, int k_)
{
    if (n_ < k_ || n_ < 0 || k_ < 0)
        return 0;
    return 1LL * fac[n_] * fac_inv[k_] % mod * fac_inv[n_ - k_] % mod;
}

int solve(int acc, int k)
{
    int ret = 1;
    for (int i = 2; 1LL * i * i <= acc; i++)
        if (acc % i == 0)
        {
            int idx = 0;
            while (acc % i == 0)
                idx++, acc /= i;
            ret = 1LL * ret * binomial(idx + k - 1, idx) % mod;
        }
    if (acc > 1)
        ret = 1LL * ret * k % mod;
    return ret;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &f[i]);
    for (int i = fac[0] = 1; i < MAX_N; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    fac_inv[0] = fac_inv[1] = 1;
    for (int i = 2; i < MAX_N; i++)
        fac_inv[i] = 1LL * (mod - mod / i) * fac_inv[mod % i] % mod;
    for (int i = 2; i < MAX_N; i++)
        fac_inv[i] = 1LL * fac_inv[i - 1] * fac_inv[i] % mod;
    scanf("%d", &m);
    while (m--)
    {
        int x, k, ans = 0;
        scanf("%d%d", &k, &x);
        for (int i = 1; 1LL * i * i <= x; i++)
            if (x % i == 0)
            {
                ans = (0LL + ans + 1LL * f[i] * solve(x / i, k) % mod) % mod;
                if (x / i != i)
                    ans = (0LL + ans + 1LL * f[x / i] * solve(i, k) % mod) % mod;
            }
        printf("%d\n", ans);
    }
    return 0;
}