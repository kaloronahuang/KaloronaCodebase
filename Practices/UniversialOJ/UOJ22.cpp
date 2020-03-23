// UOJ22.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5050, mod = 998244353;

int f[MAX_N], min_val, m, n, ai[MAX_N], cnt[MAX_N], fac[MAX_N], fac_inv[MAX_N], inv[MAX_N], x;

int main()
{
    scanf("%d%d", &n, &x), m = min_val = 5000;
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), cnt[ai[i]]++, min_val = min(min_val, ai[i]);
    for (int i = 1; i <= m; i++)
        cnt[i] += cnt[i - 1];
    for (int i = fac[0] = 1; i <= n; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    inv[0] = inv[1] = 1;
    for (int i = 2; i <= n; i++)
        inv[i] = 1LL * inv[mod % i] * (mod - mod / i) % mod;
    for (int i = fac_inv[0] = 1; i <= n; i++)
        fac_inv[i] = 1LL * fac_inv[i - 1] * inv[i] % mod;
    f[x] = 1LL * fac[n] * fac_inv[cnt[x]] % mod;
    for (int i = m; i >= 1; i--)
        for (int j = 1; j <= n; j++)
            if (ai[j] <= i)
                f[i % ai[j]] = (1LL * f[i % ai[j]] + 1LL * f[i] * fac[cnt[i] - 1] % mod * fac_inv[cnt[i % ai[j]]] % mod) % mod;
    for (int i = min_val - 1; i >= 0; i--)
        if (f[i] > 0)
            printf("%d\n%d\n", i, f[i]), exit(0);
    return 0;
}