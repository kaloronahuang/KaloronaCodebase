// P5122.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, MAX_E = 3e5 + 200;

int n, m, k, head[MAX_N], current, dist[MAX_N];
bool vis[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_E << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void spfa(int entry_point)
{
    memset(dist, 0x3f, sizeof(dist));
    queue<int> q;
    q.push(entry_point), dist[entry_point] = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), vis[u] = false;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[edges[i].to] > dist[u] + edges[i].weight)
            {
                dist[edges[i].to] = dist[u] + edges[i].weight;
                if (vis[edges[i].to] == false)
                    q.push(edges[i].to), vis[edges[i].to] = true;
            }
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1, u, v, w; i <= m; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w), addpath(u + n, v + n, w), addpath(v + n, u + n, w);
    for (int i = 1, id, val; i <= k; i++)
        scanf("%d%d", &id, &val), addpath(id, id + n, -val);
    spfa(n);
    for (int i = 1; i < n; i++)
        if (dist[i] >= dist[i + n])
            puts("1");
        else
            puts("0");
    return 0;
}