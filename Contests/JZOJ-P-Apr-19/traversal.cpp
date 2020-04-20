// traversal.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

typedef long long ll;

int n, siz[MAX_N], head[MAX_N], current, wi[MAX_N], tot;
ll dp[MAX_N], g[MAX_N];
char name[20];
bool tag[MAX_N];

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
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        dfs(edges[i].to, u), siz[u] += siz[edges[i].to];
        dp[u] += dp[edges[i].to] + 1LL * siz[edges[i].to] * wi[edges[i].to] + siz[edges[i].to] - (tag[edges[i].to] == true);
    }
}

void collect(int u, int fa)
{
    if (fa != 0)
        g[u] = g[fa] + dp[fa] - dp[u] - 1LL * siz[u] * wi[u] - (siz[u] - (tag[u] == true)) + ((tot - siz[u]) * 3LL);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        collect(edges[i].to, u);
}

void fileIO(string src)
{
    freopen((src + ".in").c_str(), "r", stdin);
    freopen((src + ".out").c_str(), "w", stdout);
}

int main()
{
    fileIO("traversal");
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1, m, val; i <= n; i++)
    {
        scanf("%s%d", name, &m), wi[i] = strlen(name);
        if (m == 0)
            siz[i] = 1, tag[i] = true, tot++;
        else
            while (m--)
                scanf("%d", &val), addpath(i, val);
    }
    dfs(1, 0), collect(1, 0);
    ll ans = 2e18;
    for (int i = 1; i <= n; i++)
        ans = min(ans, dp[i] + g[i]);
    printf("%lld\n", ans);
    return 0;
}