// BZ3864.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1002, mod = 1e9 + 7;

int T, n, m, dp[2][1 << 15], org[MAX_N], trans[1 << 15][4], tmp[20], target[20], ansBox[20];
char str[MAX_N];

int main()
{
    // freopen("1.in", "r", stdin);
    scanf("%d", &T);
    while (T--)
    {
        scanf("%s%d", str + 1, &m), n = strlen(str + 1);
        for (int i = 1; i <= n; i++)
            if (str[i] == 'A')
                org[i] = 0;
            else if (str[i] == 'C')
                org[i] = 1;
            else if (str[i] == 'T')
                org[i] = 2;
            else
                org[i] = 3;
        memset(dp, 0, sizeof(dp)), dp[0][0] = 1;
        for (int stat = 0; stat < (1 << n); stat++)
            for (int c = 0; c < 4; c++)
            {
                for (int i = 1; i <= n; i++)
                    tmp[i] = (stat >> (i - 1)) & 1;
                for (int i = 1; i <= n; i++)
                    tmp[i] += tmp[i - 1];
                for (int i = 1; i <= n; i++)
                    if (org[i] == c)
                        target[i] = max(tmp[i - 1] + 1, tmp[i]);
                    else
                        target[i] = max(tmp[i], target[i - 1]);
                int nxt = 0;
                for (int i = 1; i <= n; i++)
                    nxt |= ((target[i] - target[i - 1]) << (i - 1));
                trans[stat][c] = nxt;
            }
        for (int i = 1; i <= m; i++)
        {
            memset(dp[i & 1], 0, sizeof(dp[i & 1]));
            for (int stat = 0; stat < (1 << n); stat++)
                if (dp[(i - 1) & 1][stat])
                    for (int c = 0; c < 4; c++)
                        dp[i & 1][trans[stat][c]] = (0LL + dp[i & 1][trans[stat][c]] + dp[(i - 1) & 1][stat]) % mod;
        }
        memset(ansBox, 0, sizeof(ansBox));
        for (int stat = 0; stat < (1 << n); stat++)
            ansBox[__builtin_popcount(stat)] = (0LL + ansBox[__builtin_popcount(stat)] + dp[m & 1][stat]) % mod;
        for (int i = 0; i <= n; i++)
            printf("%d\n", ansBox[i]);
    }
    return 0;
}