// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 330, mod = 998244353;

int threshold, len, n, pre[MAX_N], dp[MAX_N][MAX_N][MAX_N], units[MAX_N];
char str[MAX_N];

int main()
{
    scanf("%s%d", str + 1, &threshold), len = strlen(str + 1);
    int last_pos = 0, ones = 0;
    for (int i = 1; i <= len; i++)
        ones += str[i] == '1';
    for (int i = 1; i <= len + 1; i++)
        if (str[i] != '1')
            units[++n] = i - last_pos - 1, last_pos = i;
    for (int i = 1; i <= n; i++)
        pre[i] = pre[i - 1] + units[i];
    dp[0][0][0] = 1, threshold = min(threshold, ones);
    for (int i = 0; i < n; i++)
        for (int j = pre[i]; j <= pre[n]; j++)
            for (int k = 0; k <= threshold; k++)
                if (dp[i][j][k])
                {
                    for (int g = max(j, pre[i + 1]); g <= pre[n]; g++)
                        if (k + g - j - units[i + 1] <= threshold)
                        {
                            if (i + 1 == n && g - j > units[i + 1])
                                break;
                            int cost = g - j <= units[i + 1] ? 0 : g - j - units[i + 1];
                            dp[i + 1][g][k + cost] = (0LL + dp[i + 1][g][k + cost] + dp[i][j][k]) % mod;
                        }
                }
    int ans = 0;
    for (int i = 0; i <= threshold; i++)
        ans = (0LL + ans + dp[n][ones][i]) % mod;
    printf("%d\n", ans);
    return 0;
}