// H.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
using namespace std;
const int mod = 1e9 + 7;
ll h, w, dp[1001][1001];
char map[1001][1001];
int main()
{
    scanf("%d%d", &h, &w);
    for (int i = 1; i <= h; i++)
        scanf("%s", map[i] + 1);
    dp[1][1] = 1;
    for (int i = 1; i <= h; i++)
        for (int j = 1; j <= w; j++)
        {
            if (map[i - 1][j] == '.')
                dp[i][j] = (dp[i][j] + dp[i - 1][j]) % mod;
            if (map[i][j - 1] == '.')
                dp[i][j] = (dp[i][j - 1] + dp[i][j]) % mod;
        }
    printf("%lld", dp[h][w]);
    return 0;
}