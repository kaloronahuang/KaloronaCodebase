// B.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 550, dx[4] = {0, 0, -1, 1}, dy[4] = {-1, 1, 0, 0};

int n, pi[MAX_N * MAX_N], dist[MAX_N * MAX_N], idx[MAX_N][MAX_N];
int ptot, xi[MAX_N * MAX_N], yi[MAX_N * MAX_N], rem[MAX_N * MAX_N];

void dfs(int u)
{
    for (int d = 0; d < 4; d++)
    {
        int dstx = xi[u] + dx[d], dsty = yi[u] + dy[d];
        int nd = dist[u] + 1 - rem[idx[dstx][dsty]];
        if (dist[idx[dstx][dsty]] > nd)
            dist[idx[dstx][dsty]] = nd, dfs(idx[dstx][dsty]);
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n * n; i++)
        scanf("%d", &pi[i]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            idx[i][j] = ++ptot, xi[ptot] = i, yi[ptot] = j;
            dist[ptot] = min(min(n - i + 1, i), min(n - j + 1, j));
        }
    int ans = 0;
    for (int i = 1; i <= n * n; i++)
    {
        int u = pi[i];
        ans += dist[u] - 1, rem[u] = 1;
        for (int d = 0; d < 4; d++)
        {
            int dstx = xi[u] + dx[d], dsty = yi[u] + dy[d];
            dist[u] = min(dist[idx[dstx][dsty]], dist[u]);
        }
        dfs(idx[xi[u]][yi[u]]);
    }
    printf("%d\n", ans);
    return 0;
}