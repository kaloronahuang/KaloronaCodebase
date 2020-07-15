// P5307.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 330, mod = 1e9 + 7, MAX_F = 3030;

int n, m, ub, dp[2][MAX_N][MAX_F], ftot, fac[int(1e6) + 200], mat[MAX_N][MAX_N], idsys[int(1e6) + 200];

int main()
{
    scanf("%d%d%d", &n, &m, &ub);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &mat[i][j]);
    for (int i = 1; i <= ub; i++)
        fac[i] = (ub + i - 1) / i;
    reverse(fac + 1, fac + 1 + ub), ftot = unique(fac + 1, fac + 1 + ub) - fac - 1;
    reverse(fac + 1, fac + 1 + ftot);
    for (int i = 1; i <= ftot; i++)
        idsys[fac[i]] = i;
    dp[1][1][idsys[int((ub + mat[1][1] - 1) / mat[1][1])]] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            for (int k = 1; k <= ftot; k++)
            {
                if (j < m)
                {
                    int &ret = dp[i & 1][j + 1][idsys[int((fac[k] + mat[i][j + 1] - 1) / mat[i][j + 1])]];
                    ret = (0LL + ret + dp[i & 1][j][k]) % mod;
                }
                if (i < n)
                {
                    int &ret = dp[!(i & 1)][j][idsys[int((fac[k] + mat[i + 1][j] - 1) / mat[i + 1][j])]];
                    ret = (0LL + ret + dp[i & 1][j][k]) % mod;
                }
                if (i != n || j != m || k != ftot)
                    dp[i & 1][j][k] = 0;
            }
    printf("%d\n", dp[n & 1][m][ftot]);
    return 0;
}