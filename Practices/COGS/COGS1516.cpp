// COGS1516.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

vector<int> stats[21];
ll n, dp[1 << 21];

int main()
{
    freopen("rook.in", "r", stdin);
    freopen("rook.out", "w", stdout);
    scanf("%lld", &n);
    for (int stat = 0; stat < (1 << n); stat++)
        stats[__builtin_popcount(stat)].push_back(stat);
    dp[0] = 1;
    for (int cnt = 0; cnt < n; cnt++)
        for (vector<int>::iterator it = stats[cnt].begin(); it != stats[cnt].end(); it++)
        {
            int stat = *it;
            for (int j = 0; j < n; j++)
                if ((stat & (1 << j)) == 0)
                    dp[stat | (1 << j)] += dp[stat];
        }
    printf("%lld", dp[(1 << n) - 1]);
    return 0;
}