// COGS111.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e6 + 200;

int L, S, T, M, dp[MAX_N], pos[MAX_N], dist[MAX_N];
bool vis[MAX_N];

int main()
{
    freopen("river.in", "r", stdin);
    freopen("river.out", "w", stdout);
    scanf("%d%d%d%d", &L, &S, &T, &M);
    for (int i = 1; i <= M; i++)
        scanf("%d", &pos[i]);
    sort(pos + 1, pos + 1 + M);
    memset(dp, 0x3f, sizeof(dp)), dp[0] = 0;
    int last = 0;
    for (int i = 1; i <= M; i++)
        dist[i] = (pos[i] - pos[i - 1]) % 2520 + dist[i - 1];
    dist[M + 1] = (L - pos[M]) % 2520 + dist[M], M++;
    for (int i = 0; i <= M; i++)
        vis[dist[i]] = true;
    for (int i = S; i <= dist[M] + T; i++)
        for (int j = S; j <= T && i - j >= 0; j++)
            dp[i] = min(dp[i - j] + (vis[i] == true), dp[i]);
    int ans = 0x3f3f3f3f;
    for (int i = dist[M]; i <= dist[M] + T; i++)
        ans = min(ans, dp[i]);
    printf("%d", ans);
    return 0;
}