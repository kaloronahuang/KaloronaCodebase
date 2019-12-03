// YBT-OJ1675.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 3030;

int n, hi[MAX_N];
ll dp[MAX_N][MAX_N], pre[MAX_N], suf[MAX_N][MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &hi[i]), pre[i] = pre[i - 1] + hi[i];
    for (int i = 1; i <= n; i++)
    {
        dp[i][0] = i - 1;
        for (int j = 1, ptr = 0; j < i; j++)
        {
            while (pre[ptr] < 2 * pre[j] - pre[i] && ptr < j)
                ptr++;
            dp[i][j] = suf[j][ptr] + i - j - 1;
        }
        suf[i][i] = 0x3f3f3f3f3f3f3f3f;
        for (int j = i - 1; j >= 0; j--)
            suf[i][j] = min(suf[i][j + 1], dp[i][j]);
    }
    ll ans = 0x3f3f3f3f3f3f3f3f;
    for (int i = 0; i < n; i++)
        ans = min(ans, dp[n][i]);
    printf("%lld\n", ans);
    return 0;
}