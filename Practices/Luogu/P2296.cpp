// P2296.cpp
#include <bits/stdc++.h>
#define pr pair<int, int>

using namespace std;

const int MAX_N = 1e4 + 200, MAX_E = 2e5 + 200;

int head[MAX_N], current, n, m, st, ed, ui[MAX_E], vi[MAX_E], deg[MAX_N], odeg[MAX_N], dist[MAX_N];
bool vis[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_E];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void bfs()
{
    queue<int> q;
    q.push(ed);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edges[i].nxt)
        {
            deg[edges[i].to]++;
            if (deg[edges[i].to] == 1)
                q.push(edges[i].to);
        }
    }
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
            if (dist[edges[i].to] > dist[u] + 1)
                dist[edges[i].to] = dist[u] + 1, pq.push(make_pair(-dist[edges[i].to], edges[i].to));
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
        scanf("%d%d", &ui[i], &vi[i]), addpath(vi[i], ui[i]), odeg[ui[i]]++;
    scanf("%d%d", &st, &ed);
    bfs();
    memset(head, -1, sizeof(head)), current = 0;
    for (int i = 1; i <= m; i++)
        if (odeg[ui[i]] == deg[ui[i]] && odeg[vi[i]] == deg[vi[i]])
            addpath(ui[i], vi[i]);
    shortest_path(st), printf("%d\n", dist[ed] == 0x3f3f3f3f ? -1 : dist[ed]);
    return 0;
}