// P2597.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 75534;

int head[MAX_N], current, n, m, deg[MAX_N], order[MAX_N], fa[20][MAX_N], dep[MAX_N], siz[MAX_N], root;
bool vis[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

vector<int> G[MAX_N], revG[MAX_N];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void toposort()
{
    int tot = 0;
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (deg[i] == 0)
            q.push(i);
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), order[++tot] = u;
        for (int i = 0, siz = G[u].size(); i < siz; i++)
            if (--deg[G[u][i]] == 0)
                q.push(G[u][i]);
    }
}

int getLCA(int x, int y)
{
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = 19; i >= 0; i--)
        if (dep[fa[i][x]] >= dep[y])
            x = fa[i][x];
    if (x == y)
        return x;
    for (int i = 19; i >= 0; i--)
        if (fa[i][x] != fa[i][y])
            x = fa[i][x], y = fa[i][y];
    return fa[0][x];
}

void dfs(int u)
{
    siz[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa[0][u])
            dfs(edges[i].to), siz[u] += siz[edges[i].to];
}

int main()
{
    memset(head, -1, sizeof(head)), scanf("%d", &n);
    for (int i = 1, val; i <= n; i++)
        while (scanf("%d", &val) && val != 0)
            G[val].push_back(i), deg[i]++, revG[i].push_back(val);
    toposort(), deg[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        int u = order[i], lca = revG[u].empty() ? 0 : revG[u][0];
        for (int idx = 0, siz = revG[u].size(); idx < siz; idx++)
            lca = getLCA(lca, revG[u][idx]);
        fa[0][u] = lca, dep[u] = dep[lca] + 1, vis[u] = true;
        for (int i = 1; i <= 19; i++)
            fa[i][u] = fa[i - 1][fa[i - 1][u]];
        addpath(lca, u);
    }
    dfs(0);
    for (int i = 1; i <= n; i++)
        printf("%d\n", siz[i] - 1);
    return 0;
}