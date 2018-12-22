// P4267.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n, arr[120], dp[120][120];
int differ(int st, int ed)
{
    int cnt = 0;
    for (int i = st; i <= ed; i++)
        if (arr[i] != i - st)
            cnt++;
    return cnt;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &arr[i]);
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 0; i <= n; i++)
        dp[0][i] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++)
            for (int k = i; k >= j; k--)
                dp[i][j] = min(dp[i][j], dp[k - 1][j - 1] + differ(k, i));
    for (int i = 1; i <= n; i++)
        printf("%d\n", dp[n][i]);
    return 0;
}