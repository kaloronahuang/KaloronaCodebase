// CF1314D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 88;

int n, limit, mp[MAX_N][MAX_N], dp[MAX_N][MAX_N];
bool part[MAX_N];

int main()
{
    scanf("%d%d", &n, &limit);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", &mp[i][j]);
    int ans = 0x7fffffff;
    srand(time(NULL));
    while (clock() <= 2.0 * CLOCKS_PER_SEC)
    {
        for (int i = 0; i <= limit; i++)
            for (int j = 1; j <= n; j++)
                dp[i][j] = 0x7fffffff;
        dp[0][1] = 0;
        for (int i = 1; i <= n; i++)
            part[i] = (rand() % 2 == 0);
        for (int i = 1; i <= limit; i++)
            for (int j = 1; j <= n; j++)
                if (dp[i - 1][j] < 0x7fffffff)
                    for (int ln = 1; ln <= n; ln++)
                        if (part[j] ^ part[ln])
                            dp[i][ln] = min(dp[i][ln], dp[i - 1][j] + mp[j][ln]);
        ans = min(ans, dp[limit][1]);
    }
    printf("%d\n", ans);
    return 0;
}