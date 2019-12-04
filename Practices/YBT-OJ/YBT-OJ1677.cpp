// YBT-OJ1677.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110;

int n, m, d1[MAX_N], d2[MAX_N], dp[MAX_N];

bool check(int mid)
{
    memset(dp, 128, sizeof(dp));
    dp[0] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = m; j >= 0; j--)
            for (int k = 0; k <= min(mid / d1[i], j); k++)
                dp[j] = max(dp[j], dp[j - k] + (mid - k * d1[i]) / d2[i]);
    return dp[m] >= m;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &d1[i], &d2[i]);
    int l = 0, r = 1e9, ans = 0;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
            r = mid - 1, ans = mid;
        else
            l = mid + 1;
    }
    printf("%d\n", ans);
    return 0;
}