// FOJ4681.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 550;

int n, k, dp[MAX_N * MAX_N], ai[MAX_N], mx_range, mi;

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    sort(ai + 1, ai + 1 + n);
    mi = ai[1];
    for (int i = 1; i <= n; i++)
        ai[i] -= mi;
    mx_range = ai[n];
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        if (ai[i] == ai[i - 1])
            continue;
        for (int j = 1; j <= k * mx_range; j++)
            if (j >= ai[i])
                dp[j] = min(dp[j], dp[j - ai[i]] + 1);
    }
    for (int i = 0; i <= mx_range * k; i++)
        if (dp[i] <= k)
            printf("%d ", i + mi * k);
    return 0;
}

