// CH6202.cpp
// Create the DAG of the shortest path graph;
#include <bits/stdc++.h>
#define ll long long
#define pr pair<int, int>

using namespace std;

const int MAX_N = 2020, MAX_M = 500005;
const ll p = (1LL << 31) - 1;

int n, m, current, head[MAX_M << 1], dist[MAX_N], d[MAX_N][MAX_N], id[MAX_N];
bool vis[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_M << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void djisktra()
{
    memset(dist, 0x3f, sizeof(dist));
    priority_queue<pr> pq;
    pq.push(make_pair(0, 1)), dist[1] = 0;

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

bool compare(int a, int b) { return dist[a] < dist[b]; }

int main()
{
    memset(head, -1, sizeof(head)), memset(d, 0x3f, sizeof(d));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        id[i] = i, d[i][i] = 0;
    for (int i = 1, x, y, z; i <= m; i++)
        scanf("%d%d%d", &x, &y, &z), addpath(x, y, z), addpath(y, x, z), d[x][y] = d[y][x] = min(d[x][y], z);
    djisktra();
    sort(id + 1, id + 1 + n, compare);
    ll ans = 1;
    for (int i = 2; i <= n; i++)
    {
        ll now = 0;
        for (int j = 1; j < i; j++)
            if (dist[id[j]] + d[id[i]][id[j]] == dist[id[i]])
                now++;
        ans = ans * now % p;
    }
    printf("%lld", ans);
    return 0;
}