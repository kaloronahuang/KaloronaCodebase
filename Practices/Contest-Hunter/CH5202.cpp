// CH5202.cpp
#include <iostream>
#include <cstdio>
#define ll long long
using namespace std;
ll dp[4020], n;
int main()
{
    scanf("%lld", &n);
    dp[0] = 1;
    for (ll i = 1; i < n; i++)
        for (ll j = i; j <= n; j++)
            dp[j] = (dp[j] + dp[j - i]) % 2147483648;
    printf("%d", dp[n]);
    return 0;
}