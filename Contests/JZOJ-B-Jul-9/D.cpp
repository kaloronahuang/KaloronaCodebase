// D.cpp
#include <bits/stdc++.h>
#define pr pair<int, int>

using namespace std;

const int MAX_N = 1100, INF = 0x3f3f3f3f;

int mp[MAX_N][MAX_N], dist[MAX_N][MAX_N], head[MAX_N], current;
int distances[MAX_N], vis[MAX_N], n, m, k;

struct edge
{
    int to, nxt, weight;
} edges[MAX_N * 10];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void djisktra()
{
    memset(distances, 0x3f, sizeof(distances));
    priority_queue<pr> q;
    q.push(make_pair(0, 1)), distances[1] = 0;
    while (!q.empty())
    {
        int u = q.top().second;
        q.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (distances[edges[i].to] > distances[u] + edges[i].weight)
                distances[edges[i].to] = distances[u] + edges[i].weight, q.push(make_pair(-distances[edges[i].to], edges[i].to));
    }
}

int main()
{
    memset(head, -1, sizeof(head)), memset(mp, 0x3f, sizeof(mp));
    memset(dist, 0x3f, sizeof(dist));
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1, u, v, len; i <= m; i++)
        scanf("%d%d%d", &u, &v, &len), mp[u][v] = min(mp[u][v], len), dist[u][v] = min(dist[u][v], len);
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    for (int layer = 0; layer <= k; layer++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (mp[i][j] != INF)
                {
                    if (dist[i][j] != INF && dist[j][i] != INF)
                        addpath(layer * n + i, layer * n + j, mp[i][j]);
                    else if (layer != n)
                        addpath(layer * n + i, (layer + 1) * n + j, 2 * mp[i][j]);
                }
    djisktra();
    int ans = INF;
    for (int i = 0; i <= k; i++)
        ans = min(ans, distances[i * n + n]);
    if (ans == INF)
        puts("-1");
    else
        printf("%d", ans);
    return 0;
}