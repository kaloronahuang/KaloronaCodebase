// P3385.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2200;

int head[MAX_N], current, n, m, T, dist[MAX_N], cnt[MAX_N];
bool vis[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 2];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

bool spfa()
{
    memset(vis, false, sizeof(vis));
    memset(dist, 0x3f, sizeof(dist));
    memset(cnt, 0, sizeof(cnt));
    queue<int> q;
    q.push(1), dist[1] = 0, vis[1] = true;
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), vis[u] = false;
        if (++cnt[u] >= n)
            return true;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[edges[i].to] > dist[u] + edges[i].weight)
            {
                dist[edges[i].to] = dist[u] + edges[i].weight;
                if (!vis[edges[i].to])
                    q.push(edges[i].to), vis[edges[i].to] = true;
            }
    }
    return false;
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        memset(head, -1, sizeof(head)), current = 0;
        scanf("%d%d", &n, &m);
        for (int i = 1, u, v, w; i <= m; i++)
        {
            scanf("%d%d%d", &u, &v, &w), addpath(u, v, w);
            if (w >= 0)
                addpath(v, u, w);
        }
        puts(spfa() ? "YE5" : "N0");
    }
    return 0;
}