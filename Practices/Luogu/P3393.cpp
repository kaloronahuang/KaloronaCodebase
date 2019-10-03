// P3393.cpp
#include <bits/stdc++.h>
#define ll long long
#define pr pair<ll, int>

using namespace std;

const int MAX_N = 1e5 + 200, MAX_E = 200100;

int n, m, k, s, P, Q, head[MAX_N], current, pt[MAX_N];
ll dist[MAX_N];
bool vis[MAX_N];

struct edge
{
    int from, to, nxt, weight;
} edges[MAX_E << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].from = src;
    edges[current].to = dst, edges[current].weight = weight;
    edges[current].nxt = head[src], head[src] = current++;
}

int main()
{
    memset(head, -1, sizeof(head)), memset(pt, 0x3f, sizeof(pt));
    scanf("%d%d%d%d%d%d", &n, &m, &k, &s, &P, &Q);
    queue<int> q;
    for (int i = 1, tmp; i <= k; i++)
        scanf("%d", &tmp), q.push(tmp), pt[tmp] = 0;
    for (int i = 1, u, v; i <= m; i++)
    {
        scanf("%d%d", &u, &v);
        addpath(u, v, 0), addpath(v, u, 0);
    }
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), vis[u] = false;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (pt[edges[i].to] > pt[u] + 1)
            {
                pt[edges[i].to] = pt[u] + 1;
                if (!vis[edges[i].to])
                    q.push(edges[i].to), vis[edges[i].to] = true;
            }
    }
    for (int i = 0; i < current; i++)
        if (edges[i].to != n && edges[i].to != 1)
        {
            if (pt[edges[i].to] == 0)
            {
                edges[i].weight = 0x3f3f3f3f;
                continue;
            }
            if (pt[edges[i].to] > s)
                edges[i].weight = P;
            else
                edges[i].weight = Q;
        }
    memset(dist, 0x3f, sizeof(dist));
    memset(vis, false, sizeof(vis));

    priority_queue<pr> pq;
    pq.push(make_pair(-P, 1)), dist[1] = 0;
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
    printf("%lld", dist[n]);
    return 0;
}