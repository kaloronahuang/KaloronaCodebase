// C.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const ll MAX_K = 16, MAX_C = 7, MAX_N = MAX_K * MAX_C, mod = 1000000007;

ll T, n, k, ci[MAX_K], dp[MAX_N][MAX_N], sum[MAX_N], C[MAX_N][MAX_N];

ll comb(ll a, ll b) { return C[a][b]; }

signed main()
{
    C[0][0] = 1;
    for (int i = 1; i < MAX_N; i++)
    {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j <= i - 1; j++)
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
    }
    scanf("%lld", &T);
    while (T--)
    {
        scanf("%lld", &k), n = 0, sum[0] = 0;
        for (int i = 1; i <= k; i++)
            scanf("%lld", &ci[i]), n += ci[i], sum[i] = sum[i - 1] + ci[i];
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;
        for (int i = 1; i <= k; i++)
            for (int j = 0; j <= sum[i - 1]; j++)
                if (dp[i - 1][j])
                    for (int x = 1; x <= ci[i]; x++)
                        for (int y = 0; y <= min(1LL * j, ci[i]); y++)
                            (dp[i][j + ci[i] - x - y] += dp[i - 1][j] * comb(ci[i] - 1, x - 1) % mod * comb(j, y) % mod * comb(sum[i - 1] - j + 1, x - y) % mod) %= mod;
        printf("%lld\n", dp[k][0]);
    }
    return 0;
}