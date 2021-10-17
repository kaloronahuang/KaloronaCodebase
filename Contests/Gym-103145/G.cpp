// G.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1100, mod = 998244353;

int T, n, m, k, seg_dp[MAX_N], fseg_dp[MAX_N >> 1][MAX_N], fseg_dp_prefix[MAX_N >> 1][MAX_N], fac[MAX_N], fac_inv[MAX_N], dp[MAX_N][MAX_N];

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

int binomial(int n_, int k_) { return 1LL * fac[n_] * fac_inv[n_ - k_] % mod * fac_inv[k_] % mod; }

int main()
{
    for (int i = fac[0] = 1; i < MAX_N; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    fac_inv[MAX_N - 1] = fpow(fac[MAX_N - 1], mod - 2);
    for (int i = MAX_N - 2; i >= 0; i--)
        fac_inv[i] = 1LL * (i + 1) * fac_inv[i + 1] % mod;
    for (int i = 1; i < MAX_N; i++)
    {
        for (int j = 1; j < i; j++)
            seg_dp[i] = (0LL + seg_dp[i] + 1LL * seg_dp[j] * seg_dp[i - j] % mod) % mod;
        seg_dp[i] = (0LL + seg_dp[i] + fac_inv[i]) % mod;
    }
    fseg_dp[0][0] = 1;
    for (int pos = 1; pos <= (MAX_N >> 1); pos++)
        for (int current_acc = pos; current_acc < MAX_N; current_acc++)
        {
            for (int clen = 1; clen <= current_acc; clen++)
                fseg_dp[pos][current_acc] = (0LL + fseg_dp[pos][current_acc] + 1LL * fseg_dp_prefix[pos - 1][current_acc - clen] * fac_inv[clen] % mod) % mod;
            fseg_dp_prefix[pos][current_acc] = (0LL + fseg_dp[pos][current_acc] + fseg_dp_prefix[pos - 1][current_acc]) % mod;
        }
    dp[0][0] = 1;
    for (int i = 1; i <= (MAX_N >> 1); i++)
        for (int j = 0; j <= i; j++)
        {
            dp[i][j] = dp[i - 1][j];
            for (int len = 1; len <= i && j - len >= 0; len++)
                dp[i][j] = (0LL + 1LL * dp[i - len - 1][j - len] * seg_dp[len] % mod + dp[i][j]) % mod;
        }
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%d", &n, &m, &k), k = m - k;
        if (k > n)
        {
            puts("0");
            continue;
        }
        // dp[];
        int ans = 0;
        if (m == k)
            ans = 1LL * fac[m] * dp[n][k] % mod;
        else
        {
            int rep = m - k;
            for (int pre_x = 1; pre_x <= k; pre_x++)
            {
                int pans = 1LL * fseg_dp[pre_x][rep + pre_x] * dp[n - pre_x - 1][k - pre_x] % mod;
                ans = (0LL + ans + pans) % mod;
            }
            ans = 1LL * ans * fac[m] % mod;
        }
        printf("%d\n", ans);
    }
    return 0;
}