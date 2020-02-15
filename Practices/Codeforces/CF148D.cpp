// CF148D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2020;

int n, W, B;
double dp[MAX_N][MAX_N];

int main()
{
    scanf("%d%d", &W, &B), n = W + B;
    dp[0][0] = 1;
    double ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= min(W, (i >> 1)); j++)
        {
            int rem = n - i - (i >> 1), remWhite = W - j, remBlack = rem - remWhite;
            if (rem <= 0 || remWhite < 0 || remBlack < 0)
                continue;
            if ((i + 1) & 1)
            {
                // A's turn;
                // ans += dp[i][j] *
                ans += dp[i][j] * double(remWhite) / double(rem);
                dp[i + 1][j] += dp[i][j] * double(remBlack) / double(rem);
            }
            else if (rem > 1)
            {
                if (remBlack > 0 && remWhite > 0)
                    dp[i + 1][j + 1] += dp[i][j] * double(remBlack) / double(rem) * double(remWhite) / double(rem - 1);
                if (remBlack > 1)
                    dp[i + 1][j] += dp[i][j] * double(remBlack) / double(rem) * double(remBlack - 1) / double(rem - 1);
            }
        }
    printf("%.10lf\n", ans);
    return 0;
}