// BZ4784.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 200, MAX_E = 1e6 + 200, mod = 998244353;

int T, n, m, head[MAX_N], current, dfn[MAX_N], low[MAX_N], tag[MAX_N], stk[MAX_N], tail, dp[MAX_N], ptot, g[MAX_N];
bool vis[MAX_N], inst[MAX_N];

struct edge
{
    int to, nxt;
    bool tag;
} edges[MAX_E << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].tag = false, head[src] = current++;
}

void mark(int u, int fa)
{
    vis[u] = true, inst[u] = true;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (inst[edges[i].to])
            tag[u]++, tag[edges[i].to]--;
        else if (!vis[edges[i].to])
            mark(edges[i].to, u);
    inst[u] = false;
}

void solidate(int u, int fa)
{
    vis[u] = true;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && vis[edges[i].to] == false)
            solidate(edges[i].to, u), tag[u] += tag[edges[i].to];
}

void tarjan(int u, int fa)
{
    dfn[u] = low[u] = ++ptot, inst[u] = true;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (dfn[edges[i].to] == 0)
        {
            stk[++tail] = i;
            tarjan(edges[i].to, u), low[u] = min(low[u], low[edges[i].to]);
            if (low[edges[i].to] == dfn[u])
                do
                {
                    edges[stk[tail]].tag = true, edges[stk[tail] ^ 1].tag = true;
                } while (stk[tail--] != i);
        }
        else if (inst[edges[i].to] && edges[i].to != fa)
            low[u] = min(low[u], low[edges[i].to]), stk[++tail] = i;
    inst[u] = false;
    if (dfn[u] == low[u] && tail)
        tail--;
}

void dfs(int u, int org)
{
    vis[u] = true, dp[u] = 1;
    int deg = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (vis[edges[i].to] == false && edges[i].tag == false)
        {
            dfs(edges[i].to, org), deg++;
            dp[u] = 1LL * dp[u] * dp[edges[i].to] % mod;
        }
    if (u == org)
        dp[u] = 1LL * g[deg] * dp[u] % mod;
    else
        dp[u] = 1LL * g[deg + 1] * dp[u] % mod;
}

int main()
{
    scanf("%d", &T);
    g[0] = g[1] = 1, g[2] = 2;
    for (int i = 3; i < MAX_N; i++)
        g[i] = (0LL + g[i - 1] + 1LL * g[i - 2] * (i - 1) % mod) % mod;
    while (T--)
    {
        scanf("%d%d", &n, &m), current = ptot = tail = 0;
        for (int i = 1; i <= n; i++)
            head[i] = -1, vis[i] = inst[i] = false, tag[i] = 0;
        for (int i = 1, u, v; i <= m; i++)
            scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
        // check;
        mark(1, 0);
        for (int i = 1; i <= n; i++)
            vis[i] = false;
        solidate(1, 0);
        bool flag = true;
        for (int i = 1; i <= n; i++)
            flag &= (tag[i] <= 2), vis[i] = false;
        if (!flag)
        {
            puts("0");
            continue;
        }
        for (int i = 1; i <= n; i++)
            dfn[i] = low[i] = 0;
        tarjan(1, 0);
        int ans = 1;
        for (int i = 1; i <= n; i++)
            if (!vis[i])
                dfs(i, i), ans = 1LL * ans * dp[i] % mod;
        printf("%d\n", ans);
    }
    return 0;
}