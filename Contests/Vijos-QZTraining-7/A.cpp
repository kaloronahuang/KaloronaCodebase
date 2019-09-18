// A.cpp
#include <bits/stdc++.h>
#define pr pair<int, int>

using namespace std;

const int MAX_N = 1e4 + 200, MAX_E = 2e5 + 200, MAX_K = 6;

int head[MAX_N], current, n, m, k, *dist, distances[MAX_K][MAX_N], k_set[MAX_K], dist_id[MAX_N];
bool vis[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_E << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].weight = weight;
    edges[current].nxt = head[src], head[src] = current++;
}

void shortest_path(int st)
{
    memset(dist, 0x3f, sizeof(distances[0]));
    memset(vis, false, sizeof(vis));
    priority_queue<pr> pq;
    dist[st] = 0, pq.push(make_pair(0, st));
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
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= k; i++)
        scanf("%d", &k_set[i]), dist_id[k_set[i]] = i;
    for (int i = 1, u, v, w; i <= m; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
    for (int i = 1; i <= k; i++)
        dist = distances[i], shortest_path(k_set[i]);
    int gans = 0x3f3f3f3f;
    do
    {
        // insert it;
        int pans = 0;
        for (int i = 1; i < k; i++)
            pans += distances[dist_id[k_set[i]]][k_set[i + 1]];
        for (int i = 1; i <= n; i++)
            if (!dist_id[i])
                gans = min(gans, pans + distances[dist_id[k_set[1]]][i] + distances[dist_id[k_set[k]]][i]);
    } while (next_permutation(k_set + 1, k_set + 1 + k));
    printf("%d", gans);
    return 0;
}