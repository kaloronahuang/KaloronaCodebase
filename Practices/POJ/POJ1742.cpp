// POJ1742.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m, ai[120], ci[120], used[100200];
bool dp[100200];
int main()
{
    while (scanf("%d%d", &n, &m) && n)
    {
        for (int i = 1; i <= n; i++)
            scanf("%d", &ai[i]);
        for (int i = 1; i <= n; i++)
            scanf("%d", &ci[i]);
        memset(dp, 0, sizeof(dp));
        dp[0] = true;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 0; j <= m; j++)
                used[j] = 0;
            for (int j = ai[i]; j <= m; j++)
                if (!dp[j] && dp[j - ai[i]] && used[j - ai[i]] < ci[i])
                    dp[j] = true, used[j] = used[j - ai[i]] + 1;
        }
        int ans = 0;
        for (int i = 1; i <= m; i++)
            if (dp[i])
                ans++;
        printf("%d\n", ans);
    }
    return 0;
}