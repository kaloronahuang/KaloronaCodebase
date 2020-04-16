// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, head[MAX_N], current, siz[MAX_N], dep[MAX_N], idx, deg[MAX_N], up[MAX_N];
long long ans = 0;
bool vis[MAX_N];

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
    siz[u] = 1, dep[u] = dep[fa] + 1, up[u] = fa;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u), siz[u] += siz[edges[i].to];
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &idx);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u), deg[u]++, deg[v]++;
    dfs(1, 0);
    priority_queue<pair<int, int>> pq;
    for (int i = 2; i <= n; i++)
        if (deg[i] == 1)
            pq.push(make_pair(dep[i] - siz[i], i));
    while (!pq.empty() && idx)
    {
        int u = pq.top().second;
        ans += pq.top().first;
        pq.pop(), idx--;
        if (up[u] && !vis[up[u]])
            pq.push(make_pair(dep[up[u]] - siz[up[u]], up[u])), vis[up[u]] = true;
    }
    printf("%lld\n", ans);
    return 0;
}