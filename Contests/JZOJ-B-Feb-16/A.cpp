// A.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MOD = 15746, MAX_N = 1000010;
ll dp[MAX_N], n;
int main()
{
    scanf("%lld", &n);
    dp[1] = 1, dp[2] = 2;
    for (int i = 3; i <= n; i++)
        dp[i] = (dp[i - 1] + dp[i - 2]) % MOD;
    printf("%lld",dp[n]);
    return 0;
}