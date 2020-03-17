// UOJ422.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 7, MAX_M = 110, mod = 998244353, MAX_I = 1e5 + 200;

int n, m, overlayTot, inv[MAX_I], dp[2][1 << MAX_N][1200];
char mp[MAX_N][MAX_M];

int main()
{
    scanf("%d%d", &n, &m), overlayTot = 2 * n * m - n - m;
    for (int i = 1; i <= n; i++)
        scanf("%s", mp[i] + 1);
    inv[0] = inv[1] = 1;
    for (int i = 2; i < MAX_I; i++)
        inv[i] = 1LL * inv[mod % i] * (mod - mod / i) % mod;
    dp[0][0][0] = mod - 1;
    int b = 0;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
        {
            b ^= 1;
            memset(dp[b], 0, sizeof(dp[b]));
            for (int stat = 0; stat < (1 << n); stat++)
                for (int overlay = 0; overlay <= overlayTot; overlay++)
                    if (dp[!b][stat][overlay])
                    {
                        // select j;
                        int nxt = stat & (((1 << n) - 1) ^ (1 << (j - 1)));
                        dp[b][nxt][overlay] = (0LL + dp[b][nxt][overlay] + dp[!b][stat][overlay]) % mod;
                        if (mp[j][i] == '*')
                        {
                            nxt |= (1 << (j - 1));
                            int sol = 0;
                            if (j > 1 && !(stat & (1 << (j - 2))))
                                sol++;
                            if (i > 1 && !(stat & (1 << (j - 1))))
                                sol++;
                            sol += (j < n) + (i < m);
                            dp[b][nxt][overlay + sol] = (0LL + dp[b][nxt][overlay + sol] + mod - dp[!b][stat][overlay]) % mod;
                        }
                    }
        }
    int ans = 0;
    for (int stat = 0; stat < (1 << n); stat++)
        for (int j = 1; j <= overlayTot; j++)
            ans = (0LL + ans + 1LL * dp[b][stat][j] * inv[j] % mod) % mod;
    printf("%lld\n", 1LL * ans * overlayTot % mod);
    return 0;
}