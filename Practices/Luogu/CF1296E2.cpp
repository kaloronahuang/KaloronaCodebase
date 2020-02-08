// CF1296E2.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, dp[MAX_N], max_len[26], ans;
char str[MAX_N];

int main()
{
    scanf("%d%s", &n, str + 1);
    for (int i = n; i >= 1; i--)
    {
        ans = max(dp[i] = max_len[str[i] - 'a'] + 1, ans);
        for (int c = str[i] - 'a' + 1; c < 26; c++)
            max_len[c] = max(max_len[c], dp[i]);
    }
    printf("%d\n", ans);
    for (int i = 1; i <= n; i++)
        printf("%d ", dp[i]);
    putchar('\n');
    return 0;
}