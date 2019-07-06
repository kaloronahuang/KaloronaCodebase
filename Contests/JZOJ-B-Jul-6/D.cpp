// D.cpp
#include <bits/stdc++.h>

const int MAX_N = 17;

using namespace std;

int n, ai[MAX_N], dp[MAX_N * 20], ans = -1;
bool flag[(1 << MAX_N)];

void dfs(int dep, int statA, int lenA, int statB, int lenB)
{
    if (dep == n)
    {
        if (flag[statA] && flag[statB])
            ans = max(ans, (lenA * lenB) / 4);
        return;
    }
    dfs(dep + 1, statA, lenA, statB, lenB);
    dfs(dep + 1, statA | (1 << dep), lenA + ai[dep + 1], statB, lenB);
    dfs(dep + 1, statA, lenA, statB | (1 << dep), lenB + ai[dep + 1]);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    for (int stat = 1; stat < (1 << n); stat++)
    {
        int sum = 0;
        for (int i = 1; i <= n; i++)
            if ((stat >> (i - 1)) & 1)
                sum += ai[i];
        if (sum & 1)
            continue;
        memset(dp, 0, sizeof(dp));
        dp[0] = 1;
        for (int i = 1; i <= n; i++)
            if ((stat >> (i - 1)) & 1)
                for (int k = sum; k >= ai[i]; k--)
                    dp[k] |= dp[k - ai[i]];
        if (dp[sum >> 1])
            flag[stat] = true;
    }
    dfs(0, 0, 0, 0, 0);
    if (ans > 0)
        printf("%d", ans);
    else
        puts("No Solution");
    return 0;
}