// CH0103.cpp
#include <cstdio>
#include <cstring>
#define min(x, y) (x < y) ? x : y
const int maxn = 20;
int n, weight[maxn][maxn], dp[1 << maxn][maxn];
int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &weight[i][j]);
    memset(dp, 0x7f, sizeof dp);
    dp[1][0] = 0;
    for (int i = 0; i < (1 << n); i++)
        for (int id = 1; id < n; id++)
            if (i & (1 << id))
                for (int mid = 0; mid < n; mid++)
                    if (i & (1 << mid))
                        dp[i][id] = min(dp[i][id], dp[i ^ (1 << id)][mid] + weight[id][mid]);
    printf("%d", dp[(1 << n) - 1][n - 1]);
    return 0;
}