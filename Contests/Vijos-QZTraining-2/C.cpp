// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 11;

int mp[MAX_N][MAX_N], dp[1 << MAX_N][1 << MAX_N], n, m, k;

int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1, x, y; i <= m; i++)
        scanf("%d%d", &x, &y), mp[x - 1][y - 1] = mp[y - 1][x - 1] = 1;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (mp[i][j])
                dp[(1 << i) | (1 << j)][(1 << i) | (1 << j)] = 1;
    for (int i = 1; i < (1 << n); i++)
        for (int j = 1; j < (1 << n); j++)
            if ((i & j) == j && dp[i][j] > 0 && __builtin_popcount(j) <= k)
                for (int p = 0; p < n; p++)
                    if ((i & (1 << p)) == 0)
                        for (int to = 0; to < n; to++)
                            if (mp[p][to] && (i & (1 << to)) && (j & (~(1 << to))) < (1 << p))
                                dp[i ^ (1 << p)][j & (~(1 << to)) ^ (1 << p)] += dp[i][j];
    int ans = 0;
    for (int stat = 1; stat < (1 << n); stat++)
        if (__builtin_popcount(stat) == k)
            ans += dp[(1 << n) - 1][stat];
    printf("%d", ans);
    return 0;
}