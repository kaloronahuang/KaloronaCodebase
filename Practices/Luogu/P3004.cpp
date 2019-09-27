// P3004.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 5001;

int dp[2][MAX_N], n, ci[MAX_N], sum[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ci[i]);
    for (int i = 1; i <= n; i++)
        dp[1 & 1][i] = ci[i], sum[i] = sum[i - 1] + ci[i];
    for (int len = 2; len <= n; len++)
        for (int i = 1; i + len - 1 <= n; i++)
        {
            int j = i + len - 1;
            dp[len & 1][i] = sum[j] - sum[i - 1] - min(dp[(len - 1) & 1][i], dp[(len - 1) & 1][i + 1]);
        }
    printf("%d\n", dp[n & 1][1]);
    return 0;
}