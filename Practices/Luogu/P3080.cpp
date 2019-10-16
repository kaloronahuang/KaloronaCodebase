// P3080.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010;

int n, pt[MAX_N], dp[MAX_N][MAX_N][2];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &pt[i]);
    sort(pt + 1, pt + 1 + n);
    int pos = lower_bound(pt + 1, pt + 1 + n, 0) - pt;
    for (int i = n; i >= pos; i--)
        pt[i + 1] = pt[i];
    pt[pos] = 0, memset(dp, 0x3f, sizeof(dp)), dp[pos][pos][0] = dp[pos][pos][1] = 0;
    for (int len = 2; len <= n + 1; len++)
        for (int i = 1; i + len - 1 <= n + 1; i++)
        {
            int j = i + len - 1;
            dp[i][j][0] = min(dp[i + 1][j][0] + abs(pt[i] - pt[i + 1]) * (n - (j - (i + 1))), dp[i + 1][j][1] + abs(pt[i] - pt[j]) * (n - (j - (i + 1))));
            dp[i][j][1] = min(dp[i][j - 1][1] + abs(pt[j] - pt[j - 1]) * (n - (j - (i + 1))), dp[i][j - 1][0] + abs(pt[i] - pt[j]) * (n - (j - (i + 1))));
        }
    printf("%d\n", min(dp[1][n + 1][1], dp[1][n + 1][0]));
    return 0;
}