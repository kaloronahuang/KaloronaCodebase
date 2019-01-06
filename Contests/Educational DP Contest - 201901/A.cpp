// A.cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cmath>
#define ll long long
using namespace std;
const int INF = 0x3f3f3f3f, MX_N = 1e5 + 200;
ll n, arr[MX_N], dp[MX_N];
int main()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &arr[i]);
    dp[2] = abs(arr[2] - arr[1]);
    for (int i = 3; i <= n; i++)
        dp[i] = min(dp[i - 1] + abs(arr[i - 1] - arr[i]), dp[i - 2] + abs(arr[i] - arr[i - 2]));
    printf("%lld", dp[n]);
    return 0;
}