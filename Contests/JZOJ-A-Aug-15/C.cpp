// C.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 310, MAX_C = 1e6 + 200, mod = 1e9 + 7;

int n, m, dp[MAX_N << 1][MAX_N][MAX_N], fac[MAX_C], fac_inv[MAX_C];

int quick_pow(int bas, int tim)
{
    int ans = 1;
    bas %= mod;
    while (tim)
    {
        if (tim & 1)
            ans = 1LL * ans * bas % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ans;
}

int Comb(int n_, int k_) { return 1LL * fac[n_] * fac_inv[k_] % mod * fac_inv[n_ - k_] % mod; }
int A(int n_, int k_) { return 1LL * fac[n_] * fac_inv[n_ - k_] % mod; }

int main()
{
    scanf("%d%d", &n, &m);
    dp[0][0][0] = 1;
    ll answer = 0;

    for (int i = fac[0] = fac_inv[0] = 1; i < MAX_C; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    fac_inv[MAX_C - 1] = quick_pow(fac[MAX_C - 1], mod - 2);
    fac_inv[0] = 1;
    for (int i = MAX_C - 2; i >= 1; i--)
        fac_inv[i] = 1LL * fac_inv[i + 1] * (i + 1) % mod;

    for (int i = 1; i <= min(m << 1, n); i++)
        for (int j = 1; j <= m; j++)
            for (int k = j, sum = 0; k > 0; k--)
            {
                dp[i][j][k] = (dp[i - 1][j - 1][k - 1] + sum) % mod;
                sum = (dp[i - 1][j][k] + sum) % mod;
                answer = (answer + 1LL * dp[i][j][k] * A(m, j) % mod * Comb(n - 1, i - 1) % mod) % mod;
            }
    printf("%lld", answer);
    return 0;
}
