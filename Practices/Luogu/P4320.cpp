// P4320.cpp
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e6 + 3;

int head[MAX_N], current, n, m, q, dfn[MAX_N], low[MAX_N], stk[MAX_N], dep[MAX_N];
int ncnt, ptot, tail, cut[MAX_N], aff[MAX_N], dist[MAX_N], org_dist[MAX_N], fa[24][MAX_N];
vector<int> DCCs[MAX_N], G[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

inline char getChar()
{
    static char buf[100000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) +
                             fread(buf, 1, 100000, stdin),
                        p1 == p2)
               ? EOF
               : *p1++;
}

int read()
{
    int x = 0, f = 1;
    char ch = getChar();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getChar();
    }
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + ch - '0', ch = getChar();
    return x * f;
}

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void tarjan(int u, int org)
{
    dfn[u] = low[u] = ++ptot, stk[++tail] = u;
    int cnt = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (dfn[edges[i].to] == 0)
        {
            tarjan(edges[i].to, org), low[u] = min(low[u], low[edges[i].to]);
            if (low[edges[i].to] >= dfn[u])
            {
                // maybe a cut;
                cnt++;
                if (cnt >= 2 || u != org)
                    cut[u] = 1;
                ncnt++;
                do
                {
                    DCCs[ncnt].push_back(stk[tail]), aff[stk[tail]] = ncnt;
                } while (stk[tail--] != edges[i].to);
                // can't pop the cut out of the stack;
                // there must be 2 components connected by the cut;
                DCCs[ncnt].push_back(u), aff[u] = ncnt;
            }
        }
        else
            low[u] = min(low[u], dfn[edges[i].to]);
}

void bfs(int src)
{
    queue<int> q;
    q.push(src), dep[src] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = 0, siz = G[u].size(); i < siz; i++)
            if (dep[G[u][i]] == 0)
            {
                dep[G[u][i]] = dep[u] + 1, dist[G[u][i]] += dist[u];
                fa[0][G[u][i]] = u, q.push(G[u][i]);
            }
    }
}

int getLCA(int x, int y)
{
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = 23; i >= 0; i--)
        if (dep[fa[i][x]] >= dep[y])
            x = fa[i][x];
    if (x == y)
        return x;
    for (int i = 23; i >= 0; i--)
        if (fa[i][x] != fa[i][y])
            x = fa[i][x], y = fa[i][y];
    return fa[0][x];
}

int query(int x, int y)
{
    int lca = getLCA(x, y);
    return dist[x] + dist[y] - dist[lca] - dist[fa[0][lca]] - org_dist[x] - org_dist[y] + 2;
}

int main()
{
    memset(head, -1, sizeof(head));
    n = read(), m = read();
    for (int i = 1, u, v; i <= m; i++)
        u = read(), v = read(), addpath(u, v), addpath(v, u);
    // get the DCCs and make it into a fucking tree;
    for (int i = 1; i <= n; i++)
        if (dfn[i] == 0)
            tarjan(i, i);
    int tree_tot = ncnt;
    for (int i = 1; i <= n; i++)
        if (cut[i])
            aff[i] = ++tree_tot, dist[aff[i]] = org_dist[aff[i]] = 1;
    for (int cp = 1; cp <= ncnt; cp++)
        for (int i = 0, siz = DCCs[cp].size(); i < siz; i++)
            if (cut[DCCs[cp][i]])
                G[cp].push_back(aff[DCCs[cp][i]]), G[aff[DCCs[cp][i]]].push_back(cp);
    for (int i = 1; i <= tree_tot; i++)
        if (dep[i] == 0)
            bfs(i);
    for (int i = 1; i <= 23; i++)
        for (int j = 1; j <= tree_tot; j++)
            fa[i][j] = fa[i - 1][fa[i - 1][j]];
    q = read();
    while (q--)
    {
        int x, y;
        x = read(), y = read();
        printf("%d\n", query(aff[x], aff[y]));
    }
    return 0;
}