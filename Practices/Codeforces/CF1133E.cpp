// CF1133E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5050;

int n, k, ai[MAX_N], dp[2][MAX_N];

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    sort(ai + 1, ai + 1 + n);
    for (int i = 1; i <= k; i++)
    {
        for (int j = 1, ptr = 1, max_val = 0; j <= n; j++)
        {
            while (ai[j] - ai[ptr] > 5)
                max_val = max(max_val, dp[!(i & 1)][ptr]), ptr++;
            dp[i & 1][j] = max_val + j - ptr + 1;
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans = max(ans, dp[k & 1][i]);
    printf("%d\n", ans);
    return 0;
}