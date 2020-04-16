// P3577.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e4 + 200, MAX_M = 2.5e4 + 200, INF = 0x3f3f3f3f, MAX_STAT = 1 << 15;

int n, m, head[MAX_N], current, ci[MAX_N], pow3[MAX_N], ans, dp[15][MAX_STAT], dep[MAX_N];
bool vis[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_M << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u)
{
    vis[u] = true;
    int d = dep[u];
    if (d == 0)
        dp[0][0] = ci[u], dp[0][1] = 0, dp[0][2] = INF;
    else
    {
        vector<int> ds;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (vis[edges[i].to] && dep[edges[i].to] < d)
                ds.push_back(dep[edges[i].to]);
        for (int stat = 0; stat < pow3[d + 1]; stat++)
            dp[d][stat] = INF;
        for (int stat = 0; stat < pow3[d]; stat++)
        {
            int dst = stat, place = 1;
            for (int x : ds)
                if ((stat / pow3[x]) % 3 == 0)
                    place = 2;
                else if ((stat / pow3[x]) % 3 == 1)
                    dst += pow3[x];
            dp[d][stat + place * pow3[d]] = min(dp[d][stat + place * pow3[d]], dp[d - 1][stat]);
            dp[d][dst] = min(dp[d][dst], dp[d - 1][stat] + ci[u]);
        }
    }
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (!vis[edges[i].to])
        {
            dep[edges[i].to] = dep[u] + 1, dfs(edges[i].to);
            for (int stat = 0; stat < pow3[d + 1]; stat++)
            dp[d][stat] = min(dp[d + 1][stat], dp[d + 1][stat + 2 * pow3[d + 1]]);
        }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = pow3[0] = 1; i <= n; i++)
        scanf("%d", &ci[i]);
    for (int i = 1; i <= 13; i++)
        pow3[i] = pow3[i - 1] * 3;
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    for (int root = 1; root <= n; root++)
        if (!vis[root])
            dfs(root), ans += min(dp[0][0], dp[0][2]);
    printf("%d\n", ans);
    return 0;
}