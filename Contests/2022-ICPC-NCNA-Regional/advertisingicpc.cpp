// D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 10, _I = 0, _C = 1, _P = 2, mod = 998244353, MAX_THREE = 6561;
const char mpc[3] = {'I', 'C', 'P'};

int n, m, dp[MAX_N][MAX_THREE][2], upper;
char mp[MAX_N][MAX_N], tmp[2][MAX_N];
bool mat[MAX_THREE][MAX_THREE];
vector<int> stats[MAX_THREE];

void decode(int x, char *c)
{
    for (int i = m - 1; i >= 0; i--)
        c[i] = mpc[x % 3], x /= 3;
}

int main()
{
    scanf("%d%d", &n, &m);
    upper = 1;
    for (int i = 0; i < n; i++)
        scanf("%s", mp[i]);
    for (int i = 1; i <= m; i++)
        upper *= 3;
    for (int i = 0; i < upper; i++)
    {
        decode(i, tmp[0]);
        for (int j = 0; j < upper; j++)
        {
            decode(j, tmp[1]);
            for (int p = 0; p < m - 1; p++)
                mat[i][j] |= (tmp[0][p] == 'P' && tmp[0][p + 1] == 'C' && tmp[1][p] == 'I' && tmp[1][p + 1] == 'C');
            if (mat[i][j])
                stats[i].push_back(j);
        }
    }
    int sum[2] = {0, 0};
    for (int stat = 0; stat < upper; stat++)
    {
        decode(stat, tmp[0]);
        bool broken = false;
        for (int j = 0; j < m && (!broken); j++)
            if (mp[0][j] != '?' && mp[0][j] != tmp[0][j])
                broken = true;
        if (broken)
            continue;
        dp[0][stat][0] = 1, dp[0][stat][1] = 0;
        sum[0] = (0LL + sum[0] + 1) % mod;
    }
    for (int i = 1; i < n; i++)
    {
        int psum[2] = {0, 0};
        for (int stat = 0; stat < upper; stat++)
        {
            decode(stat, tmp[0]);
            bool broken = false;
            for (int j = 0; j < m && (!broken); j++)
                if (mp[i][j] != '?' && mp[i][j] != tmp[0][j])
                    broken = true;
            if (broken)
                continue;
            dp[i][stat][0] = sum[0];
            dp[i][stat][1] = sum[1];
            for (int v : stats[stat])
            {
                dp[i][stat][0] = (0LL + dp[i][stat][0] + mod - dp[i - 1][v][0]) % mod;
                dp[i][stat][1] = (0LL + dp[i][stat][1] + dp[i - 1][v][0]) % mod;
            }
            psum[0] = (0LL + psum[0] + dp[i][stat][0]) % mod;
            psum[1] = (0LL + psum[1] + dp[i][stat][1]) % mod;
        }
        sum[0] = psum[0];
        sum[1] = psum[1];
    }
    printf("%d\n", sum[1]);
    return 0;
}
