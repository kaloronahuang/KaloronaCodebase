// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 301, mod = 1e9 + 7;

int dp[2][MAX_N][2001], bucket[(int)1e6 + 200], n, m, X, fac[MAX_N << 1], fac_inv[MAX_N << 1];
int id[(int)1e6 + 200];

int quick_pow(int bas, int tim)
{
    int ans = 1;
    while (tim)
    {
        if (tim & 1)
            ans = 1LL * bas * ans % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ans;
}

int combination(int n_, int k_) { return 1LL * fac[n_] * fac_inv[n_ - k_] % mod * fac_inv[k_] % mod; }

int main()
{
    /*
    freopen("mobitel.in", "r", stdin);
    freopen("mobitel.out", "w", stdout);
    */
    scanf("%d%d%d", &n, &m, &X);
    X--;
    for (int i = fac[0] = 1; i <= n + m; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    fac_inv[0] = 1, fac_inv[n + m] = quick_pow(fac[n + m], mod - 2);
    for (int i = n + m - 1; i >= 1; i--)
        fac_inv[i] = 1LL * fac_inv[i + 1] * (i + 1) % mod;
    int ans = combination(n + m - 2, n - 1);
    for (int i = 1; i <= X; i++)
        if (bucket[bucket[0]] != X / i)
        {
            bucket[++bucket[0]] = X / i;
            id[(int)(X / i)] = bucket[0];
        }
    dp[0][1][1] = 1;
    for (int i = 1; i <= n; i++)
    {
        memset(dp[i & 1], 0, sizeof(dp[i & 1]));
        for (int j = 1; j <= m; j++)
        {
            int num;
            scanf("%d", &num);
            for (int k = 1; k <= bucket[0]; k++)
                dp[i & 1][j][id[bucket[k] / num]] = (1LL * dp[i & 1][j][id[bucket[k] / num]] + 1LL * dp[(i - 1) & 1][j][k] + 1LL * dp[i & 1][j - 1][k]) % mod;
        }
    }
    for (int i = 1; i <= bucket[0]; i++)
        ans = (1LL * ans - 1LL * dp[n & 1][m][i] + 1LL * mod) % mod;
    printf("%d", ans);
    return 0;
}