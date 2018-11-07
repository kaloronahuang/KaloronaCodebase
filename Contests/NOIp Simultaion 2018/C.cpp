// C.cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
#define ll long long
const int maxn = 1010;
const int maxm = 120;
ll dp[maxn][maxm];
ll arr[maxn];
ll pre[maxn][maxn];
ll n, m;

void genDP()
{
    for (int i = 1; i <= n; i++)
        pre[i][i] = arr[i];
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            pre[i][j] = pre[i][j - 1] ^ arr[j];
    for (int i = 2; i <= n; i++)
        for (int k = 2; k <= min(m, (ll)i); k++)
            for (int mid = 1; mid < i; mid++)
            {
                ll sum = pre[mid + 1][i];
                dp[i][k] = max(dp[i][k], dp[mid][k - 1] + sum);
            }
}

int main()
{
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &arr[i]), dp[i][1] = dp[i - 1][1] ^ arr[i];
    genDP();
    printf("%lld", dp[n][m]);
    return 0;
}