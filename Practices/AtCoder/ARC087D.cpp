// ARC087D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 8580;

int X, Y;
bool dp[2][MAX_N << 1];
char S[MAX_N];
vector<int> vecs[2];

int main()
{
    scanf("%s%d%d", S + 1, &X, &Y);
    int opt = 0, acc = 0;
    bool flag = true;
    for (int i = 1; S[i]; i++)
        if (S[i] == 'F')
            acc++;
        else if (flag)
            X -= acc, flag = false, opt ^= 1, acc = 0;
        else
            vecs[opt].push_back(acc), opt ^= 1, acc = 0;
    if (acc > 0)
        vecs[opt].push_back(acc);
    if (flag)
    {
        puts((acc == X) ? "Yes" : "No");
        return 0;
    }
    bool ans = true;
    int cb = 0;
    dp[0][MAX_N] = true;
    for (int x : vecs[0])
    {
        cb ^= 1, memset(dp[cb], 0, sizeof(dp[cb]));
        for (int i = 2 * MAX_N - 1; i >= 0; i--)
        {
            if (i - x >= 0)
                dp[cb][i] |= dp[!cb][i - x];
            if (i + x < 2 * MAX_N)
                dp[cb][i] |= dp[!cb][i + x];
        }
    }
    ans &= dp[cb][X + MAX_N];
    memset(dp, 0, sizeof(dp));
    cb = 0, dp[0][MAX_N] = true;
    for (int x : vecs[1])
    {
        cb ^= 1, memset(dp[cb], 0, sizeof(dp[cb]));
        for (int i = 2 * MAX_N - 1; i >= 0; i--)
        {
            if (i - x >= 0)
                dp[cb][i] |= dp[!cb][i - x];
            if (i + x < 2 * MAX_N)
                dp[cb][i] |= dp[!cb][i + x];
        }
    }
    ans &= dp[cb][Y + MAX_N];
    puts(ans ? "Yes" : "No");
    return 0;
}