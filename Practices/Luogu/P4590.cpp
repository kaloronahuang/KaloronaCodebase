// P4590.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010, MAX_M = 15, mod = 1e9 + 7;
const int nxt_len[3][3] = {{1, 0, 0}, {1, 2, 0}, {1, 0, 3}};

int n, m, dp[2][1 << MAX_M][3], trans[1 << MAX_M][3], f[2][MAX_N], org[MAX_N], ans[MAX_N];
char str[MAX_N];

void build()
{
    for (int stat = 0; stat < (1 << m); stat++)
    {
        for (int i = 0; i < m; i++)
            f[0][i + 1] = f[0][i] + ((stat >> i) & 1);
        for (int i = 0; i < 3; i++)
        {
            // get the new stat after choosing char i;
            for (int j = 1; j <= m; j++)
            {
                f[1][j] = max(f[1][j - 1], f[0][j]);
                if (i == org[j])
                    f[1][j] = max(f[1][j], f[0][j - 1] + 1);
            }
            int nxt = 0;
            for (int j = 1; j <= m; j++)
                nxt |= (f[1][j] - f[1][j - 1]) << (j - 1);
            trans[stat][i] = nxt;
        }
    }
}

int main()
{
    scanf("%d%d%s", &n, &m, str + 1);
    for (int i = 1; i <= m; i++)
        org[i] = (str[i] == 'N' ? 0 : (str[i] == 'O' ? 1 : 2));
    build(), dp[0][0][0] = 1;
    for (int i = 1; i <= n; i++)
    {
        memset(dp[i & 1], 0, sizeof(dp[i & 1]));
        for (int j = 0; j < (1 << m); j++)
            for (int len = 0; len < 3; len++)
                for (int c = 0; c < 3; c++)
                    if (!(len == 2 && c == 2))
                        dp[i & 1][trans[j][c]][nxt_len[len][c]] = (0LL + dp[i & 1][trans[j][c]][nxt_len[len][c]] + dp[!(i & 1)][j][len]) % mod;
    }
    for (int stat = 0; stat < (1 << m); stat++)
        for (int len = 0; len < 3; len++)
            ans[__builtin_popcount(stat)] = (0LL + ans[__builtin_popcount(stat)] + dp[n & 1][stat][len]) % mod;
    for (int i = 0; i <= m; i++)
        printf("%d\n", ans[i]);
    return 0;
}