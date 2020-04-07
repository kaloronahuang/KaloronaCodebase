// LOJ2496.cpp
#pragma GCC optimize(2)
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, mod = 998244353;

typedef pair<int, int> pii;

int n, m, head[MAX_N], current, dfn[MAX_N], ptot, upper, dp[MAX_N][2];
vector<pii> vec, org;

struct edge
{
    int to, nxt;
    bool tag;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u, int fa)
{
    dfn[u] = ++ptot;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            if (dfn[edges[i].to] == 0)
                org.push_back(make_pair(u, edges[i].to)), dfs(edges[i].to, u);
            else if (dfn[edges[i].to] < dfn[u])
                vec.push_back(make_pair(u, edges[i].to));
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dfs(1, 0), upper = vec.size();
    int ans = 0;
    for (int stat = 0; stat < (1 << upper); stat++)
    {
        for (int i = 1; i <= n; i++)
            dp[i][0] = dp[i][1] = 1;
        for (int i = 0; i < upper; i++)
            if (stat & (1 << i))
                dp[vec[i].first][1] = dp[vec[i].second][0] = 0;
            else
                dp[vec[i].second][1] = 0;
        bool flag = true;
        for (int i = 1; i <= n && flag; i++)
            if (dp[i][0] == 0 && dp[i][1] == 0)
                flag = false;
        if (flag)
        {
            for (int i = n - 1; i >= 1; i--)
            {
                int u = org[i - 1].first, v = org[i - 1].second;
                dp[u][0] = 1LL * dp[u][0] * (0LL + dp[v][0] + dp[v][1]) % mod;
                dp[u][1] = 1LL * dp[u][1] * dp[v][0] % mod;
            }
            ans = (0LL + ans + dp[1][0] + dp[1][1]) % mod;
        }
    }
    printf("%d\n", ans);
    return 0;
}