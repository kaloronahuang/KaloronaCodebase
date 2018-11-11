// M.cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int maxn = 810;
#define ll long long
int a[maxn];
int b[maxn];
ll dp[maxn][maxn];
int n;

ll gcd(ll a, ll b)
{
    if (a < b)
        return gcd(b, a);
    return (b == 0) ? a : gcd(b, a % b);
}

void genDP()
{
    for (int i = 1; i < n; i++)
        dp[i][i + 1] = (gcd(a[i], a[i + 1]) == 1) ? 0 : b[i] + b[i + 1];
    for (int len = 3; len <= n; len++)
        for (int i = 1; i + len - 1 <= n; i++)
        {
            int j = i + len - 1;
            for (int k = i; k < j; k++)
                dp[i][j] = max(dp[i][j], dp[i][k] + dp[k][j]);
        }
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &b[i]);
    genDP();
    ll ans = 0;
    ans = max(ans, dp[1][n]);
    cout << ans;
    return 0;
}