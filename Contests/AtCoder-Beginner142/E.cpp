// E.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 13, MAX_M = 1e3 + 200;
const ll INF = 0x3f3f3f3f3f3f3f3f;

ll dp[MAX_M][(1 << MAX_N)], n, m, ai[MAX_M], keymp[MAX_M];

int main()
{
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        int tmp, tmpx;
        scanf("%lld%d", &ai[i], &tmp);
        while (tmp--)
            scanf("%d", &tmpx), keymp[i] |= (1 << (tmpx - 1));
    }
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 1; i <= m; i++)
    {
        dp[i][0] = 0;
        for (int stat = 0; stat < (1 << n); stat++)
            dp[i][stat] = dp[i - 1][stat];
        for (int stat = 0; stat < (1 << n); stat++)
            dp[i][stat | keymp[i]] = min(dp[i][stat | keymp[i]], dp[i - 1][stat] + ai[i]);
    }
    if (dp[m][(1 << n) - 1] == INF)
        puts("-1");
    else
        printf("%lld", dp[m][(1 << n) - 1]);
    return 0;
}