// P2679.cpp
#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
long long n, m, k, dp[220][220], prefix[220][220];
char A[2020], B[2020];
int main()
{
    scanf("%lld%lld%lld%s%s", &n, &m, &k, A, B), dp[0][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = m; j >= 1; j--)
            for (int h = k; h >= 1; h--)
                dp[j][h] = (1LL * dp[j][h] + (prefix[j][h] = (A[i - 1] == B[j - 1] ? 1LL * prefix[j - 1][h] + 1LL * dp[j - 1][h - 1] : 0)) % mod) % mod;
    printf("%lld", dp[m][k]);
    return 0;
}