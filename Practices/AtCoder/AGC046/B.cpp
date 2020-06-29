// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3030, mod = 998244353;

int n, m, a, b, dp[MAX_N][MAX_N];

int main()
{
    scanf("%d%d%d%d", &a, &b, &n, &m);
    dp[a][b] = 1;
    for (int i = a; i <= n; i++)
        for (int j = b; j <= m; j++)
            if (i != a || j != b)
                dp[i][j] = (0LL + 1LL * dp[i - 1][j] * j % mod + 1LL * dp[i][j - 1] * i % mod + mod - 1LL * dp[i - 1][j - 1] * (i - 1) % mod * (j - 1) % mod) % mod;
    printf("%d\n", dp[n][m]);
    return 0;
}