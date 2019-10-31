// P3423.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3020;

int n, bi[MAX_N], ci[MAX_N], space[MAX_N], id[MAX_N], value[MAX_N], tot, ans[MAX_N], dp[MAX_N * 10];
int limit;
bitset<30300> stat[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &bi[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ci[i]), id[i] = i;
    for (int i = 1; i <= n; i++)
    {
        int remain = ci[i], p = 1;
        while (p < remain)
        {
            space[++tot] = bi[i] * p, value[tot] = p, id[tot] = i;
            remain -= p, p <<= 1;
        }
        if (remain)
            space[++tot] = bi[i] * remain, value[tot] = remain, id[tot] = i;
    }
    scanf("%d", &limit);
    memset(dp, 0x3f, sizeof(dp)), dp[0] = 0;
    for (int i = 1; i <= tot; i++)
        for (int j = limit; j >= space[i]; j--)
            if (dp[j] > dp[j - space[i]] + value[i])
                stat[i][j] = true, dp[j] = dp[j - space[i]] + value[i];
    printf("%d\n", dp[limit]);
    int curt = limit;
    for (int i = tot; i >= 1; i--)
        if (stat[i][curt])
            curt -= space[i], ans[id[i]] += value[i];
    for (int i = 1; i <= n; i++)
        printf("%d ", ans[i]);
    return 0;
}