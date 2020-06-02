// P4323.cpp
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, mod = 1e9 + 7, bitnum = 133;

typedef pair<int, int> pii;

int n, sub[2][MAX_N], g[2][MAX_N], bpow[MAX_N], cidx;
vector<int> G[2][MAX_N];
vector<pii> subs[2][MAX_N];

int fpow(int bas, int tim)
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

const int invBitnum = fpow(bitnum, mod - 2);

void dfs(int u, int fa, int idx)
{
    for (int v : G[idx][u])
        if (v != fa)
            dfs(v, u, idx);
    cidx = idx;
    sort(G[idx][u].begin(), G[idx][u].end(), [](const int &rhs1, const int &rhs2) { return sub[cidx][rhs1] < sub[cidx][rhs2]; });
    sub[idx][u] = 1LL * bitnum * bitnum % mod;
    int rk = 0;
    for (int v : G[idx][u])
        if (v != fa)
            sub[idx][u] = (0LL + sub[idx][u] + 1LL * bpow[rk] * sub[idx][v] % mod) % mod, subs[idx][u].push_back(make_pair(sub[idx][v], v)), rk++;
    sub[idx][u] = 1LL * sub[idx][u] * bitnum % mod * bitnum % mod * bitnum % mod;
}

const int endlInv = 1LL * invBitnum * invBitnum % mod * invBitnum % mod;

void collect(int u, int fa, int idx)
{
    if (fa != 0)
        subs[idx][u].push_back(make_pair(g[idx][u], fa));
    sort(subs[idx][u].begin(), subs[idx][u].end());
    int rk = 0, acc = 0;
    deque<int> pre, suf;
    pre.push_back(0), suf.push_back(0);
    for (pii v : subs[idx][u])
    {
        acc = (0LL + acc + 1LL * bpow[rk] * v.first % mod) % mod;
        pre.push_back(acc), suf.push_back(1LL * bpow[rk] * v.first % mod), rk++;
    }
    pre.push_back(0), suf.push_back(0);
    for (int i = rk; i >= 0; i--)
        suf[i] = (0LL + suf[i] + suf[i + 1]) % mod;
    rk = 1;
    for (pii v : subs[idx][u])
    {
        if (v.second != fa)
        {
            g[idx][v.second] = (1LL * bitnum * bitnum % mod + 0LL + pre[rk - 1] + 1LL * invBitnum * suf[rk + 1] % mod) % mod * bitnum % mod * bitnum % mod * bitnum % mod;
            collect(v.second, u, idx);
        }
        rk++;
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = bpow[0] = 1; i <= n + 10; i++)
        bpow[i] = 1LL * bpow[i - 1] * bitnum % mod;
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), G[0][u].push_back(v), G[0][v].push_back(u);
    for (int i = 1, u, v; i <= n; i++)
        scanf("%d%d", &u, &v), G[1][u].push_back(v), G[1][v].push_back(u);
    dfs(1, 0, 0), dfs(1, 0, 1), collect(1, 0, 0), collect(1, 0, 1);
    map<int, int> mp;
    for (int i = 1; i <= n; i++)
    {
        sort(subs[0][i].begin(), subs[0][i].end());
        int acc = 0;
        for (pii v : subs[0][i])
            acc = (1LL * acc * bitnum % mod + v.first) % mod;
        mp[acc]++;
    }
    for (int i = 1; i <= n + 1; i++)
        if (G[1][i].size() == 1)
        {
            int cpt = G[1][i][0];
            sort(subs[1][cpt].begin(), subs[1][cpt].end());
            int acc = 0;
            for (pii v : subs[1][cpt])
                if (v.second != i)
                    acc = (1LL * acc * bitnum % mod + v.first) % mod;
            if (mp[acc])
                printf("%d\n", i), exit(0);
        }
    return 0;
}