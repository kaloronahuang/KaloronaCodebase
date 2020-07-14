// BZ3195.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 35, MAX_S = 1 << 10, mod = 1e9 + 7;

int n, m, k, dp[2][MAX_N][MAX_S];

int main()
{
    scanf("%d%d%d", &n, &m, &k), k++;
    int b = 1;
    dp[0][0][0] = 1;
    for (int i = 1; i <= n; i++, b ^= 1)
    {
        memset(dp[b], 0, sizeof(dp[b]));
        for (int j = 0; j <= m; j++)
            for (int stat = 0; stat < (1 << min(i, k)); stat++)
                if (!(stat & 1))
                    dp[b][j][stat] = dp[!b][j][stat >> 1];
        for (int pt = max(1, i - k + 1); pt <= i - 1; pt++)
            for (int j = m; j >= 1; j--)
                for (int delta = j; delta >= 1; delta--)
                    for (int stat = 0; stat < (1 << min(i, k)); stat++)
                        dp[b][j][stat] = (0LL + dp[b][j][stat] + dp[b][j - delta][stat ^ (delta & 1) ^ ((delta & 1) << (i - pt))]) % mod;
    }
    printf("%d\n", dp[n & 1][m][0]);
    return 0;
}