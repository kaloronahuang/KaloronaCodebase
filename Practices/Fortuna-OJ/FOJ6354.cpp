// FOJ6354.cpp
#include <bits/stdc++.h>
#define pr pair<double, int>

using namespace std;

const int MAX_N = 1e5 + 200, MAX_E = 6e5 + 200;

int head[MAX_N * 3], current, n, m;
double dist[MAX_N * 3];
bool vis[MAX_N * 3];

struct edge
{
    int to, nxt;
    double weight;
} edges[MAX_E * 3];

void addpath(int src, int dst, double weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = fabs(weight), head[src] = current++;
}

void djisktra()
{
    fill(dist + 1, dist + 1 + MAX_N * 3, (double)0x3f3f3f3f);
    priority_queue<pr> pq;
    dist[1] = 0, pq.push(make_pair(0, 1));
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

int main()
{
    freopen("tiring.in", "r", stdin);
    freopen("tiring.out", "w", stdout);
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v, w; i <= m; i++)
    {
        scanf("%d%d%d", &u, &v, &w);
        addpath(u, v + n, w), addpath(u + n, v + 2 * n, 1.0 / (1.0 - w)), addpath(u + 2 * n, v, 1 - (1 / (1.0 * w)));
        swap(u, v);
        addpath(u, v + n, w), addpath(u + n, v + 2 * n, 1.0 / (1.0 - w)), addpath(u + 2 * n, v, 1 - (1 / (1.0 * w)));
    }
    djisktra();
    printf("%.3lf", min(dist[n], min(dist[n << 1], dist[3 * n])));
    return 0;
}