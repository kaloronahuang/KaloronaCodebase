// P4056.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 201000, MAX_M = 1010;
const double INF = 1e18, eps = 1e-6;

int n, m, dp[MAX_M][MAX_M], q[MAX_N], recent[MAX_M];
int val[MAX_M][MAX_M], dist[MAX_N];

double calc(int j, int k) { return (k == j ? -INF : (1.0 * (dp[recent[j]][j] - dp[recent[k]][k] - dist[j] + dist[k] - j * j + k * k) / (2 * (k - j)))); }

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, x, y, value; i <= n; i++)
        scanf("%d%d%d", &x, &y, &value), val[x][y] = value;
    memset(dp, 128, sizeof(dp));
    dp[1][1] = val[1][1], recent[1] = 1, val[1][1] = 0;
    for (int i = 1; i <= m; i++)
    {
        int l = 1, r = 0;
        for (int j = 1; j <= m; j++)
            dist[j] = (recent[j] != 0) * (recent[j] - i) * (recent[j] - i);
        for (int j = 1; j <= m; j++)
        {
            if (recent[j])
            {
                while (l < r && calc(q[r - 1], q[r]) > calc(q[r], j) - eps)
                    r--;
                q[++r] = j;
            }
            if (val[i][j])
            {
                while (l < r && calc(q[l], q[l + 1]) < j + eps)
                    l++;
                dp[i][j] = dp[recent[q[l]]][q[l]] - dist[q[l]] - (j - q[l]) * (j - q[l]) + val[i][j];
                recent[j] = i, dist[j] = 0;
                while (l < r && calc(q[r - 1], q[r]) > calc(q[r], j) - eps)
                    r--;
                q[++r] = j;
            }
        }
    }
    printf("%d\n", dp[m][m]);
    return 0;
}