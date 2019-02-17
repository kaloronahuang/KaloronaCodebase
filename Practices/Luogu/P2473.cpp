// P2473.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 17;
int n, k, stat[MAX_N], pi[MAX_N], tmpx;
double dp[1 << MAX_N][200];
int main()
{
    scanf("%d%d", &k, &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &pi[i]);
        while (scanf("%d", &tmpx) && tmpx != 0)
            stat[i] |= (1 << (tmpx - 1));
    }
    for (int i = k; i >= 1; i--)
        for (int st = 0; st < (1 << n); st++)
        {
            for (int j = 1; j <= n; j++)

                if ((stat[j] & st) == stat[j])
                    dp[st][i] += max(dp[st][i + 1], dp[st | (1 << (j - 1))][i + 1] + pi[j]);
                else
                    dp[st][i] += dp[st][i + 1];
            dp[st][i] /= n;
        }
    printf("%.6lf", dp[0][1]);
    return 0;
}