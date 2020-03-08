// CF1322D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2020, INF = 0x3f3f3f3f;

int n, m, li[MAX_N], si[MAX_N], ci[MAX_N << 1], num[MAX_N], dp[MAX_N][1 << 11];

int fight(int level, int stat)
{
    int ret = 0;
    for (int i = 0; i < 11; i++)
        if (stat & (1 << i))
            ret += ci[level + i];
    return ret;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &li[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &si[i]);
    for (int i = 1; i <= n + m; i++)
        scanf("%d", &ci[i]);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < (1 << 11); j++)
            dp[i][j] = -INF;
        dp[i][0] = 0;
    }
    for (int i = n; i >= 1; i--)
        for (int j = li[i]; j >= 0; j--)
            for (int k = num[j]; k >= 0; k--)
                if (dp[j][k] != -INF)
                {
                    int org = li[i] - j > 11 ? 0 : (k >> (li[i] - j)), dst = org + 1;
                    dp[li[i]][dst] = max(dp[li[i]][dst], dp[j][k] - si[i] + fight(li[i], org ^ dst));
                    num[li[i]] = max(num[li[i]], dst);
                }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < (1 << 11); j++)
            ans = max(ans, dp[i][j]);
    printf("%d\n", ans);
    return 0;
}