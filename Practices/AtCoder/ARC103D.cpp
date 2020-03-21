// ARC103F.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

typedef long long ll;
typedef pair<int, int> pii;

int n, siz[MAX_N], id[MAX_N], fa[MAX_N], head[MAX_N], current;
ll D[MAX_N];
set<ll> st[2];
map<ll, int> mp;

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

ll dfs(int u, int up)
{
    ll ret = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != up)
            ret += dfs(edges[i].to, u) + siz[edges[i].to];
    return ret;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &D[i]), mp[D[i]] = i, siz[i] = 1, id[i] = i;
    sort(id + 1, id + 1 + n, [](const int &rhs1, const int &rhs2) { return D[rhs1] > D[rhs2]; });
    for (int i = 1; i < n; i++)
    {
        int u = id[i];
        ll transfer = D[u] - (n - siz[u]) + siz[u];
        if (mp.count(transfer) == 0)
            puts("-1"), exit(0);
        fa[u] = mp[transfer], siz[fa[u]] += siz[u], addpath(fa[u], u), addpath(u, fa[u]);
    }
    if (dfs(id[n], 0) == D[id[n]])
    {
        for (int i = 1; i <= n; i++)
            if (fa[i] != 0)
                printf("%d %d\n", i, fa[i]);
    }
    else
        puts("-1");
    return 0;
}