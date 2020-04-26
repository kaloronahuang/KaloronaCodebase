// CF613D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4e5 + 200;

int n, q, head[MAX_N], current, st[20][MAX_N], log2_[MAX_N], dep[MAX_N], pos[MAX_N];
int ptot, dtot, lft[MAX_N], rig[MAX_N], anti[MAX_N], up[MAX_N], dp[MAX_N][2];
int vtot, vseq[MAX_N], stk[MAX_N], tail;
bool vis[MAX_N];
vector<int> vG[MAX_N];

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
    dep[u] = dep[fa] + 1, st[0][++ptot] = u, pos[u] = ptot;
    lft[u] = ++dtot, anti[dtot] = u, up[u] = fa;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u), st[0][++ptot] = u;
    rig[u] = dtot;
}

int gmin(int x, int y) { return dep[x] < dep[y] ? x : y; }

int getLCA(int x, int y)
{
    if (pos[x] > pos[y])
        swap(x, y);
    int d = log2_[pos[y] - pos[x] + 1];
    return gmin(st[d][pos[x]], st[d][pos[y] - (1 << d) + 1]);
}

bool compare(int a, int b) { return lft[a] < lft[b]; }

void addpath_virtual(int u, int v) { vG[u].push_back(v), vG[v].push_back(u); }

void collect(int u, int fa)
{
    dp[u][0] = dp[u][1] = 0;
    int noUp = 0, bypass = 0, upgoing = 0;
    for (int i = 0, siz = vG[u].size(); i < siz; i++)
    {
        int v = vG[u][i];
        if (v == fa || v == u)
            continue;
        collect(v, u);
        upgoing = min(upgoing + dp[v][1], min(dp[v][0], dp[v][1]) + noUp);
        noUp += dp[v][1];
        bypass += min(dp[v][0], dp[v][1]);
    }
    vG[u].clear();
    if (vis[u])
        // crutial point;
        dp[u][0] = noUp, dp[u][1] = noUp + 1;
    else
        dp[u][0] = upgoing, dp[u][1] = min(noUp, bypass + 1);
}

int solve()
{
    scanf("%d", &vtot);
    for (int i = 1; i <= vtot; i++)
        scanf("%d", &vseq[i]), vis[vseq[i]] = true;
    for (int i = 1; i <= vtot; i++)
        if (vis[up[vseq[i]]])
            return -1;
    sort(vseq + 1, vseq + 1 + vtot, compare);
    stk[++tail] = 1;
    for (int i = 1; i <= vtot; i++)
    {
        int lca = getLCA(vseq[i], stk[tail]);
        while (tail > 1 && dep[stk[tail - 1]] > dep[lca])
            addpath_virtual(stk[tail - 1], stk[tail]), tail--;
        if (dep[stk[tail]] > dep[lca])
            addpath_virtual(stk[tail], lca), tail--;
        if (lca != stk[tail])
            stk[++tail] = lca;
        stk[++tail] = vseq[i];
    }
    while (tail > 1)
        addpath_virtual(stk[tail - 1], stk[tail]), tail--;
    collect(stk[tail], 0);
    return min(dp[stk[tail]][0], dp[stk[tail]][1]);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dfs(1, 0), log2_[2] = 1;
    for (int i = 3; i <= ptot; i++)
        log2_[i] = log2_[i >> 1] + 1;
    for (int i = 1; i < 20; i++)
        for (int j = 1; j <= ptot; j++)
            st[i][j] = gmin(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
    scanf("%d", &q);
    while (q--)
    {
        printf("%d\n", solve());
        // clear;
        for (int i = 1; i <= vtot; i++)
            vis[vseq[i]] = false;
        vtot = tail = 0;
    }
    return 0;
}