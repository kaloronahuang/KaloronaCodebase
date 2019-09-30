// COGS1749.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4020, MAX_E = 21000;

int n, m, wi[MAX_N], ci[MAX_N], tot, wi_tmp[MAX_N], ci_tmp[MAX_N], idx[MAX_N];
int dp[MAX_E], bucket[MAX_N];

int main()
{
    
    freopen("pay.in", "r", stdin);
    freopen("pay.out", "w", stdout);
    
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &wi_tmp[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ci_tmp[i]);
    scanf("%d", &m);
    for (int i = 1; i <= n; i++)
    {
        int now = 1;
        while (ci_tmp[i] >= now)
        {
            wi[++tot] = wi_tmp[i] * now, idx[tot] = i;
            ci[tot] = now, ci_tmp[i] -= now, now <<= 1;
        }
        if (ci_tmp[i])
        {
            wi[++tot] = wi_tmp[i] * ci_tmp[i];
            ci[tot] = ci_tmp[i], idx[tot] = i;
        }
    }
    memset(dp, 0x3f, sizeof(dp)), dp[0] = 0;
    for (int i = 1; i <= tot; i++)
        for (int j = m; j >= 0; j--)
            if (j >= wi[i] && dp[j] > dp[j - wi[i]] + ci[i])
                dp[j] = dp[j - wi[i]] + ci[i];
    int cur = m;
    while (cur > 0)
        for (int i = tot; i >= 1; i--)
            if (cur >= wi[i] && dp[cur] == dp[cur - wi[i]] + ci[i])
                cur -= wi[i], bucket[idx[i]] += ci[i];
    printf("%d\n", dp[m]);
    for (int i = 1; i <= n; i++)
        printf("%d ", bucket[i]);
    return 0;
}