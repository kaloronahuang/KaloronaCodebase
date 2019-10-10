// P1941.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1001000, INF = 0x3f3f3f3f;

int dp[10010][2020], n, m, k, jump[MAX_N], descend[MAX_N], upper[MAX_N], lower[MAX_N];
bool tunnel[MAX_N];

int main()
{
    memset(upper, -1, sizeof(upper)), memset(lower, -1, sizeof(lower));
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &jump[i], &descend[i]), lower[i] = 1, upper[i] = m;
    for (int i = 1, x; i <= k; i++)
        scanf("%d", &x), scanf("%d%d", &lower[x], &upper[x]), lower[x]++, upper[x]--, tunnel[x] = true;
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 1; i <= m; i++)
        dp[0][i] = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = jump[i] + 1; j <= m + jump[i]; j++)
            dp[i][j] = min(dp[i - 1][j - jump[i]] + 1, dp[i][j - jump[i]] + 1);
        for (int j = m + 1; j <= m + jump[i]; j++)
            dp[i][m] = min(dp[i][m], dp[i][j]);
        for (int j = 1; j <= m - descend[i]; j++)
            dp[i][j] = min(dp[i][j], dp[i - 1][j + descend[i]]);
        for (int j = 0; j < lower[i]; j++)
            dp[i][j] = INF;
        for (int j = upper[i] + 1; j <= m; j++)
            dp[i][j] = INF;
    }
    int ans = INF;
    for (int i = 1; i <= m; i++)
        ans = min(ans, dp[n][i]);
    if (ans < INF)
        printf("1\n%d\n", ans), exit(0);
    int pos = n;
    for (int i = n; i >= 1; i--)
    {
        bool flag = true;
        for (int j = 1; j <= m; j++)
            if (dp[i][j] < INF)
            {
                flag = false;
                break;
            }
        if (!flag)
        {
            pos = i;
            break;
        }
    }
    int cnt = 0;
    for (int i = 1; i <= pos; i++)
        if (tunnel[i])
            cnt++;
    printf("0\n%d\n", cnt);
    return 0;
}