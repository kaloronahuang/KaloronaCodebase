// CF757F.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200;

typedef long long ll;
typedef pair<ll, int> pli;

const ll INF = 0x3f3f3f3f3f3f3f3f;

int head[MAX_N], current, n, m, start_pt, deg[MAX_N], fa[20][MAX_N], root, dep[MAX_N], siz[MAX_N], gans;
ll dist[MAX_N];
bool vis[MAX_N];
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

void shortestPath()
{
    memset(dist, 0x3f, sizeof(dist));
    priority_queue<pli> pq;
    pq.push(make_pair(0, start_pt)), dist[start_pt] = 0;
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
}

int getLCA(int x, int y)
{
    if (dep[x] < dep[y])
        swap(x, y);
    int delta = dep[x] - dep[y];
    for (int i = 19; i >= 0; i--)
        if (delta & (1 << i))
            x = fa[i][x];
    if (x == y)
        return x;
    for (int i = 19; i >= 0; i--)
        if (fa[i][x] != fa[i][y])
            x = fa[i][x], y = fa[i][y];
    return fa[0][x];
}

void toposort()
{
    memset(head, -1, sizeof(head)), current = 0;
    queue<int> q;
    for (int u = 1; u <= n; u++)
        if (dist[u] != INF && deg[u] == 0)
            q.push(u), fa[0][u] = root;
        else
            fa[0][u] = -1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), dep[u] = dep[fa[0][u]] + 1;
        for (int i = 1; (1 << i) < dep[u]; i++)
            fa[i][u] = fa[i - 1][fa[i - 1][u]];
        for (int i = 0, siz = G[u].size(); i < siz; i++)
        {
            if (fa[0][G[u][i]] == -1)
                fa[0][G[u][i]] = u;
            else
                fa[0][G[u][i]] = getLCA(fa[0][G[u][i]], u);
            if (--deg[G[u][i]] == 0)
                q.push(G[u][i]);
        }
    }
}

void dfs(int u)
{
    siz[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        dfs(edges[i].to), siz[u] += siz[edges[i].to];
    if (u != root && u != start_pt)
        gans = max(gans, siz[u]);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &m, &start_pt);
    for (int i = 1, u, v, w; i <= m; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
    shortestPath(), root = n + 1, dep[root] = 1;
    for (int u = 1; u <= n; u++)
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[edges[i].to] == dist[u] + edges[i].weight)
                G[u].push_back(edges[i].to), deg[edges[i].to]++;
    toposort();
    for (int i = 1; i <= n; i++)
        if (fa[0][i] != -1)
            addpath(fa[0][i], i, 0);
    dfs(root), printf("%d\n", gans);
    return 0;
}