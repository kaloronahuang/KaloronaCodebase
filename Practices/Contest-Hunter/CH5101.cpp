// CH5101.cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int MX_N = 3010;
int n, seqa[MX_N], seqb[MX_N], dp[MX_N][MX_N];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seqa[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seqb[i]);
    seqa[0] = seqb[0] = -2e9;
    for (int i = 1; i <= n; i++)
    {
        int val = 0;
        if (seqb[0] < seqa[i])
            val = dp[i - 1][0];
        for (int j = 1; j <= n; j++)
        {
            if (seqa[i] == seqb[j])
                dp[i][j] = max(dp[i][j], val + 1);
            else
                dp[i][j] = dp[i - 1][j];
            if (seqb[j] < seqa[i])
                val = max(val, dp[i - 1][j]);
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans = max(ans, dp[n][i]);
    printf("%d", ans);
    return 0;
}