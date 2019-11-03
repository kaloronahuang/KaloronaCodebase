// CF1245C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, mod = 1e9 + 7;

int n, dp[MAX_N][2], ans;
char str[MAX_N];

int main()
{
    scanf("%s", str + 1), n = strlen(str + 1);
    dp[1][0] = 1, dp[2][1] = 1, dp[2][0] = 1;
    for (int i = 3; i <= n; i++)
        dp[i][0] = (dp[i - 1][0] + dp[i - 1][1]) % mod, dp[i][1] = (dp[i - 2][0] + dp[i - 2][1]) % mod;
    for (int i = 1; i <= n; i++)
        if (str[i] == 'w' || str[i] == 'm')
            puts("0"), exit(0);
    ans = 1;
    for (int i = 1, last_pos = 0; i <= n + 1; i++)
        if (str[i - 1] != str[i])
        {
            if (str[i - 1] == 'u' || str[i - 1] == 'n')
            {
                //printf("%d %d %d\n", i - last_pos, dp[i - last_pos][0], dp[i - last_pos][1]);
                ans = 1LL * ans * (1LL * dp[i - last_pos][0] + 1LL * dp[i - last_pos][1]) % mod;
            }
            last_pos = i;
        }
    printf("%d", ans);
    return 0;
}