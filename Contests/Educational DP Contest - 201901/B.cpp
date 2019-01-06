// A.cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cmath>
#define ll long long
using namespace std;
const int INF = 0x3f3f3f3f, MX_N = 1e5 + 200;
ll n, arr[MX_N], dp[MX_N], K;
int main()
{
    scanf("%lld%lld", &n, &K);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &arr[i]);
    memset(dp, INF, sizeof(dp));
    dp[1] = 0;
    for (int i = 2; i <= n; i++)
        for (int j = i - 1; j >= 1 && i - j <= K; j--)
            dp[i] = min(dp[i], dp[j] + abs(arr[i] - arr[j]));
    printf("%lld", dp[n]);
    return 0;
}