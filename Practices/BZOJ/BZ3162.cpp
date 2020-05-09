// BZ3162.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 200, bitnum = 133, mod = 1e9 + 7;

int n, dep[MAX_N], up[MAX_N], siz[MAX_N], mx_val = 0x3f3f3f3f, groot, sub[MAX_N], dp[MAX_N][2], inv[MAX_N];
vector<int> G[MAX_N], roots;

void dfs(int u, int fa)
{
    dep[u] = dep[fa] + 1, up[u] = fa, siz[u] = 1;
    int max_component = 0;
    for (int v : G[u])
        if (v != fa)
            dfs(v, u), siz[u] += siz[v], max_component = max(max_component, siz[v]);
    max_component = max(max_component, n - siz[u]);
    if (max_component < mx_val)
        mx_val = max_component, roots.clear(), roots.push_back(u);
    else if (max_component == mx_val)
        roots.push_back(u);
}

int binomial(int n_, int k_)
{
    int ret = 1;
    for (int i = n_ - k_ + 1; i <= n_; i++)
        ret = 1LL * ret * i % mod;
    return 1LL * ret * inv[k_] % mod;
}

void hashDFS(int u, int fa)
{
    vector<int>::iterator delIt = G[u].end();
    for (vector<int>::iterator it = G[u].begin(); it != G[u].end(); it++)
        if (*it == fa)
        {
            delIt = it;
            break;
        }
    if (delIt != G[u].end())
        G[u].erase(delIt);
    for (int v : G[u])
        hashDFS(v, u);
    sort(G[u].begin(), G[u].end(), [](const int &rhs1, const int &rhs2) { return sub[rhs1] < sub[rhs2]; });
    sub[u] = 19260817, dp[u][0] = 1, dp[u][1] = 1;
    for (int i = 0, gx = 0, siz = G[u].size(); i < siz; i = gx)
    {
        for (gx = i; gx < siz && sub[G[u][gx]] == sub[G[u][i]]; gx++)
            sub[u] = ((1LL * sub[u] * bitnum % mod) ^ sub[G[u][gx]]);
        dp[u][0] = 1LL * dp[u][0] * binomial((0LL + dp[G[u][i]][0] + dp[G[u][i]][1] + gx - i - 1) % mod, gx - i) % mod;
        dp[u][1] = 1LL * dp[u][1] * binomial((0LL + dp[G[u][i]][0] + gx - i - 1) % mod, gx - i) % mod;
    }
    sub[u] = 1LL * sub[u] * bitnum % mod * bitnum % mod * bitnum % mod;
}

int main()
{
    // freopen("2.in", "r", stdin);
    scanf("%d", &n);
    int org_n = n;
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), G[u].push_back(v), G[v].push_back(u);
    inv[0] = inv[1] = 1;
    for (int i = 2; i <= n; i++)
        inv[i] = 1LL * (mod - mod / i) * inv[mod % i] % mod;
    for (int i = 1; i <= n; i++)
        inv[i] = 1LL * inv[i] * inv[i - 1] % mod;
    dfs(1, 0);
    if (roots.size() >= 2)
    {
        int A = roots[0], B = roots[1];
        vector<int>::iterator itA, itB;
        for (vector<int>::iterator it = G[A].begin(); it != G[A].end(); it++)
            if (*it == B)
                itA = it;
        for (vector<int>::iterator it = G[B].begin(); it != G[B].end(); it++)
            if (*it == A)
                itB = it;
        G[A].erase(itA), G[B].erase(itB);
        G[A].push_back(groot = ++n), G[B].push_back(groot);
        G[groot].push_back(A), G[groot].push_back(B);
    }
    else
        groot = roots[0];
    hashDFS(groot, 0);
    if (groot == org_n + 1)
    {
        int ans = dp[groot][0];
        if (sub[roots[0]] == sub[roots[1]])
            ans = (0LL + ans + mod - binomial(dp[roots[0]][1] + 1, 2)) % mod;
        else
            ans = (0LL + ans + mod - 1LL * dp[roots[0]][1] * dp[roots[1]][1] % mod) % mod;
        printf("%d\n", ans);
    }
    else
        printf("%lld\n", (0LL + dp[groot][0] + dp[groot][1]) % mod);
    return 0;
}