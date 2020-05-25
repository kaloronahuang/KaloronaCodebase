// P4606.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int T, n, m, q, head[MAX_N], current, dfn[MAX_N], low[MAX_N], lft[MAX_N], dist[MAX_N];
int up[18][MAX_N], ptot, stk[MAX_N], tail, ncnt, dep[MAX_N], seq[MAX_N];
bool vis[MAX_N];
vector<int> G[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].nxt = head[src], edges[current].to = dst;
    head[src] = current++;
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++ptot, stk[++tail] = u;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (dfn[edges[i].to] == 0)
        {
            tarjan(edges[i].to), low[u] = min(low[u], low[edges[i].to]);
            if (low[edges[i].to] == dfn[u])
            {
                int bcc = ++ncnt;
                for (int x = 0; x != edges[i].to; tail--)
                    x = stk[tail], G[bcc].push_back(x), G[x].push_back(bcc);
                G[bcc].push_back(u), G[u].push_back(bcc);
            }
        }
        else
            low[u] = min(low[u], dfn[edges[i].to]);
}

void dfs(int u, int fa)
{
    lft[u] = ++ptot, dep[u] = dep[fa] + 1, up[0][u] = fa;
    dist[u] = dist[fa] + (u <= n);
    for (int v : G[u])
        if (v != fa)
            dfs(v, u);
}

int getLCA(int x, int y)
{
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = 17; i >= 0; i--)
        if (dep[up[i][x]] >= dep[y])
            x = up[i][x];
    if (x == y)
        return x;
    for (int i = 17; i >= 0; i--)
        if (up[i][x] != up[i][y])
            x = up[i][x], y = up[i][y];
    return up[0][x];
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        memset(head, -1, sizeof(head)), current = 0, memset(up, 0, sizeof(up));
        scanf("%d%d", &n, &m), ptot = tail = dep[0] = 0;
        for (int i = 1; i <= ncnt; i++)
            G[i].clear(), dist[i] = dfn[i] = low[i] = dep[i] = lft[i] = 0, vis[i] = false;
        ncnt = n;
        for (int i = 1, u, v; i <= m; i++)
            scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
        tarjan(1), ptot = 0, tail--, dfs(1, 0);
        for (int i = 1; i < 18; i++)
            for (int j = 1; j <= ncnt; j++)
                up[i][j] = up[i - 1][up[i - 1][j]];
        scanf("%d", &q);
        while (q--)
        {
            int Stot;
            scanf("%d", &Stot);
            for (int i = 1; i <= Stot; i++)
                scanf("%d", &seq[i]);
            sort(seq + 1, seq + 1 + Stot, [](const int &rhs1, const int &rhs2) { return lft[rhs1] < lft[rhs2]; });
            int ans = -2 * Stot;
            for (int i = 1, lca; i <= Stot; i++)
                lca = getLCA(seq[i], seq[i % Stot + 1]), ans += dist[seq[i]] + dist[seq[i % Stot + 1]] - 2LL * dist[lca];
            if (getLCA(seq[1], seq[Stot]) <= n)
                ans += 2;
            ans >>= 1, printf("%d\n", ans);
        }
    }
    return 0;
}