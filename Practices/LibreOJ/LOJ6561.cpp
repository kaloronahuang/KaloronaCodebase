// LOJ6561.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010, MAX_Q = 2e5 + 200;

int n, m, q, dp[MAX_N][MAX_N], ui[MAX_Q], vi[MAX_Q];
bool ans[MAX_Q];

struct query
{
    int l, r, s, t, id;
    bool operator<(const query &rhs) const { return l < rhs.l; }
} queries[MAX_Q];

int main()
{
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= m; i++)
        scanf("%d%d", &ui[i], &vi[i]);
    for (int i = 1; i <= q; i++)
        scanf("%d%d%d%d", &queries[i].l, &queries[i].r, &queries[i].s, &queries[i].t), queries[i].id = i;
    sort(queries + 1, queries + 1 + q);
    memset(dp, 0x3f, sizeof(dp));
    int ptr = q;
    for (int i = m; i >= 1; i--)
    {
        dp[ui[i]][vi[i]] = dp[vi[i]][ui[i]] = i;
        for (int j = 1; j <= n; j++)
            dp[ui[i]][j] = min(dp[ui[i]][j], dp[vi[i]][j]), dp[vi[i]][j] = min(dp[vi[i]][j], dp[ui[i]][j]);
        while (ptr >= 1 && queries[ptr].l == i)
            ans[queries[ptr].id] = dp[queries[ptr].s][queries[ptr].t] <= queries[ptr].r, ptr--;
    }
    for (int i = 1; i <= q; i++)
        if (ans[i])
            puts("Yes");
        else
            puts("No");
    return 0;
}