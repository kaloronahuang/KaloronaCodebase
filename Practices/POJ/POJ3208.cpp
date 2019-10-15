// POJ3208.cpp
#include <cstdio>
#include <algorithm>
#define ll long long

using namespace std;

ll dp[10][5], T, n;

void preprocess()
{
    dp[0][0] = 1;
    for (int i = 1; i <= 10; i++)
    {
        dp[i][0] = (dp[i - 1][0] + dp[i - 1][1] + dp[i - 1][2]) * 9;
        dp[i][1] = dp[i - 1][0];
        dp[i][2] = dp[i - 1][1];
        dp[i][3] = dp[i - 1][3] * 10 + dp[i - 1][2];
    }
}

int main()
{
    preprocess(), scanf("%lld", &T);
    while (T--)
    {
        scanf("%lld", &n);
        int pos = 0;
        for (pos = 3; dp[pos][3] < n; pos++)
            ;
        for (int i = pos, k = 0; i >= 1; i--)
            for (int j = 0; j <= 9; j++)
            {
                ll cnt = dp[i - 1][3];
                if (j == 6 || k == 3)
                    for (int h = max(3 - (j == 6) - k, 0); h < 3; h++)
                        cnt += dp[i - 1][h];
                if (cnt < n)
                    n -= cnt;
                else
                {
                    if (k < 3)
                        if (j == 6)
                            k++;
                        else
                            k = 0;
                    printf("%d", j);
                    break;
                }
            }
        puts("");
    }
    return 0;
}