// BZ2616.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 550, mod = 1000000007, RANGE = 1e6 + 200;

int n, threshold, hi[MAX_N], fac[RANGE], fac_inv[RANGE], stk[MAX_N], ch[MAX_N][2], siz[MAX_N], tail;
int dp[MAX_N][MAX_N], tmp[MAX_N];

int binomial(int n_, int k_) { return (n_ < k_ || k_ < 0) ? 0 : 1LL * fac[n_] * fac_inv[k_] % mod * fac_inv[n_ - k_] % mod; }

void dfs(int u, int fa)
{
    int delta = hi[u] - fa;
    siz[u] = 1;
    for (int i = 0; i < 2; i++)
        if (ch[u][i])
            dfs(ch[u][i], hi[u]), siz[u] += siz[ch[u][i]];
    memset(tmp, 0, sizeof(tmp));
    for (int i = 0; i <= siz[u]; i++)
        for (int j = 0; j <= i; j++)
            tmp[i] = (0LL + tmp[i] + 1LL * dp[ch[u][0]][j] * dp[ch[u][1]][i - j] % mod) % mod;
    for (int i = 0; i <= siz[u]; i++)
        for (int j = 0; j <= i; j++)
            dp[u][i] = (0LL + dp[u][i] + 1LL * tmp[i - j] * fac[j] % mod * binomial(delta, j) % mod * binomial(siz[u] - (i - j), j) % mod) % mod;
}

int main()
{
    scanf("%d%d", &n, &threshold);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &hi[i]);
        bool flag = false;
        while (hi[stk[tail]] > hi[i])
            flag = true, tail--;
        ch[stk[tail]][1] = i;
        if (flag)
            ch[i][0] = stk[tail + 1];
        stk[++tail] = i;
    }
    for (int i = fac[0] = 1; i < RANGE; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    fac_inv[0] = fac_inv[1] = 1;
    for (int i = 2; i < RANGE; i++)
        fac_inv[i] = 1LL * (mod - mod / i) * fac_inv[mod % i] % mod;
    for (int i = 2; i < RANGE; i++)
        fac_inv[i] = 1LL * fac_inv[i] * fac_inv[i - 1] % mod;
    dp[0][0] = 1, dfs(ch[0][1], 0), printf("%d\n", dp[ch[0][1]][threshold]);
    return 0;
}