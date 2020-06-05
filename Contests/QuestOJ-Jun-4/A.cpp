// A.cpp
#include <bits/stdc++.h>

using namespace std;

inline char nc()
{
    static char buf[1000000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++;
}

int read()
{
    int x = 0, f = 1;
    char ch = nc();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = nc();
    }
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + ch - '0', ch = nc();
    return x * f;
}

const int MAX_N = 1010, MAX_M = MAX_N * MAX_N;

typedef pair<int, int> pii;

int n, m, mp[MAX_N][20], deg[MAX_N], up[20][MAX_N], dep[MAX_N], chain[MAX_N];
int lft[MAX_N], rig[MAX_N], ptot, anti[MAX_N], dp[MAX_N][1 << 11];
int neck[MAX_N], idx[MAX_N], lg[1 << 11];
vector<int> sid[MAX_N];
vector<pii> requests[20];

struct segment
{
    int u, v, d, nu, nv;
} segs[MAX_M];

inline int lowbit(int x) { return x & (-x); }

int getLCA(int x, int y)
{
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = 19; i >= 0; i--)
        if (dep[up[i][x]] >= dep[y])
            x = up[i][x];
    if (x == y)
        return x;
    for (int i = 19; i >= 0; i--)
        if (up[i][x] != up[i][y])
            x = up[i][x], y = up[i][y];
    return up[0][x];
}

void dfs(int u, int fa)
{
    up[0][u] = fa, dep[u] = dep[fa] + 1;
    lft[u] = ++ptot, anti[ptot] = u;
    vector<int> sons;
    for (int i = 0; i < deg[u]; i++)
        if (mp[u][i] != fa)
            sons.push_back(mp[u][i]);
    deg[u] = sons.size();
    for (int i = 0; i < deg[u]; i++)
        mp[u][i] = sons[i], idx[mp[u][i]] = i;
    for (int i = 0; i < deg[u]; i++)
        dfs(mp[u][i], u);
    rig[u] = ptot;
}

void collect(int u)
{
    for (int i = 0; i < deg[u]; i++)
        collect(mp[u][i]);
    for (int i = lft[u] + 1; i <= rig[u]; i++)
    {
        int cpt = anti[i];
        if (up[0][cpt] == u)
            chain[cpt] += dp[cpt][(1 << deg[cpt]) - 1];
        else
        {
            int cf = up[0][neck[cpt]];
            chain[cpt] += dp[cf][(1 << deg[cf]) - 1 - (1 << idx[neck[cpt]])];
            neck[cpt] = cf;
        }
    }
    for (int i = 0; i < deg[u]; i++)
        idx[mp[u][i]] = i;
    for (int i = 0; i < deg[u]; i++)
        requests[i].clear();
    for (int vid : sid[u])
    {
        int nu = segs[vid].nu = neck[segs[vid].u], nv = segs[vid].nv = neck[segs[vid].v];
        int ndp = chain[segs[vid].u] + chain[segs[vid].v];
        if (nu == 0)
            swap(nu, nv);
        if (nv == 0)
            // chain shape;
            requests[idx[nu]].push_back(make_pair(ndp, 1 << idx[nu]));
        else
        {
            nu = idx[nu], nv = idx[nv];
            if (nu > nv)
                swap(nu, nv);
            requests[nu].push_back(make_pair(ndp, (1 << nu) | (1 << nv)));
        }
    }
    for (int stat = 1; stat < (1 << deg[u]); stat++)
    {
        int v = lg[lowbit(stat)];
        dp[u][stat] = dp[u][stat ^ (1 << v)] + dp[mp[u][v]][(1 << deg[mp[u][v]]) - 1];
        for (auto &g : requests[v])
            if ((stat & g.second) == g.second)
                dp[u][stat] = max(dp[u][stat], dp[u][stat ^ g.second] + g.first + 1);
    }
    neck[u] = u;
}

int main()
{
    n = read();
    for (int i = 1, g; i < (1 << 11); i <<= 1, g++)
        lg[i] = g;
    for (int i = 1, u, v; i <= n - 1; i++)
        u = read(), v = read(), mp[u][deg[u]++] = v, mp[v][deg[v]++] = u;
    dfs(1, 0), m = read();
    for (int i = 1; i < 20; i++)
        for (int j = 1; j <= n; j++)
            up[i][j] = up[i - 1][up[i - 1][j]];
    for (int i = 1; i <= m; i++)
    {
        segs[i].u = read(), segs[i].v = read();
        segs[i].d = getLCA(segs[i].u, segs[i].v);
        sid[segs[i].d].push_back(i);
    }
    collect(1), printf("%d\n", dp[1][(1 << deg[1]) - 1]);
    return 0;
}