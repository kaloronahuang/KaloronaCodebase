// P3659.cpp
#include <bits/stdc++.h>
#define ll long long
#define pr pair<ll, int>

using namespace std;

const int MAX_N = 110;

const int dx[16] = {-2, -1, 1, 2, 2, 1, -1, -2, 0, 1, 0, -1, 0, 3, 0, -3}, dy[16] = {1, 2, 2, 1, -1, -2, -2, -1, 1, 0, -1, 0, 3, 0, -3, 0};

int n, T, cost[MAX_N][MAX_N], head[MAX_N * MAX_N], current;
ll dist[MAX_N * MAX_N];
bool vis[MAX_N * MAX_N];

struct edge
{
    int to, nxt;
    ll weight;
} edges[MAX_N * MAX_N * MAX_N];

void addpath(int src, int dst, ll weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void shortest_path(int src)
{
    memset(dist, 0x3f, sizeof(dist));
    priority_queue<pr> pq;
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
}

int getId(int x, int y) { return (x - 1) * n + y; }

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &T);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", &cost[i][j]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            for (int level = 0; level < 16; level++)
            {
                int sx = i + dx[level], sy = j + dy[level];
                if (sx <= n && sx >= 1 && sy <= n && sy >= 1)
                    addpath(getId(i, j), getId(sx, sy), 3 * T + cost[sx][sy]);
            }
    shortest_path(1);
    ll ans = dist[getId(n, n)];
    if (n >= 2)
        ans = min(ans, dist[getId(n - 1, n)] + T);
    if (n >= 2)
        ans = min(ans, dist[getId(n, n - 1)] + T);
    if (n >= 3)
        ans = min(ans, dist[getId(n, n - 2)] + 2 * T);
    if (n >= 3)
        ans = min(ans, dist[getId(n - 2, n)] + 2 * T);
    if (n >= 2)
        ans = min(ans, dist[getId(n - 1, n - 1)] + 2 * T);
    printf("%lld", ans);
    return 0;
}