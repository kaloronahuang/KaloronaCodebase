// P2149.cpp
#include <bits/stdc++.h>
#define pr pair<int, int>

using namespace std;

const int MAX_N = 2550;

int head[MAX_N], current, n, m, sx, sy, dx, dy, deg[MAX_N], dist[5][MAX_N], dest[MAX_N];
bool vis[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N * MAX_N];
vector<edge> G[MAX_N];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void shortest_path(int id, int src)
{
    memset(dist[id], 0x3f, sizeof(dist[id]));
    memset(vis, false, sizeof(vis));
    priority_queue<pr> pq;
    dist[id][src] = 0, pq.push(make_pair(0, src));
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[id][edges[i].to] > dist[id][u] + edges[i].weight)
                dist[id][edges[i].to] = dist[id][u] + edges[i].weight, pq.push(make_pair(-dist[id][edges[i].to], edges[i].to));
    }
}

void toposort()
{
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (deg[i] == 0)
            q.push(i);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = 0, siz = G[u].size(); i < siz; i++)
        {
            int v = G[u][i].to;
            dest[v] = max(dest[v], dest[u] + G[u][i].weight);
            if (--deg[v] == 0)
                q.push(v);
        }
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d%d%d%d", &n, &m, &sx, &sy, &dx, &dy);
    for (int i = 1, u, v, w; i <= m; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
    // preprocess the paths;
    shortest_path(1, sx), shortest_path(2, sy), shortest_path(3, dx), shortest_path(4, dy);
    // get the intersect;
    for (int u = 1; u <= n; u++)
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[1][u] + edges[i].weight + dist[2][edges[i].to] == dist[1][sy])
                if (dist[3][u] + edges[i].weight + dist[4][edges[i].to] == dist[3][dy])
                    G[u].push_back(edge{edges[i].to, 0, edges[i].weight}), deg[edges[i].to]++;
    toposort();
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        ans = max(ans, dest[i]);
        while (!G[i].empty())
            G[i].pop_back();
    }
    memset(deg, 0, sizeof(deg)), memset(dest, 0, sizeof(dest));
    for (int u = 1; u <= n; u++)
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[1][u] + edges[i].weight + dist[2][edges[i].to] == dist[1][sy])
                if (dist[4][u] + edges[i].weight + dist[3][edges[i].to] == dist[3][dy])
                    G[u].push_back(edge{edges[i].to, 0, edges[i].weight}), deg[edges[i].to]++;
    toposort();
    for (int i = 1; i <= n; i++)
        ans = max(ans, dest[i]);
    printf("%d", ans);
    return 0;
}