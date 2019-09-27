// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5100;

int n, m, seq1[MAX_N], seq2[MAX_N], dp[MAX_N][MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq1[i]);
    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
        scanf("%d", &seq2[i]);
    for (int i = 1; i <= n; i++)
    {
        int tmp = 0;
        for (int j = 1; j <= m; j++)
        {
            dp[i][j] = dp[i - 1][j];
            if (seq1[i] > seq2[j])
                tmp = max(tmp, dp[i - 1][j]);
            if (seq1[i] == seq2[j])
                dp[i][j] = tmp + 1;
        }
    }
    int ans = 0;
    for (int i = 0; i <= m; i++)
        ans = max(ans, dp[n][i]);
    printf("%d", ans);
    return 0;
}