// UOJ549.cpp
#include <bits/stdc++.h>
#define reg register

using namespace std;

const int MAX_N = 6e4 + 200, MAX_B = (1 << 12);

int n, kidx, ai[MAX_N], pre[MAX_N];

namespace Subtask1
{

    int dp[9][MAX_N];

    int handler()
    {
        memset(dp, 0x3f, sizeof(dp)), dp[0][0] = 0;
        for (int k = 1; k <= kidx; k++)
            for (int i = k; i <= n; i++)
                for (int j = 0; j < i; j++)
                    dp[k][i] = min(dp[k][i], dp[k - 1][j] + (pre[i] ^ pre[j]));
        for (int i = kidx; i <= n; i++)
            printf("%d ", dp[kidx][i]);
        puts("");
        return 0;
    }

} // namespace Subtask1

namespace Subtask2
{

    int dp[9][MAX_B];

    int handler()
    {
        memset(dp, 0x3f, sizeof(dp)), dp[0][0] = 0;
        int mbit = 1, max_val = *max_element(ai + 1, ai + 1 + n);
        while (mbit <= max_val)
            mbit <<= 1;
        for (int i = 1; i <= n; i++)
            for (int j = min(i, kidx); j >= 1; j--)
            {
                int ret = 0x3f3f3f3f;
                for (int t = 0; t < mbit; t++)
                    ret = min(ret, dp[j - 1][t] + (pre[i] ^ t));
                dp[j][pre[i]] = min(dp[j][pre[i]], ret);
                if (j == kidx)
                    printf("%d ", ret);
            }
        puts("");
        return 0;
    }

} // namespace Subtask2

/*

namespace Subtask2
{

    int dp[MAX_B][9];
    bool vis[MAX_B];

    int handler()
    {
        int cnt = 0;
        memset(dp, 0x3f, sizeof(dp)), dp[0][0] = 0;
        for (reg int i = 1; i <= n; i++)
        {
            if (i >= kidx)
            {
                int ans = 0x7f7f7f7f;
                for (reg int last = 0; last < MAX_B; last++)
                    if (dp[last][kidx - 1] != 0x3f3f3f3f)
                        ans = min(ans, dp[last][kidx - 1] + (pre[i] ^ last));
                printf("%d ", ans);
            }
            if (!vis[pre[i]] || cnt > 0)
            {
                cnt = (vis[pre[i]]) ? 0 : cnt + 1, vis[pre[i]] = true;
                for (reg int k = min(kidx - 1, i); k >= 1; k--)
                    for (reg int pre_stat = 0; pre_stat < MAX_B; pre_stat++)
                        dp[pre[i]][k] = min(dp[pre[i]][k], dp[pre_stat][k - 1] + (pre[i] ^ pre_stat));
            }
        }
        puts("");
        return 0;
    }

} // namespace Subtask2

*/

int main()
{
    scanf("%d%d", &n, &kidx);
    for (reg int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), pre[i] = ai[i] ^ pre[i - 1];
    if (n <= 5000)
        return Subtask1::handler();
    else
        return Subtask2::handler();
    return 0;
}