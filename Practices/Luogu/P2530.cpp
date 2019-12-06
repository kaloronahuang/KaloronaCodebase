// P2530.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110;

int n, dp[MAX_N][12][12][12];
char opt[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        cin >> opt[i];
    memset(dp, 0x3f, sizeof(dp)), dp[0][0][0][0] = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int a = 0; a <= 10; a++)
            for (int b = 0; b <= 10; b++)
                if (a + b <= 10)
                    for (int c = 0; c <= 10; c++)
                        if (a + b + c <= 10)
                        {
                            if (a > 0 && opt[i] == 'A')
                                dp[i][a][b][c] = min(dp[i][a][b][c], dp[i - 1][a - 1][b][c]);
                            if (b > 0 && opt[i] == 'B')
                                dp[i][a][b][c] = min(dp[i][a][b][c], dp[i - 1][a][b - 1][c]);
                            if (c > 0 && opt[i] == 'C')
                                dp[i][a][b][c] = min(dp[i][a][b][c], dp[i - 1][a][b][c - 1]);
                            dp[i][0][b][c] = min(dp[i][0][b][c], dp[i][a][b][c] + 1);
                            dp[i][a][0][c] = min(dp[i][a][0][c], dp[i][a][b][c] + 1);
                            dp[i][a][b][0] = min(dp[i][a][b][0], dp[i][a][b][c] + 1);
                        }
    }
    printf("%d\n", dp[n][0][0][0]);
    return 0;
}