// P2059.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110;

int n, m, cards[MAX_N];
double dp[MAX_N][MAX_N];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
        scanf("%d", &cards[i]);
    dp[1][1] = 1.0;
    for (int i = 2; i <= n; i++)
        for (int j = 1; j <= i; j++)
            // to choose the card and calc the pos;
            for (int k = 1; k <= m; k++)
            {
                int nxt_pos = (cards[k] % i == 0) ? i : cards[k] % i;
                if (nxt_pos > j)
                    dp[i][j] += dp[i - 1][i - nxt_pos + j] / m;
                else
                    dp[i][j] += dp[i - 1][j - nxt_pos] / m;
            }
    for (int i = 1; i <= n; i++)
        printf("%.2lf%% ", dp[n][i] * 100);
    return 0;
}