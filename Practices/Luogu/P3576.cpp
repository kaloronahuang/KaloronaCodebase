// P3576.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e6 + 200;

int head[MAX_N], current, n, m, k, deg[MAX_N], ptx, pty;
ll min_rg[MAX_N], max_rg[MAX_N], fa[MAX_N], gi[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa[u])
            fa[edges[i].to] = u, deg[u]++;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa[u])
        {
            min_rg[edges[i].to] = min_rg[u] * deg[u];
            max_rg[edges[i].to] = (max_rg[u] + 1) * deg[u] - 1;
            max_rg[edges[i].to] = min(max_rg[edges[i].to], gi[m]);
            if (min_rg[edges[i].to] <= gi[m])
                dfs(edges[i].to);
        }
}

ll binary_find(ll limit)
{
    int l = 1, r = m, ans = 0;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (gi[mid] < limit)
            ans = max(ans, mid), l = mid + 1;
        else
            r = mid - 1;
    }
    return ans;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= m; i++)
        scanf("%lld", &gi[i]);
    scanf("%d%d", &ptx, &pty);
    for (int i = 1, u, v; i <= n - 2; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    sort(gi + 1, gi + 1 + m);
    min_rg[ptx] = max_rg[ptx] = min_rg[pty] = max_rg[pty] = k;
    dfs(ptx), dfs(pty);
    ll ans = 0;
    for (int i = 1; i <= n; i++)
        if (deg[i] == 0)
            ans += binary_find(max_rg[i] + 1) - binary_find(min_rg[i]);
    printf("%lld", ans * k);
    return 0;
}
