// P5124.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e4 + 200;

int n, k, seq[MAX_N], dp[MAX_N];

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i]);
    for (int i = 1; i <= n; i++)
    {
        for (int j = i, mx_val = seq[i]; j >= 1 && i - j + 1 <= k; j--)
            mx_val = max(mx_val, seq[j]), dp[i] = max(dp[i], dp[j - 1] + mx_val * (i - j + 1));
    }
    printf("%d", dp[n]);
    return 0;
}