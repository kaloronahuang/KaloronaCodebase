// ARC086C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, mod = 1e9 + 7;

typedef pair<int, int> pii;

int n, fa[MAX_N], head[MAX_N], current, dep[MAX_N], dcnt[MAX_N], mxdep[MAX_N];
int idx[MAX_N], ptot, all[MAX_N], zero[MAX_N], one[MAX_N];
vector<pii> dp[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

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

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u)
{
    int son = n + 1, deg = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        dfs(edges[i].to), deg++;
        if (mxdep[edges[i].to] > mxdep[son])
            son = edges[i].to;
    }
    if (son != n + 1)
        idx[u] = idx[son], mxdep[u] = mxdep[son] + 1;
    else
        idx[u] = ++ptot;
    dp[idx[u]].push_back(make_pair(1, 1));
    if (deg == 0)
        return;
    for (int i = 0; i <= mxdep[u] - 1; i++)
        all[i] = zero[i] = 1, one[i] = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        for (int j = 0; j <= mxdep[edges[i].to]; j++)
        {
            int curt = mxdep[son] - mxdep[edges[i].to] + j;
            pii cdp = dp[idx[edges[i].to]][j];
            all[curt] = 1LL * all[curt] * (0LL + cdp.first + cdp.second) % mod;
            zero[curt] = 1LL * zero[curt] * cdp.first % mod;
        }
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        for (int j = 0; j <= mxdep[edges[i].to]; j++)
        {
            int curt = mxdep[son] - mxdep[edges[i].to] + j;
            pii cdp = dp[idx[edges[i].to]][j];
            one[curt] = (0LL + one[curt] + 1LL * zero[curt] * fpow(cdp.first, mod - 2) % mod * cdp.second % mod) % mod;
        }
    for (int i = 0; i <= mxdep[u] - 1; i++)
        dp[idx[u]][i].first = (0LL + all[i] + mod - one[i]) % mod, dp[idx[u]][i].second = one[i];
}

int main()
{
    memset(head, -1, sizeof(head)), scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &fa[i]), addpath(fa[i], i);
        dep[i] = dep[fa[i]] + 1, dcnt[dep[i]]++;
    }
    dcnt[0]++, mxdep[n + 1] = -1, dfs(0);
    int ans = 0;
    for (int i = 0; i <= mxdep[0]; i++)
    {
        pii curt = dp[idx[0]][i];
        ans = (0LL + ans + 1LL * curt.second * fpow(2, n + 1 - dcnt[mxdep[0] - i]) % mod) % mod;
    }
    printf("%d\n", ans);
    return 0;
}