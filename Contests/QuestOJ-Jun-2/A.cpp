// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 21;

int n, ai[MAX_N], dp[1 << MAX_N][MAX_N];

int main()
{
    scanf("%d", &n), memset(dp, 0x3f, sizeof(dp));
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), dp[1 << (i - 1)][ai[i]] = ai[i];
    int ans = 0x3f3f3f3f;
    for (int stat = 0; stat < (1 << n); stat++)
        if (__builtin_popcount(stat) > 1)
        {
            for (int i = 1; i <= n; i++)
                if (stat & (1 << (i - 1)))
                    for (int l = 1; l <= 7; l++)
                        dp[stat][max(1, ai[i] - (l - 1))] = min(dp[stat][max(1, ai[i] - (l - 1))], dp[stat ^ (1 << (i - 1))][l] + max(1, ai[i] - (l - 1)));
        }
    for (int l = 1; l <= 7; l++)
        ans = min(ans, dp[(1 << n) - 1][l]);
    printf("%d\n", ans);
    return 0;
}