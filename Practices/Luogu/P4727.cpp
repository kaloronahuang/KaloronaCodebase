// P4727.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 66, mod = 997;

int n, stk[MAX_N], tail, ans, inv[MAX_N], fac[MAX_N], fac_inv[MAX_N];

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

void dfs(int rem, int max_level, int c, int idx, int prod)
{
    if (rem == 0)
    {
        ans = (0LL + ans + 1LL * fpow(2, idx) * prod % mod) % mod;
        return;
    }
    int org_idx = idx, org_prod = prod;
    for (int i = 1; i <= max_level; i++)
    {
        stk[++tail] = i, idx = org_idx + (i >> 1);
        for (int j = 1; j < tail; j++)
            idx += __gcd(stk[j], i);
        prod = 1LL * org_prod * inv[i] % mod;
        if (stk[tail - 1] == i)
            prod = 1LL * prod * fac[c] % mod * fac_inv[c + 1] % mod;
        dfs(rem - i, min(rem - i, i), (stk[tail - 1] == i) ? c + 1 : 1, idx, prod);
        tail--;
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = fac[0] = 1; i <= n; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    for (int i = fac_inv[0] = inv[0] = 1; i <= n; i++)
        fac_inv[i] = 1LL * fac_inv[i - 1] * (inv[i] = fpow(i, mod - 2)) % mod;
    dfs(n, n, 0, 0, 1);
    printf("%d\n", ans);
    return 0;
}