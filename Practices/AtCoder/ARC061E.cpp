// ARC061E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 8e5 + 200, INF = 0x3f3f3f3f;

int n, m, dist[MAX_N], ptot;
bool vis[MAX_N];
map<pair<int, int>, int> mp;

struct edge
{
    int to, nxt, weight;
};

vector<edge> G[MAX_N];

void addpath(int src, int dst, int weight) { G[src].push_back(edge{dst, 0, weight}); }

void addtube(int src, int dst, int weight)
{
    addpath(src, dst, weight), addpath(dst, src, weight);
}

void shortest_path(int src)
{
    memset(dist, 0x3f, sizeof(dist));
    priority_queue<pair<int, int> /**/> pq;
    pq.push(make_pair(0, src)), dist[src] = 0;
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (int i = 0, siz = G[u].size(); i < siz; i++)
            if (dist[G[u][i].to] > dist[u] + G[u][i].weight)
                dist[G[u][i].to] = dist[u] + G[u][i].weight, pq.push(make_pair(-dist[G[u][i].to], G[u][i].to));
    }
}

int createId(pair<int, int> pr)
{
    if (mp.count(pr) > 0)
        return mp[pr];
    return mp[pr] = ++ptot;
}

int main()
{
    scanf("%d%d", &n, &m), ptot = n;
    if (m == 0)
        puts("-1"), exit(0);
    for (int i = 1, u, v, w; i <= m; i++)
    {
        scanf("%d%d%d", &u, &v, &w);
        addtube(createId(make_pair(u, w)), createId(make_pair(v, w)), 0);
        addtube(u, createId(make_pair(u, w)), 1), addtube(createId(make_pair(v, w)), v, 1);
    }
    shortest_path(1);
    if (dist[n] == INF)
        puts("-1");
    else
        printf("%d\n", dist[n] >> 1);
    return 0;
}