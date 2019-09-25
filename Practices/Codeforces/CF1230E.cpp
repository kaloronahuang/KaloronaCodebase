// CF1230E.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 100100, mod = 1e9 + 7;

int head[MAX_N], current;
ll val[MAX_N], ans, n;
map<ll, ll> mps[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

ll gcd(ll a, ll b)
{
    if (a == 0 && b == 0)
        return 0;
    if (a == 0)
        return b;
    return b == 0 ? a : gcd(b, a % b);
}

void dfs(int u, int fa)
{
    for (map<ll, ll>::iterator it = mps[fa].begin(); it != mps[fa].end(); it++)
        mps[u][gcd(val[u], it->first)] += it->second;
    mps[u][val[u]]++;
    for (map<ll, ll>::iterator it = mps[u].begin(); it != mps[u].end(); it++)
        ans = (1LL * ans + 1LL * it->second * it->first % mod) % mod;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &val[i]);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dfs(1, 0), printf("%lld", ans);
    return 0;
}