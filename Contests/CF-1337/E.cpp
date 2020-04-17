// E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3030, mod = 998244353;

int n, m, dp[MAX_N][MAX_N];
char S[MAX_N], T[MAX_N];

int main()
{
    scanf("%s%s", S + 1, T + 1);
    n = strlen(S + 1), m = strlen(T + 1);
    for (int i = 1; i <= n + 1; i++)
        dp[i][i - 1] = 1;
    for (int i = 1, len = 1; i <= n; i++, len++)
        for (int l = 1; l + len - 1 <= n; l++)
        {
            if (l > m || S[i] == T[l])
                dp[l][l + len - 1] = (0LL + dp[l][l + len - 1] + dp[l + 1][l + len - 1]) % mod;
            if (l + len - 1 > m || S[i] == T[l + len - 1])
                dp[l][l + len - 1] = (0LL + dp[l][l + len - 1] + dp[l][l + len - 2]) % mod;
        }
    int ans = 0;
    for (int i = m; i <= n; i++)
        ans = (0LL + ans + dp[1][i]) % mod;
    printf("%d\n", ans);
    return 0;
}