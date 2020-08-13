// UOJ551.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 10, MAX_E = 3e5 + 200, MAX_V = 65500, mod = 998244353;

int n, m, q, maxv;

struct edge
{
    int u, v, c;
} edges[MAX_E];

namespace Subtask1
{

    int dp[MAX_N][MAX_N][220], edp[MAX_N][MAX_N][220];

    int handler()
    {
        for (int i = 1; i <= m; i++)
            edp[edges[i].u][edges[i].v][edges[i].c]++;
        for (int i = 1; i <= n; i++)
            dp[i][i][0] = 1;
        for (int sum = 1; sum <= maxv; sum++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    for (int k = 1; k <= n; k++)
                        for (int b = 1; b <= sum; b++)
                            dp[i][j][sum] = (0LL + dp[i][j][sum] + 1LL * dp[i][k][sum - b] * edp[k][j][b] % mod) % mod;
        while (q--)
        {
            int u, v, c;
            scanf("%d%d%d", &u, &v, &c), printf("%d\n", dp[u][v][c]);
        }
        return 0;
    }

} // namespace Subtask1

namespace Subtask2
{

    int dp[MAX_V], pack[MAX_V];

    int handler()
    {
        dp[0] = 1;
        for (int i = 1; i <= m; i++)
            pack[edges[i].c]++;
        for (int sum = 1; sum <= maxv; sum++)
            for (int v = 1; v <= sum; v++)
                if (pack[v] && dp[sum - v])
                    dp[sum] = (0LL + dp[sum] + 1LL * pack[v] * dp[sum - v] % mod) % mod;
        while (q--)
        {
            int u, v, c;
            scanf("%d%d%d", &u, &v, &c);
            printf("%d\n", dp[c]);
        }
        return 0;
    }

} // namespace Subtask2

int main()
{
    scanf("%d%d%d%d", &n, &m, &q, &maxv);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &edges[i].u, &edges[i].v, &edges[i].c);
    if (n == 1)
        return Subtask2::handler();
    else if (m <= 2000 && maxv <= 200)
        return Subtask1::handler();
    
    return 0;
}