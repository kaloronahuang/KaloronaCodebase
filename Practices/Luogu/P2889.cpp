// P2889.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010;

struct interval
{
    int l, r, val;
    bool operator<(const interval &it) const { return r < it.r || (r == it.r && l < it.l); }
} nodes[MAX_N];

int dp[MAX_N], n, m, R;

int main()
{
    scanf("%d%d%d", &n, &m, &R);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &nodes[i].l, &nodes[i].r, &nodes[i].val);
    sort(nodes + 1, nodes + 1 + m);
    for (int i = 1; i <= m; i++)
    {
        dp[i] = max(dp[i - 1], nodes[i].val);
        for (int j = 1; j < i; j++)
            if (nodes[j].r + R <= nodes[i].l)
                dp[i] = max(dp[i], max(dp[j] + nodes[i].val, dp[j]));
    }
    printf("%d", dp[m]);
    return 0;
}