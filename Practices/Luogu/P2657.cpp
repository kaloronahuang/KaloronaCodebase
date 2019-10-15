// P2657.cpp
#include <bits/stdc++.h>

using namespace std;

int dp[15][15], digits[15];

void preprocess()
{
    for (int i = 0; i <= 9; i++)
        dp[1][i] = 1;
    for (int i = 2; i <= 10; i++)
        for (int j = 0; j <= 9; j++)
            for (int k = 0; k <= 9; k++)
                if (abs(j - k) >= 2)
                    dp[i][j] += dp[i - 1][k];
}

// Worth to be noticed;
int solve(int x)
{
    memset(digits, 0, sizeof(digits));
    int len = 0, ans = 0;
    // Split;
    while (x)
        digits[++len] = x % 10, x /= 10;
    // Find the solution numbers within (len - 1);
    for (int i = 1; i <= len - 1; i++)
        for (int j = 1; j <= 9; j++)
            ans += dp[i][j];
    // Get the sol from numbers with lower head;
    for (int i = 1; i < digits[len]; i++)
        ans += dp[len][i];
    // Get the sol from numbers with identical head;
    for (int i = len - 1; i >= 1; i--)
    {
        // we attempt to make the previous "heads" identical;
        for (int j = 0; j <= digits[i] - 1; j++)
            if (abs(j - digits[i + 1]) >= 2)
                ans += dp[i][j];
        // same prefix judge:
        if (abs(digits[i] - digits[i + 1]) < 2)
            break;
    }
    return ans;
}

int main()
{
    preprocess();
    int l, r;
    scanf("%d%d", &l, &r), printf("%d", solve(r + 1) - solve(l));
    return 0;
}