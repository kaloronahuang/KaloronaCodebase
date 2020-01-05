// twobit.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;
typedef pair<int, int> pii;

int n, dp[MAX_N][2];
char str[MAX_N];

int main()
{
    scanf("%d%s", &n, str + 1);
    dp[0][0] = 0, dp[0][1] = 1;
    for (int i = 1; i <= n; i++)
        if (str[i] == '0')
        {
            dp[i][0] = min(dp[i - 1][0], dp[i - 1][1] + 1);
            dp[i][1] = min(dp[i - 1][0] + 1, dp[i - 1][1] + 1);
        }
        else
        {
            dp[i][0] = min(dp[i - 1][0] + 1, dp[i - 1][1] + 1);
            dp[i][1] = dp[i - 1][1];
        }
    printf("%d\n", min(dp[n][0], dp[n][1] + 1));
    return 0;
}