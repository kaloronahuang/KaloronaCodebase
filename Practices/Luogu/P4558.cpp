// P4558.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 55, mod = 998244353;

int T, n, m, d, idx[MAX_N][MAX_N], ans, dp[MAX_N][MAX_N][MAX_N * MAX_N];
char mp[MAX_N][MAX_N];

int solve(int x, int y)
{
    memset(dp, 0, sizeof(dp));
    dp[1][1][idx[1][1]] = 1;
    for (int i = 1; i <= x; i++)
        for (int j = 1; j <= y; j++)
            for (int k = 1; k <= n * m; k++)
            {
                if (i < x)
                    dp[i + 1][j][min(k, idx[i + 1][j])] = (0LL + dp[i + 1][j][min(k, idx[i + 1][j])] + dp[i][j][k]) % mod;
                if (j < y)
                    dp[i][j + 1][min(k, idx[i][j + 1])] = (0LL + dp[i][j + 1][min(k, idx[i][j + 1])] + dp[i][j][k]) % mod;
            }
    int ret = 0;
    for (int i = 1; i <= n * m; i++)
        ret = (0LL + ret + 1LL * i * dp[x][y][i] % mod) % mod;
    return ret;
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        memset(idx, 0, sizeof(idx));
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++)
            scanf("%s", mp[i] + 1);
        d = __gcd(n, m), ans = 0;
        for (int i = 1; i <= d; i++)
        {
            int j = d - i;
            if (__gcd(i, d) == 1 && __gcd(i, n) == 1 && __gcd(j, m) == 1)
            {
                for (int tx = 1; tx <= i + 1; tx++)
                    for (int ty = 1; ty <= j + 1; ty++)
                    {
                        int cx = tx, cy = ty, stp = cx + cy - 2;
                        idx[tx][ty] = n * m;
                        while (stp == tx + ty - 2 || cx != tx || cy != ty)
                        {
                            if (mp[cx][cy] == '1')
                            {
                                idx[tx][ty] = stp;
                                break;
                            }
                            cx += i, cy += j;
                            if (cx > n)
                                cx -= n;
                            if (cy > m)
                                cy -= m;
                            stp += d;
                        }
                    }
                ans = (0LL + ans + solve(i + 1, j + 1)) % mod;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}