// P4128.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 55;

int n, m, mod, stk[MAX_N], tail, ans, fac[MAX_N], fac_inv[MAX_N], inv[MAX_N];

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

void dfs(int rem, int max_level, int acc, int idx, int prod)
{
    if (max_level == 0)
    {
        ans = (0LL + ans + 1LL * prod * fpow(m, idx) % mod) % mod;
        return;
    }
    int init_idx = idx, init_prod = prod;
    for (int i = 1; i <= max_level; i++)
    {
        stk[++tail] = i, idx = init_idx + (i >> 1);
        for (int j = 1; j < tail; j++)
            idx += __gcd(stk[j], i);
        prod = 1LL * init_prod * inv[i] % mod;
        if (i == stk[tail - 1])
            // same color with more consideration;
            prod = 1LL * prod * fac[acc] % mod * fac_inv[acc + 1] % mod;
        dfs(rem - i, min(rem - i, i), i == stk[tail - 1] ? acc + 1 : 1, idx, prod);
        tail--;
    }
}

int main()
{
    scanf("%d%d%d", &n, &m, &mod);
    for (int i = fac[0] = 1; i <= n; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    for (int i = fac_inv[0] = inv[0] = 1; i <= n; i++)
        fac_inv[i] = 1LL * fac_inv[i - 1] * (inv[i] = fpow(i, mod - 2)) % mod;
    dfs(n, n, 0, 0, 1), printf("%d\n", ans);
    return 0;
}