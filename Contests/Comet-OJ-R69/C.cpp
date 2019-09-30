// C.cpp
#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int MAX_N = 2e5 + 200;

int head[MAX_N], current, n, son[MAX_N], son_weight[MAX_N];
ll f[MAX_N], d[MAX_N], dp[MAX_N][2], pre[MAX_N], succ[MAX_N], up[MAX_N], g[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void clear()
{
    memset(f, 0, sizeof(f)), memset(d, 0, sizeof(d)), memset(dp, 0, sizeof(dp));
    memset(pre, 0, sizeof(pre)), memset(succ, 0, sizeof(succ)), memset(up, 0, sizeof(up));
    memset(g, 0, sizeof(g)), memset(son, 0, sizeof(son)), memset(son_weight, 0, sizeof(son_weight));
}

void addpath(int src, int dst, int weight)
{
    edges[current].nxt = head[src], edges[current].to = dst;
    edges[current].weight = weight, head[src] = current++;
}

void dfs1(int u, int fa)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dfs1(edges[i].to, u);
            f[u] = max(d[edges[i].to] + d[u] + edges[i].weight, f[u]);
            d[u] = max(d[u], d[edges[i].to] + edges[i].weight);
            f[u] = max(f[u], f[edges[i].to]);
        }
}

void dfs2(int u, int fa)
{
    int cnt = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            son[++cnt] = edges[i].to, son_weight[cnt] = edges[i].weight;
    pre[0] = 0, succ[cnt + 1] = 0;
    for (int i = 1; i <= cnt; i++)
        pre[i] = max(pre[i - 1], d[son[i]] + son_weight[i]);
    for (int i = cnt; i >= 1; i--)
        succ[i] = max(succ[i + 1], d[son[i]] + son_weight[i]);

    ll mx = -1e13;
    for (int i = 1; i <= cnt; i++)
    {
        up[son[i]] = max(up[son[i]], up[u] + son_weight[i]);
        up[son[i]] = max(up[son[i]], max(pre[i - 1], succ[i + 1]) + son_weight[i]);
        g[son[i]] = max(g[son[i]], g[u]);
        g[son[i]] = max(g[son[i]], pre[i - 1] + succ[i + 1]);
        g[son[i]] = max(g[son[i]], max(pre[i - 1], succ[i + 1]) + up[u]);
        g[son[i]] = max(g[son[i]], mx);
        mx = max(mx, f[son[i]]);
    }
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs2(edges[i].to, u);
}

int main()
{
    ll ans = 0;
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1, x, y, z; i <= n - 1; i++)
        scanf("%d%d%d", &x, &y, &z), addpath(x, y, z), addpath(y, x, z);
    dfs1(1, 0), dfs2(1, 0);
    for (int i = 1; i <= n; i++)
        ans = max(ans, 1LL * f[i] * g[i]);
    clear();
    for (int i = 0; i < current; i++)
        edges[i].weight = -edges[i].weight;
    dfs1(1, 0), dfs2(1, 0);
    for (int i = 1; i <= n; i++)
        ans = max(ans, 1LL * f[i] * g[i]);
    printf("%lld", ans);
    return 0;
}