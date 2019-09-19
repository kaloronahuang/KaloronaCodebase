// A.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 550, mod = 998244353;

ll dp[MAX_N][MAX_N];
int n, k;

int main()
{
    freopen("melee.in", "r", stdin);
    freopen("melee.out", "w", stdout);
    scanf("%d%d", &n, &k);
    for (int i = 0; i <= n; i++)
        dp[0][i] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < i; j++)
            for (int w = 0; w <= n; w++)
                dp[i][w + 1] = (1LL * dp[i][w + 1] + 1LL * dp[j][w] * dp[i - j - 1][w] % mod) % mod;
    ll ans = dp[n][n] - dp[n][k - 1];
    while (ans < 0)
        ans += mod;
    printf("%lld", ans);
    return 0;
}