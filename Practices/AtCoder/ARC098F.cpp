// ARC098F.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

typedef long long ll;

int n, m, head[MAX_N], current, ai[MAX_N], bi[MAX_N], ci[MAX_N], id[MAX_N], rk[MAX_N], mem[MAX_N];
ll dp[MAX_N], tot[MAX_N];
vector<int> G[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int find(int x) { return mem[x] == x ? x : mem[x] = find(mem[x]); }

void dfs(int u, int fa)
{
    tot[u] = bi[u];
    for (auto son : G[u])
        dfs(son, u), tot[u] += tot[son];
}

void calc(int u, int fa)
{
    if (G[u].empty())
        return (void)(dp[u] = bi[u] + ci[u]);
    dp[u] = 1e18;
    for (auto v : G[u])
        calc(v, u), dp[u] = min(dp[u], tot[u] - tot[v] + max(1LL * ci[u], dp[v]));
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &ai[i], &bi[i]), ci[i] = max(ai[i] - bi[i], 0), id[i] = i, mem[i] = i;
    sort(id + 1, id + 1 + n, [](const int &rhs1, const int &rhs2) { return ci[rhs1] < ci[rhs2]; });
    for (int i = 1; i <= n; i++)
        rk[id[i]] = i;
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    for (int idx = 1; idx <= n; idx++)
    {
        int u = id[idx];
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (u != find(edges[i].to) && rk[u] > rk[find(edges[i].to)])
                G[u].push_back(find(edges[i].to)), mem[find(edges[i].to)] = u;
    }
    dfs(id[n], 0), calc(id[n], 0), printf("%lld\n", dp[id[n]]);
    return 0;
}