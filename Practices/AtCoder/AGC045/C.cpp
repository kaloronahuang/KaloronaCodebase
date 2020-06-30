// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5050, mod = 1e9 + 7;

int n, A, B, bin[MAX_N], dp[MAX_N][MAX_N], f[MAX_N][MAX_N], pre[MAX_N];

int main()
{
    scanf("%d%d%d", &n, &A, &B);
    for (int i = bin[0] = 1; i <= n; i++)
        bin[i] = 2LL * bin[i - 1] % mod;
    if (A < B)
        swap(A, B);
    dp[0][0] = 1;
    for (int i = 0; i <= n; i++)
    {
        if (i != 0)
            pre[i] = (0LL + pre[i] + pre[i - 1]) % mod;
        dp[i][1] = (0LL + dp[i][1] + pre[i]) % mod;
        for (int j = 1; j <= A; j++)
        {
            dp[i][j] = (0LL + dp[i][j] + f[i][j]) % mod;
            f[i + 1][min(j + 1, A)] = (0LL + f[i + 1][min(j + 1, A)] + f[i][j]) % mod;
        }
        if (i == n)
            break;
        for (int j = 0; j <= A - 1; j++)
        {
            dp[i + 1][j + 1] = (0LL + dp[i + 1][j + 1] + dp[i][j]) % mod;
            pre[i + 2] = (0LL + pre[i + 2] + dp[i][j]) % mod;
            if (i + B + 1 <= n)
            {
                pre[i + B + 1] = (0LL + pre[i + B + 1] + mod - dp[i][j]) % mod;
                f[i + B + 1][min(j + B + 1, A)] = (0LL + f[i + B + 1][min(j + B + 1, A)] + dp[i][j]) % mod;
            }
            if (n - i >= B)
                dp[n][min(j + n - i, A)] = (0LL + dp[n][min(j + n - i, A)] + dp[i][j]) % mod;
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans = (0LL + ans + 1LL * dp[i][A] * bin[n - i] % mod) % mod;
    printf("%d\n", ans);
    return 0;
}