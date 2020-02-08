// CF632E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1100;

int n, k, dp[MAX_N * MAX_N], ai[MAX_N], bi[MAX_N];

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    sort(ai + 1, ai + 1 + n);
    for (int i = 1; i <= n; i++)
        bi[i] = ai[i] - ai[1];
    memset(dp, 0x3f, sizeof(dp)), dp[0] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = max(bi[i], 1); j < MAX_N * MAX_N; j++)
            dp[j] = min(dp[j], dp[j - bi[i]] + 1);
    for (int i = 0; i < MAX_N * MAX_N; i++)
        if (dp[i] <= k)
            printf("%d ", k * ai[1] + i);
    putchar('\n');
    return 0;
}