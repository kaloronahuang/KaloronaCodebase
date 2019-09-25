// C.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 110, MAX_L = 20;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, m, C, T, logs[int(1e5) + 200];
ll g[MAX_L][MAX_N][MAX_N], pi[MAX_N], ci[MAX_N], A[MAX_N], B[MAX_N], dp[MAX_N][MAX_N * MAX_N];
ll mx_dist[MAX_N][MAX_N];

int main()
{
    scanf("%d%d%d%d", &n, &m, &C, &T);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            g[0][i][j] = (i == j) ? 0 : -INF;
    for (int i = 1; i <= n; i++)
        scanf("%lld%lld", &pi[i], &ci[i]);
    for (ll i = 1, x, y, d; i <= m; i++)
        scanf("%lld%lld%lld", &x, &y, &d), g[0][x][y] = max(d, g[0][x][y]);
    for (int i = 1; i < MAX_L; i++)
    {
        for (int x = 1; x <= n; x++)
            for (int y = 1; y <= n; y++)
                g[i][x][y] = -INF;
        for (int k = 1; k <= n; k++)
            for (int x = 1; x <= n; x++)
                for (int y = 1; y <= n; y++)
                    g[i][x][y] = max(g[i][x][y], g[i - 1][x][k] + g[i - 1][k][y]);
    }
    logs[1] = 0;
    for (int i = 2; i <= 1e5; i++)
        logs[i] = logs[i >> 1] + 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            A[j] = (i == j) ? 0 : -INF;
        ll gallons = min(1LL * C, ci[i]);
        for (int bit = 0; bit < MAX_L; bit++)
            if (gallons & (1 << bit))
            {
                for (int j = 1, k; j <= n; j++)
                    for (k = 1, B[j] = -INF; k <= n; k++)
                        B[j] = max(B[j], A[k] + g[bit][k][j]);
                for (int j = 1; j <= n; j++)
                    A[j] = B[j];
            }
        for (int j = 1; j <= n; j++)
            mx_dist[i][j] = A[j];
    }
    for (int i = 0; i <= n * n; i++)
        for (int j = 1; j <= n; j++)
        {
            if (i < pi[j])
            {
                dp[j][i] = 0;
                continue;
            }
            dp[j][i] = -INF;
            for (int k = 1; k <= n; k++)
                dp[j][i] = max(dp[j][i], dp[k][i - pi[j]] + mx_dist[j][k]);
        }
    while (T--)
    {
        ll st, q, d;
        scanf("%lld%lld%lld", &st, &q, &d);
        if (dp[st][q] < d)
        {
            puts("-1");
            continue;
        }
        ll l = 0, r = q, ret;
        while (l <= r)
        {
            ll mid = (l + r) >> 1;
            if (dp[st][mid] >= d)
                ret = mid, r = mid - 1;
            else
                l = mid + 1;
        }
        printf("%lld\n", q - ret);
    }
    return 0;
}