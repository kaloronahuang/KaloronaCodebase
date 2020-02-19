// camp.cpp
// #pragma GCC optimize(2)
#include <bits/stdc++.h>

using namespace std;

const int MAX_K = 1e5 + 200, MAX_N = 2020, mod = 1e9 + 7;

int n, m, a, b, k, prob[MAX_K], prob_rev[MAX_K], fac[MAX_K], fac_inv[MAX_K], pre_prob[MAX_N];
int dp[2][MAX_N][MAX_N], pre[2][MAX_N][MAX_N], pre_weighted[2][MAX_N][MAX_N];

void fileIO()
{
    freopen("camp.in", "r", stdin);
    freopen("camp.out", "w", stdout);
}

int quick_pow(int bas, int tim)
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

int getProb(int l) { return 1LL * binomial(k, l) * prob[l] % mod * prob_rev[k - l] % mod; }

void initialize()
{
    for (int i = fac[0] = 1; i <= k; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    fac_inv[k] = quick_pow(fac[k], mod - 2);
    for (int i = k - 1; i >= 0; i--)
        fac_inv[i] = 1LL * fac_inv[i + 1] * (i + 1) % mod;
    prob[0] = 1, prob[1] = 1LL * a * quick_pow(b, mod - 2) % mod;
    prob_rev[0] = 1, prob_rev[1] = (mod + 1 - prob[1]) % mod;
    for (int i = 2; i <= k; i++)
        prob[i] = 1LL * prob[i - 1] * prob[1] % mod, prob_rev[i] = 1LL * prob_rev[i - 1] * prob_rev[1] % mod;
    for (int i = 1; i <= m; i++)
        pre_prob[i] = (0LL + pre_prob[i - 1] + getProb(i - 1)) % mod;
}

int main()
{
    // fileIO();
    scanf("%d%d%d%d%d", &n, &m, &a, &b, &k);
    initialize();
    dp[0][0][0] = pre[0][0][0] = 1;
    dp[1][0][m] = pre[1][0][m] = 1;
    for (int row = 1; row <= n; row++)
    {
        for (int rig = 0; rig <= m; rig++)
        {
            dp[1][row][rig] = 1LL * pre_prob[rig] * pre[1][row - 1][m] % mod;
            dp[1][row][rig] = (0LL + dp[1][row][rig] + mod - pre_weighted[1][row - 1][rig]) % mod;
            dp[1][row][rig] = (0LL + dp[1][row][rig] + mod - 1LL * pre[0][row - 1][rig + 1] * pre_prob[rig] % mod) % mod;
            dp[1][row][rig] = 1LL * dp[1][row][rig] * getProb(m - rig) % mod;
        }

        pre[1][row][0] = dp[1][row][0];
        for (int i = 1; i <= m; i++)
            pre[1][row][i] = (0LL + pre[1][row][i - 1] + dp[1][row][i]) % mod;
        for (int i = 1; i <= m; i++)
            pre_weighted[1][row][i] = (0LL + pre_weighted[1][row][i - 1] + 1LL * getProb(i - 1) * pre[1][row][i - 1] % mod) % mod;

        for (int lft = 1; lft <= m + 1; lft++)
        {
            dp[0][row][lft] = 1LL * pre_prob[m - lft + 1] * pre[0][row - 1][1] % mod;
            dp[0][row][lft] = (0LL + dp[0][row][lft] + mod - pre_weighted[0][row - 1][lft]) % mod;
            dp[0][row][lft] = (0LL + dp[0][row][lft] + mod - 1LL * pre[1][row - 1][lft - 1] * pre_prob[m - lft + 1] % mod) % mod;
            dp[0][row][lft] = 1LL * dp[0][row][lft] * getProb(lft - 1) % mod;
        }

        pre[0][row][m + 1] = dp[0][row][m + 1];
        for (int i = m; i >= 1; i--)
            pre[0][row][i] = (0LL + pre[0][row][i + 1] + dp[0][row][i]) % mod;
        for (int i = m; i >= 1; i--)
            pre_weighted[0][row][i] = (0LL + pre_weighted[0][row][i + 1] + 1LL * getProb(m - (i + 1) + 1) * pre[0][row][i + 1] % mod) % mod;
    }
    printf("%lld\n", (0LL + pre[1][n][m] + pre[0][n][1]) % mod);
    return 0;
}