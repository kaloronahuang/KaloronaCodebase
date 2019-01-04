// B.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#define ripe(num) num % 180
using namespace std;
const int MX_N = 20;
int n, arr[MX_N];
bool dp[MX_N][400];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &arr[i]);
    dp[0][0] = true;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= 360; j++)
        {
            // positive;
            int deg = j + arr[i];
            if (deg == 360 || deg == 0)
                dp[i][0] |= dp[i - 1][j], dp[i][360] |= dp[i - 1][j];
            else
                deg %= 360, dp[i][deg] |= dp[i - 1][j];
            deg = j - arr[i];
            if (deg == 360 || deg == 0)
                dp[i][0] |= dp[i - 1][j], dp[i][360] |= dp[i - 1][j];
            else
            {
                while (deg < 0)
                    deg += 360;
                deg %= 360, dp[i][deg] |= dp[i - 1][j];
            }
        }
    printf(dp[n][0] || dp[n][360] ? "YES" : "NO");
    return 0;
}