// D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 220, MAX_LOG = 20;

int n, m, sum[MAX_N][MAX_N], dp[2][MAX_N][MAX_N][MAX_N];
char str[MAX_N][MAX_N];

bool check(int i, int j, int l, int r)
{
    int acc = sum[j][r] - sum[i - 1][r] - sum[j][l - 1] + sum[i - 1][l - 1];
    return acc == 0 || acc == 1LL * (j - i + 1) * (r - l + 1);
}

int calc(int p, int i, int j, int k)
{
    int l = i, r = j - 1, res = 0;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        res = max(res, min(dp[p][i][mid][k], dp[p][mid + 1][j][k]));
        if (dp[p][i][mid][k] < dp[p][mid + 1][j][k])
            r = mid - 1;
        else
            l = mid + 1;
    }
    return res;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%s", str[i] + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + (str[i][j] == '#');
    if (check(1, n, 1, m))
        puts("0"), exit(0);
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j++)
            for (int k = 1, acc; k <= m; k = acc)
            {
                acc = k;
                while (acc <= m && check(i, j, k, acc))
                    acc++;
                for (int p = k; p < acc; p++)
                    dp[0][i][j][p] = acc - 1;
                if (acc == k)
                    dp[0][i][j][k] = k - 1, acc++;
            }
    for (int x = 1;; x++)
    {
        int c = x & 1, pc = !(x & 1);
        for (int i = 1; i <= n; i++)
            for (int j = i; j <= n; j++)
                for (int k = 1; k <= m; k++)
                {
                    int ret = dp[pc][i][j][k];
                    if (ret == m)
                        dp[c][i][j][k] = m;
                    else
                        dp[c][i][j][k] = max(dp[pc][i][j][ret + 1], calc(pc, i, j, k));
                }
        if (dp[c][1][n][1] == m)
            printf("%d\n", x), exit(0);
    }
    return 0;
}