// P1436.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#define ll long long
using namespace std;
ll n, presum[10][10], map[10][10], ans, dp[20][20][20][20][20];
struct rect
{
    int x1, x2, y1, y2;
};
ll sum(int i, int j, int a, int b)
{
    return presum[a][b] - presum[i - 1][b] - presum[a][j - 1] + presum[i - 1][j - 1];
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= 8; i++)
        for (int j = 1; j <= 8; j++)
        {
            scanf("%d", &map[i][j]);
            presum[i][j] = presum[i - 1][j] + presum[i][j - 1] - presum[i - 1][j - 1] + map[i][j];
        }
    for (int i = 1; i <= 8; i++)
        for (int j = 1; j <= 8; j++)
            for (int a = i; a <= 8; a++)
                for (int b = j; b <= 8; b++)
                    dp[i][j][a][b][0] = sum(i, j, a, b) * sum(i, j, a, b);
    for (int k = 1; k < n; k++)
        for (int i = 1; i <= 8; i++)
            for (int j = 1; j <= 8; j++)
                for (int a = i; a <= 8; a++)
                    for (int b = j; b <= 8; b++)
                    {
                        ll minval = (1LL << 61LL);
                        for (int hor = j; hor < b; hor++)
                            minval = min(minval, min(dp[i][j][a][hor][k - 1] + dp[i][hor + 1][a][b][0],
                                                     dp[i][j][a][hor][0] + dp[i][hor + 1][a][b][k - 1]));
                        for (int ver = i; ver < a; ver++)
                            minval = min(minval, min(dp[i][j][ver][b][k - 1] + dp[ver + 1][j][a][b][0],
                                                     dp[i][j][ver][b][0] + dp[ver + 1][j][a][b][k - 1]));
                        dp[i][j][a][b][k] = minval;
                    }
    printf("%lld", dp[1][1][8][8][n - 1]);
    return 0;
}