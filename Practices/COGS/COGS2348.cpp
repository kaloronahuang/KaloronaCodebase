// COGS2348.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 17;

ll dp[1 << MAX_N][MAX_N];
int n, k, si[MAX_N];
vector<int> stats[MAX_N];

int main()
{
    freopen("mengbi.in", "r", stdin);
    freopen("mengbi.out", "w", stdout);
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &si[i]);
    for (int i = 1; i < (1 << n); i++)
        stats[__builtin_popcount(i)].push_back(i);
    for (int i = 0; i < n; i++)
        dp[1 << i][i + 1] = 1;
    for (int bits = 2; bits <= n; bits++)
    {
        for (int idx = 0, tmp = stats[bits].size(); idx < tmp; idx++)
        {
            int stat = stats[bits][idx];
            for (int i = 1; i <= n; i++)
                if (stat & (1 << (i - 1)))
                    // as a tail;
                    for (int j = 1; j <= n; j++)
                        if (i != j && (stat & (1 << (j - 1))) && abs(si[i] - si[j]) > k)
                            dp[stat][i] += dp[stat ^ (1 << (i - 1))][j];
        }
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++)
        ans += dp[(1 << n) - 1][i];
    printf("%lld", ans);
    return 0;
}