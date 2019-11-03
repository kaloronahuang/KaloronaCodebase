// C.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e5 + 200, mod = 1e9 + 7;

int head[MAX_N], current, n, m, deg[MAX_N], rk[MAX_N], perm[MAX_N];
ll ans, cnt[MAX_N], sum[MAX_N], ai[MAX_N];
vector<int> G[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].nxt = head[src], edges[current].to = dst;
    head[src] = current++;
}

bool compare(int a, int b) { return deg[a] < deg[b] || (deg[a] == deg[b] && a < b); }

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &ai[i]);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u), deg[u]++, deg[v]++;
    for (int i = 1; i <= n; i++)
        perm[i] = i;
    sort(perm + 1, perm + 1 + n, compare);
    for (int i = 1; i <= n; i++)
        rk[perm[i]] = i;
    for (int u = 1; u <= n; u++)
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (rk[u] < rk[edges[i].to])
                G[u].push_back(edges[i].to);
    for (int u = 1; u <= n; u++)
    {
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            for (int id = 0, siz = G[edges[i].to].size(); id < siz; id++)
                if (rk[G[edges[i].to][id]] > rk[u])
                {
                    int w = G[edges[i].to][id];
                    ans = (1LL * ans + 1LL * (ai[edges[i].to] + ai[w]) * cnt[w] % mod + sum[w]) % mod;
                    sum[w] = (1LL * sum[w] + 1LL * ai[u] + 1LL * ai[edges[i].to]) % mod, cnt[w]++;
                }
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            for (int id = 0, siz = G[edges[i].to].size(); id < siz; id++)
                if (rk[G[edges[i].to][id]] > rk[u])
                    sum[G[edges[i].to][id]] = cnt[G[edges[i].to][id]] = 0;
    }
    printf("%lld", ans);
    return 0;
}