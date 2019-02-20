// CH5301.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 1010;
int n, arr[MAX_N], dp[MAX_N][MAX_N], sum[MAX_N];
int main()
{
    scanf("%d", &n);
    memset(dp, 0x7f, sizeof(dp));
    for (int i = 1; i <= n; i++)
        scanf("%d", &arr[i]), dp[i][i] = 0, sum[i] = sum[i - 1] + arr[i];
    for (int len = 2; len <= n; len++)
        for (int i = 1; i + len - 1 <= n; i++)
        {
            int j = i + len - 1;
            for (int k = i; k < j; k++)
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
            dp[i][j] += sum[j] - sum[i - 1];
        }
    printf("%d", dp[1][n]);
    return 0;
}