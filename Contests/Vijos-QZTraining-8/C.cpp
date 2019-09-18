// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1005;

double dp[MAX_N][MAX_N];
int n, m;

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        dp[i][0] = i;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            dp[i][j] = max(0.0, i / double(i + j) * (dp[i - 1][j] + 1) + j / double(i + j) * (dp[i][j - 1] - 1));
    printf("%.8lf\n", dp[n][m]);
    return 0;
}