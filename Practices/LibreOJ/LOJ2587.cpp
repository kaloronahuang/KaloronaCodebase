// LOJ2587.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 4e5 + 200, MAX_E = 2e5 + 200;

int n, m, head[MAX_N], current, dfn[MAX_N], low[MAX_N], ptot, stk[MAX_N], tail, ncnt, dot[MAX_N], siz[MAX_N], csiz;
vector<int> G[MAX_N];
ll ans;

struct edge
{
    int to, nxt;
} edges[MAX_E << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++ptot, stk[++tail] = u, csiz++;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (dfn[edges[i].to] == 0)
        {
            tarjan(edges[i].to), low[u] = min(low[u], low[edges[i].to]);
            if (low[edges[i].to] == dfn[u])
            {
                int bcc = ++ncnt;
                dot[bcc] = 0;
                for (int x = 0; x != edges[i].to; tail--)
                    x = stk[tail], G[bcc].push_back(x), G[x].push_back(bcc), dot[bcc]++;
                G[bcc].push_back(u), G[u].push_back(bcc), dot[bcc]++;
            }
        }
        else
            low[u] = min(low[u], dfn[edges[i].to]);
}

void dfs(int u, int fa)
{
    siz[u] = (u <= n);
    for (int v : G[u])
        if (v != fa)
            dfs(v, u), ans += 2LL * dot[u] * siz[u] * siz[v], siz[u] += siz[v];
    ans += 2LL * dot[u] * siz[u] * (csiz - siz[u]);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    ncnt = n;
    for (int i = 1; i <= n; i++)
        dot[i] = -1;
    for (int i = 1; i <= n; i++)
        if (dfn[i] == 0)
            csiz = 0, tarjan(i), tail--, dfs(i, 0);
    printf("%lld\n", ans);
    return 0;
}