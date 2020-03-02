// LOJ3092.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110, MAX_M = 2e4 + 200;

int s, n, m, ai[MAX_N][MAX_N], dp[MAX_M];

int main()
{
    scanf("%d%d%d", &s, &n, &m);
    for (int i = 1; i <= s; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", &ai[j][i]);
    for (int i = 1; i <= n; i++)
        sort(ai[i] + 1, ai[i] + 1 + s);
    for (int i = 1; i <= n; i++)
        for (int j = m; j >= 1; j--)
            for (int k = 0; k <= s; k++)
                if (ai[i][k] * 2 < j)
                    dp[j] = max(dp[j], dp[j - ai[i][k] * 2 - 1] + i * k);
                else
                    break;
    printf("%d\n", dp[m]);
    return 0;
}