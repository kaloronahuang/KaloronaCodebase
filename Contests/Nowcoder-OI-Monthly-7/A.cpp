// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int org[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6}, MAX_N = 5e7 + 200;

int n, k, dp[MAX_N];

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 0; i < 10; i++)
        dp[i] = org[i];
    for (int i = 10; i < MAX_N; i++)
        dp[i] = dp[i / 10] + org[i % 10];
    int stk = n / k - 4 - dp[n], ans = 0;
    for (int i = 0; i <= n; i++)
        if (stk == dp[i] + dp[n - i])
            ans++;
    printf("%d", ans >> 1);
    return 0;
}