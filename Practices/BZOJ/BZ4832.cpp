// BZ4832.cpp
#include <bits/stdc++.h>

using namespace std;

int T, n;
double dp[55][9][9][9];

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        memset(dp, 0, sizeof(dp));
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            for (int a = 0; a <= 7; a++)
                for (int b = 0; a + b <= 7; b++)
                    for (int c = 0; a + b + c <= 7; c++)
                    {
                        double &src = dp[i][a][b][c];
                        int tot = a + b + c + 1;
                        if (a + b + c < 7)
                            src += 1.0 * c / tot * dp[i - 1][a][b + 1][c] + (b >= 1 ? 1.0 * b / tot * dp[i - 1][a + 1][b - 1][c + 1] : 0);
                        else
                            src += (c >= 1 ? 1.0 * c / tot * dp[i - 1][a][b + 1][c - 1] : 0) + (b >= 1 ? 1.0 * b / tot * dp[i - 1][a + 1][b - 1][c] : 0);
                        if (a > 0)
                            src += 1.0 * a / tot * dp[i - 1][a - 1][b][c];
                        src += 1.0 / tot * (dp[i - 1][a][b][c] + 1);
                    }
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        printf("%.2lf\n", dp[n][a][b][c]);
    }
    return 0;
}