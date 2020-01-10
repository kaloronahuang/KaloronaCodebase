// FOJ1914.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;
typedef pair<int, int> pii;
typedef long long ll;

int head[MAX_N], current, n, m, q, dfn[MAX_N], low[MAX_N], stk[MAX_N], tail, ptot;
int ncnt, aff[MAX_N], up[15][MAX_N], dep[MAX_N];
ll dist[MAX_N], loops[MAX_N], prefix[MAX_N];
bool inst[MAX_N], vis[MAX_N];

vector<int> G[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void shortest_path(int src)
{
    memset(dist, 0x3f, sizeof(dist));
    priority_queue<pii> pq;
    pq.push(make_pair(0, src)), dist[src] = 0;
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[edges[i].to] > dist[u] + edges[i].weight)
                dist[edges[i].to] = dist[u] + edges[i].weight, pq.push(make_pair(-dist[edges[i].to], edges[i].to));
    }
    memset(vis, false, sizeof(vis));
}

void tarjan(int u, int fa)
{
    dfn[u] = ++ptot;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            if (dfn[edges[i].to] == 0)
                up[0][edges[i].to] = u, prefix[edges[i].to] = prefix[u] + edges[i].weight, tarjan(edges[i].to, u);
            else if (dfn[edges[i].to] < dfn[u])
            {
                loops[++ncnt] = 0LL + prefix[u] - prefix[edges[i].to] + edges[i].weight;
                for (int pt = u, pre; pt != edges[i].to;)
                    G[edges[i].to].push_back(pt), aff[pt] = ncnt, pre = up[0][pt], up[0][pt] = edges[i].to, pt = pre;
            }
        }
    if (up[0][u] == fa)
        G[fa].push_back(u);
}

void dfs_collect(int u, int fa)
{
    dep[u] = dep[fa] + 1;
    for (int i = 0, siz = G[u].size(); i < siz; i++)
        if (G[u][i] != fa)
            dfs_collect(G[u][i], u);
}

ll query(int x, int y)
{
    if (dep[x] < dep[y])
        swap(x, y);
    int u = x, v = y;
    for (int i = 14; i >= 0; i--)
        if (dep[up[i][x]] >= dep[y])
            x = up[i][x];
    if (x == y)
        return dist[u] - dist[v];
    for (int i = 14; i >= 0; i--)
        if (up[i][x] != up[i][y])
            x = up[i][x], y = up[i][y];
    if (aff[x] && aff[x] == aff[y])
        return dist[u] - dist[x] + dist[v] - dist[y] + min(llabs(prefix[x] - prefix[y]), loops[aff[x]] - llabs(prefix[x] - prefix[y]));
    return dist[u] + dist[v] - (dist[up[0][x]] << 1);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1, u, v, w; i <= m; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
    shortest_path(1), tarjan(1, 0);
    dfs_collect(1, 0);
    for (int i = 1; i <= 14; i++)
        for (int j = 1; j <= ptot; j++)
            up[i][j] = up[i - 1][up[i - 1][j]];
    while (q--)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        printf("%lld\n", query(x, y));
    }
    return 0;
}