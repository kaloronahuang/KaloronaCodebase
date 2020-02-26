// CF1314B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 18, MAX_M = (1 << MAX_N);

int n, team, f[MAX_M], nxt[MAX_M], dp[2][MAX_N][MAX_N];

void goNxt(int l, int r, int dep)
{
    int mid = (l + r) >> 1;
    nxt[mid] = dep;
    if (l != r)
        goNxt(l, mid - 1, dep + 1), goNxt(mid + 1, r, dep + 1);
}

int main()
{
    scanf("%d%d", &n, &team);
    if (team == 0)
        puts("0"), exit(0);
    int total = (1 << n);
    for (int i = 1, val; i <= team; i++)
        scanf("%d", &val), f[val] = 1;
    if (n >= 3)
        goNxt(1, (1 << (n - 2)) - 1, 1);
    int ans = 1;
    for (int i = 1; i <= total; i += 2)
        ans += (f[i] || f[i + 1]);
    int opt = 0;
    for (int p = 1, q = 1; p <= total; p += 4, q++, opt = 1 - opt)
    {
        memset(dp[opt], 0, sizeof(dp[opt]));
        int acc = f[p] + f[p + 1] + f[p + 2] + f[p + 3];
        for (int i = 0; i <= n - 1; i++)
            for (int j = 0; j <= n - 1; j++)
                if (acc >= 2)
                    dp[opt][nxt[q]][nxt[q]] = max(dp[opt][nxt[q]][nxt[q]], dp[opt ^ 1][i][j] + (n - i - 1) + 2 * (n - 1 - j));
                else if (acc == 1)
                {
                    dp[opt][nxt[q]][min(j, nxt[q])] = max(dp[opt][nxt[q]][min(j, nxt[q])], dp[opt ^ 1][i][j] + (n - 1 - i));
                    dp[opt][min(nxt[q], i)][nxt[q]] = max(dp[opt][min(nxt[q], i)][nxt[q]], dp[opt ^ 1][i][j] + 2 * (n - 1 - j));
                }
                else
                    dp[opt][min(nxt[q], i)][min(nxt[q], j)] = max(dp[opt][min(nxt[q], i)][min(nxt[q], j)], dp[opt ^ 1][i][j]);
    }
    printf("%d\n", ans + dp[opt ^ 1][0][0]);
    return 0;
}