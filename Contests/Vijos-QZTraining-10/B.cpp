// B.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1030;

int mp[MAX_N][MAX_N], n, m, T;
ll dp[MAX_N][MAX_N];

int main()
{
    while (scanf("%d%d", &n, &m) != EOF)
    {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                scanf("%d", &mp[i][j]);
        for (int j = 1; j <= m; j++)
        {
            ll cur = -1e18;
            for (int i = 1; i <= n; i++)
                if (mp[i][j] == -1)
                    cur = -1e18, dp[i][j] = cur;
                else
                    cur = max(cur, dp[i][j - 1]) + mp[i][j], dp[i][j] = cur;
            cur = -1e18;
            for (int i = n; i >= 1; i--)
                if (mp[i][j] == -1)
                    cur = -1e18;
                else
                    cur = max(cur, dp[i][j - 1]) + mp[i][j], dp[i][j] = max(cur, dp[i][j]);
            int down_bound = 0;
            for (int i = n; i >= 1; i--)
                if (mp[i][j] == -1)
                    break;
                else if (dp[i][j - 1] >= 0)
                {
                    down_bound = i;
                    break;
                }
            cur = 0;
            for (int i = 1; i < down_bound; i++)
                if (mp[i][j] == -1)
                    break;
                else
                    cur += mp[i][j], dp[i][j] = max(dp[i][j], cur);
            int up_bound = n + 1;
            for (int i = 1; i <= n; i++)
                if (mp[i][j] == -1)
                    break;
                else if (dp[i][j - 1] >= 0)
                {
                    up_bound = i;
                    break;
                }
            cur = 0;
            for (int i = n; i > up_bound; i--)
                if (mp[i][j] == -1)
                    break;
                else
                    cur += mp[i][j], dp[i][j] = max(dp[i][j], cur);
        }
        ll ans = -1;
        for (int i = 1; i <= n; i++)
            ans = max(ans, dp[i][m]);
        printf("%lld\n", ans);
    }
    return 0;
}