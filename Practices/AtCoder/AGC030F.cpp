// AGC030F.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 330, mod = 1e9 + 7;

int n, ai[MAX_N << 1], dp[MAX_N << 1][MAX_N][MAX_N], both_nexist, single_exist, seq[MAX_N << 1], m;
bool vis[MAX_N << 1], pending[MAX_N << 1];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n << 1; i++)
        scanf("%d", &ai[i]);
    for (int i = 1; i <= n << 1; i += 2)
    {
        if (ai[i] > 0 && ai[i + 1] > 0)
            vis[ai[i]] = vis[ai[i + 1]] = true;
        else if (ai[i] < 0 && ai[i + 1] < 0)
            both_nexist++;
        else
            single_exist++, pending[max(ai[i], ai[i + 1])] = true;
    }
    for (int i = (n << 1); i >= 1; i--)
        if (!vis[i])
            seq[++m] = i;
    dp[0][0][0] = 1;
    for (int i = 1; i <= m; i++)
        for (int j = 0; j <= both_nexist + single_exist; j++)
            for (int k = 0; k <= single_exist; k++)
            {
                if (!pending[seq[i]])
                {
                    dp[i][j + 1][k] = (0LL + dp[i][j + 1][k] + dp[i - 1][j][k]) % mod;
                    if (j > 0)
                        dp[i][j - 1][k] = (0LL + dp[i][j - 1][k] + dp[i - 1][j][k]) % mod;
                    if (k > 0)
                        dp[i][j][k - 1] = (0LL + dp[i][j][k - 1] + 1LL * k * dp[i - 1][j][k] % mod) % mod;
                }
                else
                {
                    dp[i][j][k + 1] = (0LL + dp[i][j][k + 1] + dp[i - 1][j][k]) % mod;
                    if (j > 0)
                        dp[i][j - 1][k] = (0LL + dp[i][j - 1][k] + dp[i - 1][j][k]) % mod;
                }
            }
    int ans = dp[m][0][0];
    for (int i = 1; i <= both_nexist; i++)
        ans = 1LL * ans * i % mod;
    printf("%d\n", ans);
    return 0;
}