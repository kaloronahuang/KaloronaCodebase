// UOJ394.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 6e5 + 200, mod = 998244353, BLOCK = 85;

int T, n, pi[MAX_N], dp[1 << 18][(BLOCK << 1) + 1][2], cnt[1 << 18];

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        memset(dp, 0, sizeof(dp));
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d", &pi[i]), pi[i]--;
        dp[0][BLOCK][1] = 1;
        for (int stat = 0; stat < (1 << n); stat++)
            cnt[stat] = cnt[stat >> 1] + (stat & 1);
        for (int stat = 0; stat < (1 << n); stat++)
            for (int last = -BLOCK; last <= BLOCK; last++)
                if (dp[stat][last + BLOCK][0] || dp[stat][last + BLOCK][1])
                {
                    int pcnt = 0;
                    for (int i = 0; i < n; i++)
                        if (!(stat & (1 << i)))
                        {
                            int nxt = last + abs(i - cnt[stat]) - 2 * (cnt[stat] - pcnt);
                            if (nxt <= BLOCK && nxt >= -BLOCK)
                                dp[stat ^ (1 << i)][nxt + BLOCK][0] = (0LL + dp[stat ^ (1 << i)][nxt + BLOCK][0] + dp[stat][last + BLOCK][0]) % mod;
                            if (pi[cnt[stat] + 1] == i)
                                dp[stat ^ (1 << i)][nxt + BLOCK][1] = (0LL + dp[stat ^ (1 << i)][nxt + BLOCK][1] + dp[stat][last + BLOCK][1]) % mod;
                            else if (i > pi[cnt[stat] + 1])
                                dp[stat ^ (1 << i)][nxt + BLOCK][0] = (0LL + dp[stat ^ (1 << i)][nxt + BLOCK][0] + dp[stat][last + BLOCK][1]) % mod;
                        }
                        else
                            pcnt++;
                }
        printf("%d\n", dp[(1 << n) - 1][BLOCK][0]);
    }
    return 0;
}