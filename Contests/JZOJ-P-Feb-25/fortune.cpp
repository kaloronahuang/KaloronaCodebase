// fortune.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 88;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int task, T, n, xi[MAX_N], yi[MAX_N], zi[MAX_N];
ll dp[MAX_N][MAX_N][MAX_N * MAX_N], ans;

void fileIO()
{
    freopen("fortune.in", "r", stdin);
    freopen("fortune.out", "w", stdout);
}

int S, bird;
ll val;

void dfs(int pos)
{
    if (pos == n + 1)
        return (void)(ans = max(ans, val));
    S += bird;
    val += xi[pos] + S, dfs(pos + 1), val -= xi[pos] + S;
    S += yi[pos], dfs(pos + 1), S -= yi[pos];
    bird += zi[pos], dfs(pos + 1), bird -= zi[pos];
    S -= bird;
}

int main()
{
    scanf("%d%d", &task, &T);
    while (T--)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d%d%d", &xi[i], &yi[i], &zi[i]);
        for (int i = 1; i <= n + 1; i++)
            for (int j = 0; j <= n; j++)
                for (int k = 0; k <= n * n; k++)
                    dp[i][j][k] = -INF;
        dp[n + 1][0][0] = 0;
        for (int i = n; i >= 1; i--)
            for (int j = 1; j <= n - i + 1; j++)
                for (int k = j * i; k <= 1LL * n * n; k++)
                {
                    dp[i][j][k] = -INF;
                    if (dp[i + 1][j][k] != -INF)
                        dp[i][j][k] = max(dp[i + 1][j][k] + 1LL * j * yi[i], dp[i + 1][j][k] + 1LL * zi[i] * (k - j * i));
                    if (dp[i + 1][j - 1][k - i] != -INF)
                        dp[i][j][k] = max(dp[i][j][k], dp[i + 1][j - 1][k - i] + xi[i]);
                    continue;
                }
        ll ans = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 0; j <= i * n; j++)
                ans = max(ans, dp[1][i][j]);
        printf("%lld\n", ans);
    }
    return 0;
}