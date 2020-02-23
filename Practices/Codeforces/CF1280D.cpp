// CF1280D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3030;

typedef long long ll;

int T, head[MAX_N], current, n, m, val[MAX_N], siz[MAX_N];
pair<int, ll> dp[MAX_N][MAX_N], tmp[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u, int fa)
{
    siz[u] = 1, dp[u][1] = make_pair(0, val[u]);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dfs(edges[i].to, u);
            for (int a = 1; a <= siz[u] + siz[edges[i].to]; a++)
                tmp[a] = make_pair(-1, 0);
            for (int a = 1; a <= siz[u]; a++)
                for (int b = 1; b <= siz[edges[i].to]; b++)
                {
                    tmp[a + b] = max(tmp[a + b], make_pair(dp[u][a].first + dp[edges[i].to][b].first + (dp[edges[i].to][b].second > 0), dp[u][a].second));
                    tmp[a + b - 1] = max(tmp[a + b - 1], make_pair(dp[u][a].first + dp[edges[i].to][b].first, dp[u][a].second + dp[edges[i].to][b].second));
                }
            for (int a = 1; a <= siz[u] + siz[edges[i].to]; a++)
                dp[u][a] = tmp[a];
            siz[u] += siz[edges[i].to];
        }
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        memset(dp, 0, sizeof(dp));
        memset(head, -1, sizeof(head)), current = 0;
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++)
            scanf("%d", &val[i]), val[i] = -val[i];
        for (int i = 1, v; i <= n; i++)
            scanf("%d", &v), val[i] += v;
        for (int i = 1, u, v; i <= n - 1; i++)
            scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
        dfs(1, 0);
        printf("%d\n", dp[1][m].first + (dp[1][m].second > 0));
    }
    return 0;
}