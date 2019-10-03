// CH6B02.cpp
#include <bits/stdc++.h>
#define pr pair<int, int>

using namespace std;

const int MAX_N = 1e6 + 200;

int head[MAX_N], current, n, m, opt[MAX_N], src_pt, dist[MAX_N];
bool vis[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N * 20];

void addpath(int src, int dst, int weight)
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

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++)
        scanf("%d", &opt[i]), src_pt = (opt[i] == 0) ? i : src_pt;
    for (int i = 1; i <= n; i++)
        for (int level = 0; level < m; level++)
        {
            if (level < m - 1)
                addpath(i + level * n, i + (level + 1) * n, 1);
            if (level > 0)
                addpath(i + level * n, i + (level - 1) * n, 1);
        }
    for (int i = 1; i <= n; i++)
        for (int level = 0; level < m; level++)
            if (opt[level] != 0 && i + opt[level] <= n && i + opt[level] >= 1)
                addpath(i + level * n, i + opt[level] + level * n, 2 * abs(opt[level]));
    shortest_path(1 + src_pt * n);
    int ans = 0x7fffffff;
    for (int i = 0; i < m; i++)
        ans = min(ans, dist[n + i * n]);
    if (ans == 0x3f3f3f3f)
        puts("-1");
    else
        printf("%d", ans);
    return 0;
}