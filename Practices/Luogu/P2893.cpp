// P2893.cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#define ll long long
using namespace std;
const int MX_N = 2020;
ll N, arr[MX_N], level[MX_N], dp[MX_N][MX_N], m;
ll doDp()
{
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 0; i <= m; i++)
        dp[0][i] = 0;
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= m; j++)
            dp[i][j] = min(dp[i][j - 1], dp[i - 1][j] + abs(arr[i] - level[j]));
    return dp[N][m];
}
int main()
{
    scanf("%lld", &N);
    for (int i = 1; i <= N; i++)
        scanf("%lld", &arr[i]), level[i] = arr[i];
    sort(level + 1, level + 1 + N);
    m = unique(level + 1, level + 1 + N) - level - 1;
    ll ans = doDp();
    reverse(arr + 1, arr + N + 1);
    printf("%lld", min(ans, doDp()));
    return 0;
}