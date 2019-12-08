// CF1264D1.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2020, mod = 998244353;

char str[MAX_N];
int prefixQ[MAX_N], n, dp[MAX_N][MAX_N], pow2[MAX_N];

int main()
{
    scanf("%s", str + 1), n = strlen(str + 1);
    for (int i = pow2[0] = 1; i <= n; i++)
        prefixQ[i] = prefixQ[i - 1] + (str[i] == '?'), pow2[i] = 2LL * pow2[i - 1] % mod;
    for (int len = 2; len <= n; len++)
        for (int i = 1; i + len - 1 <= n; i++)
        {
            int j = i + len - 1;
            if (str[i] != '(')
                dp[i][j] = (1LL * dp[i][j] + 1LL * dp[i + 1][j]) % mod;
            if (str[j] != ')')
                dp[i][j] = (1LL * dp[i][j] + 1LL * dp[i][j - 1]) % mod;
            if (str[i] != '(' && str[j] != ')')
                dp[i][j] = (1LL * dp[i][j] - 1LL * dp[i + 1][j - 1] + mod) % mod;
            if (str[i] != ')' && str[j] != '(')
                dp[i][j] = (1LL * dp[i][j] + 1LL * dp[i + 1][j - 1] + pow2[prefixQ[j - 1] - prefixQ[i]]) % mod;
        }
    printf("%d\n", dp[1][n]);
    return 0;
}