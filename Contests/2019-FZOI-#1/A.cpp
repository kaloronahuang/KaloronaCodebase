// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5050;

int n, m, seq[MAX_N << 1], ub, n_, suffix_true[MAX_N << 1][MAX_N], suffix_false[MAX_N << 1][MAX_N];
bool dp[MAX_N << 1][MAX_N];

int main()
{
    scanf("%d%d%d", &n, &m, &ub);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i]);
    for (int i = n + 1; i <= n + m; i++)
        seq[i] = seq[i - n];
    n_ = n, n += m;
    for (int i = 1; i <= n; i++)
        dp[i][m] = false;
    for (int i = 1; i <= m - 1; i++)
        dp[n][i] = true;
    for (int i = 1; i <= n; i++)
        for (int j = m; j >= 1; j--)
        {
            suffix_true[i][j] = suffix_true[i][j + 1] + (dp[i][j] == true);
            suffix_false[i][j] = suffix_false[i][j + 1] + (dp[i][j] == false);
        }
    for (int i = n - 1; i >= 1; i--)
        for (int j = m - 1; j >= 1; j--)
        {
            dp[i][j] = false;
            if (seq[i + 1] == seq[i])
                dp[i][j] = (suffix_true[i + 1][j + 1] - suffix_true[i + 1][min(j + ub - 1, m - 1) + 2] > 0);
            else
                dp[i][j] = (suffix_false[i + 1][j + 1] - suffix_false[i + 1][min(j + ub - 1, m - 1) + 2] > 0);
            suffix_true[i][j] = suffix_true[i][j + 1] + (dp[i][j] == true);
            suffix_false[i][j] = suffix_false[i][j + 1] + (dp[i][j] == false);
            continue;
        }
    for (int i = 1; i <= n_; i++)
        if (seq[i] == 1)
            printf("%d ", dp[i][1] == true);
        else
            printf("%d ", dp[i][1] == false);
    return 0;
}