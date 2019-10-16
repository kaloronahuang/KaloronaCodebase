// P2467.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int dp[2][MAX_N], n, p;

int main()
{
    scanf("%d%d", &n, &p);
    dp[0][2] = 1;
    for (int i = 3; i <= n; i++)
        for (int j = 2; j <= i; j++)
            dp[i & 1][j] = (1LL * dp[i & 1][j - 1] + 1LL * dp[(i - 1) & 1][i - j + 1]) % p;
    int ans = 0;
    for (int i = 2; i <= n; i++)
        ans = (1LL * ans + 1LL * dp[n & 1][i]) % p;
    printf("%d", (ans << 1) % p);
    return 0;
}