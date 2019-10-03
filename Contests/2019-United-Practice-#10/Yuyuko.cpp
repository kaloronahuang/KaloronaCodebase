// Yuyuko.cpp
#include <bits/stdc++.h>
#define pr pair<int, int>

using namespace std;

const int MAX_N = 3e4 + 200, MAX_E = 1e5 + 200;

int head[MAX_N], n, m, current, dist[MAX_N];

struct edge
{
    int to, nxt, weight;
    bool tag;
} edges[MAX_E << 1];

bool vis[MAX_N];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void shortest_path()
{
    memset(vis, false, sizeof(vis)), memset(dist, 0x3f, sizeof(dist));
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
            if (edges[i].tag == false && dist[edges[i].to] > dist[u] + edges[i].weight)
                dist[edges[i].to] = dist[u] + edges[i].weight, pq.push(make_pair(-dist[edges[i].to], edges[i].to));
    }
}

int main()
{
    freopen("zaw.in", "r", stdin);
    freopen("zaw.out", "w", stdout);
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v, a, b; i <= m; i++)
        scanf("%d%d%d%d", &u, &v, &a, &b), addpath(u, v, a), addpath(v, u, b);
    int ans = 0x7fffffff;
    for (int i = head[1]; i != -1; i = edges[i].nxt)
    {
        // set this edge shit;
        edges[i].tag = edges[i ^ 1].tag = true;
        shortest_path();
        edges[i].tag = edges[i ^ 1].tag = false;
        if (dist[edges[i].to] != 0x3f3f3f3f)
            ans = min(ans, dist[edges[i].to] + edges[i ^ 1].weight);
    }
    printf("%d", ans == 0x7fffffff ? -1 : ans);
    return 0;
}