// bag1.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 330;

int n, h, fi[MAX_N], di[MAX_N], ti[MAX_N], dp[MAX_N][MAX_N], prefix[MAX_N];

int main()
{
    freopen("bag1.in", "r", stdin);
    freopen("bag1.out", "w", stdout);
    scanf("%d%d", &n, &h), h *= 12;
    for (int i = 1; i <= n; i++)
        scanf("%d", &fi[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &di[i]);
    for (int i = 1; i <= n - 1; i++)
        scanf("%d", &ti[i]), prefix[i + 1] = prefix[i] + ti[i];
    for (int i = 0; i <= h; i++)
        for (int j = 1; prefix[j] <= i && j <= n; j++)
            for (int k = 1, acc = fi[j], idx = fi[j]; k + ti[j - 1] <= i; k++, idx -= di[j], acc += max(idx, 0))
                dp[i][j] = max(dp[i][j], dp[i - k - ti[j - 1]][j - 1] + acc);
    printf("%d", dp[h][n]);
    return 0;
}