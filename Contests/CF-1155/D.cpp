// D.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAX_N = 3e5 + 2000;
ll arr[MAX_N], n, x, dp[MAX_N][3], ans;

int main()
{
    scanf("%lld%lld", &n, &x);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &arr[i]);
    for (int i = 1; i <= n; i++)
    {
        dp[i][0] = max(dp[i - 1][0] + arr[i], arr[i]);
        dp[i][1] = max(dp[i - 1][1] + arr[i] * x, dp[i - 1][0] + arr[i] * x);
        dp[i][1] = max(dp[i][1], arr[i] * x);
        dp[i][2] = max(dp[i - 1][2] + arr[i], dp[i - 1][1] + arr[i]);
        dp[i][2] = max(dp[i][2], arr[i]);
        ans = max(ans, max(dp[i][0], max(dp[i][1], dp[i][2])));
    }
    printf("%lld", ans);
    return 0;
}