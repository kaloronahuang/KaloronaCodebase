// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, mod = 998244353;
typedef long long ll;
typedef pair<int, int> pii;

int head[MAX_N], current, n, m, k, pos[MAX_N], dep[MAX_N], fa[20][MAX_N], fac[MAX_N], fac_inv[MAX_N];
ll prefix[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void fileIO()
{
    freopen("meal.in", "r", stdin);
    freopen("meal.out", "w", stdout);
}

inline char nc()
{
    static char buf[1 << 20], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++;
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

int quick_pow(int bas, int tim)
{
    int ret = 1;
    while (tim)
    {
        if (tim & 1)
            ret = 1LL * ret * bas % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ret;
}

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void dfs(int u)
{
    dep[u] = dep[fa[0][u]] + 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa[0][u])
        {
            fa[0][edges[i].to] = u, prefix[edges[i].to] = prefix[u] + edges[i].weight;
            dfs(edges[i].to);
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

ll getDist(int x, int y) { return prefix[x] + prefix[y] - (prefix[getLCA(x, y)] << 1); }

int binomial(int n_, int k_) { return 1LL * fac[n_] * fac_inv[k_] % mod * fac_inv[n_ - k_] % mod; }

/*

namespace subtask1
{

ll dp[1 << 20][21], ans[1 << 20];
int lcas[30][30], kstat[1 << 20];

void subtask1Handler()
{
    // some special cases;
    if (k == 1)
        puts("0"), exit(0);
    // iterating the status;
    int nominator = 0, denominator = binomial(m, k);
    // here comes a shift;
    for (int i = 1; i <= m; i++)
        pos[i - 1] = pos[i];
    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++)
            lcas[i][j] = getLCA(pos[i], pos[j]);
    memset(ans, 0x3f, sizeof(ans));
    // collect;
    for (int stat = 1; stat < (1 << m); stat++)
    {
        int cnt_bit = 0;
        for (int i = 0; i < m; i++)
            if (stat & (1 << i))
                cnt_bit++;
        if (cnt_bit == k)
            kstat[++kstat[0]] = stat;
    }
    // start to dp;
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 0; i < m; i++)
        dp[(1 << i)][i] = 0;
    for (int stat = 1; stat < (1 << m); stat++)
    {
        int cnt_bit = 0;
        for (int i = 0; i < m; i++)
            if (stat & (1 << i))
                cnt_bit++;
        if (cnt_bit > k || cnt_bit == 1)
            continue;
        for (int endpoint = 0; endpoint < m; endpoint++)
            if (stat & (1 << endpoint))
            {
                int pre_stat = stat ^ (1 << endpoint);
                for (int pre_point = 0; pre_point < m; pre_point++)
                    if (pre_stat & (1 << pre_point))
                        dp[stat][endpoint] = min(dp[stat][endpoint], dp[pre_stat][pre_point] + prefix[pos[pre_point]] + prefix[pos[endpoint]] - (prefix[lcas[pre_point][endpoint]] << 1));
            }
    }
    // complete the answer;
    for (int idx = 1; idx <= kstat[0]; idx++)
    {
        for (int endpoint = 0; endpoint < m; endpoint++)
            ans[kstat[idx]] = min(ans[kstat[idx]], dp[kstat[idx]][endpoint]);
        nominator = (1LL * nominator + ans[kstat[idx]]) % mod;
    }
    printf("%lld\n", 1LL * nominator * quick_pow(denominator, mod - 2) % mod);
}

} // namespace subtask1
// 40 pts expected;

*/

int main()
{
    fileIO();
    memset(head, -1, sizeof(head));
    n = read(), m = read(), k = read();
    // math shit;
    for (int i = fac[0] = 1; i <= n; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    fac_inv[n] = quick_pow(fac[n], mod - 2);
    for (int i = n - 1; i >= 0; i--)
        fac_inv[i] = 1LL * fac_inv[i + 1] * (i + 1) % mod;
    // another input stuff;
    for (int i = 1; i <= m; i++)
        pos[i] = read();
    for (int i = 1, u, v, w; i <= n - 1; i++)
        u = read(), v = read(), w = read(), addpath(u, v, w), addpath(v, u, w);
    dfs(1);
    for (int i = 1; i <= 19; i++)
        for (int j = 1; j <= n; j++)
            fa[i][j] = fa[i - 1][fa[i - 1][j]];
    /*
    if (m <= 20)
        subtask1::subtask1Handler(), exit(0);
    */
    // working one the virtual tree;
    
    return 0;
}