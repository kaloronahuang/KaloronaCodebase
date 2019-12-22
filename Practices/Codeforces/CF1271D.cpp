// CF1271D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5050, INF = 0x3f3f3f3f;

int n, m, k, ai[MAX_N], bi[MAX_N], ci[MAX_N], lft[MAX_N], rig[MAX_N];
int dp[MAX_N][MAX_N];
pair<int, int> trans[MAX_N];

int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d%d%d", &ai[i], &bi[i], &ci[i]), lft[i] = n + 1, rig[i] = i;
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), rig[v] = max(rig[v], u);
    for (int i = 1; i <= n; i++)
        trans[i] = make_pair(rig[i], ci[i]);
    sort(trans + 1, trans + 1 + n);
    for (int i = 1; i <= n; i++)
        lft[trans[i].first] = min(lft[trans[i].first], i);
    for (int i = k + 1; i <= 5000; i++)
        dp[0][i] = -INF;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= 5000; j++)
            dp[i][j] = -INF;
        for (int j = ai[i]; j <= 5000 && j + bi[i] <= 5000; j++)
            dp[i][j + bi[i]] = max(dp[i][j + bi[i]], dp[i - 1][j]);
        for (int idx = lft[i]; idx <= n && trans[idx].first == i; idx++)
            for (int j = 0; j < 5000; j++)
                dp[i][j] = max(dp[i][j], dp[i][j + 1] + trans[idx].second);
    }
    int ans = -1;
    for (int i = 0; i <= 5000; i++)
        ans = max(ans, dp[n][i]);
    printf("%d\n", ans);
    return 0;
}