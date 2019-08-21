// B.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 110;

ll n, m, mp[MAX_N][MAX_N], a, b, k, dp[2][MAX_N][MAX_N];

int main()
{
	freopen("maja.in", "r", stdin);
	freopen("maja.out", "w", stdout);
    scanf("%lld%lld%lld%lld%lld", &n, &m, &a, &b, &k);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%lld", &mp[i][j]);
    ll gans = 0;
    memset(dp[0], -1, sizeof(dp[0]));
    dp[0][a][b] = 0;
    for (int w = 1; w <= min(n * m, k >> 1); w++)
    {
        memset(dp[w & 1], -1, sizeof(dp[w & 1]));
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
            {
                ll best = max(dp[(w - 1) & 1][i - 1][j], max(dp[(w - 1) & 1][i + 1][j], max(dp[(w - 1) & 1][i][j - 1], dp[(w - 1) & 1][i][j + 1])));
                if (best == -1)
                    continue;
                dp[w & 1][i][j] = mp[i][j] + best;
                // w steps;
                // to bet it;
                if ((k - 2 * w) & 1)
                    continue;
                best = max(mp[i - 1][j], max(mp[i + 1][j], max(mp[i][j + 1], mp[i][j - 1])));
                gans = max(gans, dp[w & 1][i][j] * 2 + ((k - 2 * w) >> 1) * (mp[i][j] + best) - mp[i][j]);
            }
    }
    printf("%lld", gans);
    return 0;
}
