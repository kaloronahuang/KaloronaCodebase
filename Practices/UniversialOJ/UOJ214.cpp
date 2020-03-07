// UOJ214.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 32, MAX_M = 14, mod = 998244353;

int T, n, m, song[MAX_N], skill_tot, pre_inv[10001];
bool skill[300][300];
char str[MAX_N];

int fpow(int bas, int tim)
{
    int ret = 1;
    while (tim)
    {
        if (tim & 1)
            ret = 1LL * ret * bas % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ret;
}

namespace Subtask1
{

int need[MAX_N][26];

void subtask1Handler()
{
    int ans = 0;
    bool valid = false;
    for (int i = 0; i < (1 << (n - m + 1)); i++)
    {
        memset(need, 0, sizeof(need));
        bool tag = true;
        int cnt = 0;
        for (int j = 0; j < n - m + 1; j++)
            if (i & (1 << j))
                for (int k = 0; k < m; k++)
                {
                    if (skill[j + k][str[k]] == false)
                        tag = false;
                    need[j + k][str[k] - 'a'] = true;
                }
        if (i && tag)
            valid = true;
        else
            continue;
        for (int j = 0; j < n; j++)
            for (int k = 0; k < 26; k++)
                cnt += need[j][k];
        int tmp = 1LL * skill_tot * pre_inv[cnt] % mod;
        if (~__builtin_popcount(i) & 1)
            tmp = mod - tmp;
        if (__builtin_popcount(i) & 1)
            ans = (0LL + ans + 1LL * skill_tot * pre_inv[cnt] % mod) % mod;
        else
            ans = (0LL + ans + mod - 1LL * skill_tot * pre_inv[cnt] % mod) % mod;
    }
    if (!valid)
        puts("-1");
    else
        printf("%d\n", ans);
}

} // namespace Subtask1

namespace Subtask2
{

int f[MAX_N][1 << 14 | 1], dp[2][MAX_N * 26 + 10][1 << 14 | 1];

void subtask2Handler()
{
    memset(f, 0, sizeof(f)), memset(dp, 0, sizeof(dp));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < (1 << m); j++)
        {
            int prod = 0;
            bool flag = true;
            for (int k = 0; k < m; k++)
            {
                if (!skill[i + k][str[k]])
                {
                    flag = false;
                    break;
                }
                bool tag = true;
                for (int l = 0; l < m; l++)
                    if (j & (1 << l))
                        if (k + l < m && str[k + l + 1] == str[k])
                        {
                            tag = false;
                            break;
                        }
                if (tag)
                    prod++;
            }
            if (!flag)
                f[i][j] = -1;
            else
                f[i][j] = prod;
        }
    dp[0][0][0] = -1;
    bool valid = false;
    int rd = 1;
    for (int i = 0; i + m <= n; i++)
    {
        memset(dp[rd], 0, sizeof(dp[rd]));
        for (int j = 0; j <= n * 26; j++)
            for (int k = 0; k < (1 << m); k++)
            {
                if (dp[rd ^ 1][j][k] == 0)
                    continue;
                int lesson = f[i][k], dst = ((k & ((1 << (m - 1)) - 1)) << 1);
                dp[rd][j][dst] = (0LL + dp[rd][j][dst] + dp[rd ^ 1][j][k]) % mod;
                if (f[i][k] == -1)
                    continue;
                int tmp = mod - dp[rd ^ 1][j][k];
                dp[rd][j + lesson][dst ^ 1] = (0LL + dp[rd][j + lesson][dst ^ 1] + tmp) % mod;
                valid = true;
            }
        rd ^= 1;
    }
    if (!valid)
        return (void)(puts("-1"));
    int ans = 0;
    for (int j = 0; j <= n * 26; j++)
        for (int stat = 0; stat < (1 << m); stat++)
            if (dp[rd ^ 1][j][stat])
                ans = (0LL + ans + 1LL * pre_inv[j] * dp[rd ^ 1][j][stat] % mod) % mod;
    printf("%lld\n", 1LL * ans * skill_tot % mod);
}

} // namespace Subtask2

int main()
{
    scanf("%d", &T);
    for (int i = 1; i < 10001; i++)
        pre_inv[i] = (0LL + pre_inv[i - 1] + fpow(i, mod - 2)) % mod;
    while (T--)
    {
        memset(skill, false, sizeof(skill));
        scanf("%d%d", &n, &m), skill_tot = 0;
        for (int i = 0; i < n; i++)
        {
            scanf("%s", str);
            for (int j = 0; str[j]; j++)
                skill[i][str[j]] = true, skill_tot++;
        }
        scanf("%s", str);
        if (m <= 13)
            Subtask2::subtask2Handler();
        else
            Subtask1::subtask1Handler();
    }
    return 0;
}