// POJ3463.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e4 + 200;

int T, n, m, S, F, head[MAX_N], current, prod[MAX_N][2], dist[MAX_N][2];
bool vis[MAX_N][2];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

struct triple
{
    int dist, x, id;
    bool operator<(const triple &tr) const { return dist > tr.dist; }
    triple() {}
    triple(int d, int x_, int id_) : dist(d), x(x_), id(id_) {}
};

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void reset() { memset(head, -1, sizeof(head)), current = 0; }

void shortest_path()
{
    memset(dist, 0x3f, sizeof(dist)), memset(prod, 0, sizeof(prod));
    memset(vis, false, sizeof(vis));
    priority_queue<triple> pq;
    pq.push(triple(0, S, 0)), dist[S][0] = 0, prod[S][0] = 1;

    while (!pq.empty())
    {
        int u = pq.top().x, id = pq.top().id;
        pq.pop();
        if (vis[u][id])
            continue;
        vis[u][id] = true;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
        {
            int v = edges[i].to, wgt = dist[u][id] + edges[i].weight;
            if (wgt < dist[v][0])
            {
                dist[v][1] = dist[v][0];
                prod[v][1] = prod[v][0];
                dist[v][0] = wgt, prod[v][0] = prod[u][id];
                pq.push(triple(dist[v][0], v, 0));
                pq.push(triple(dist[v][1], v, 1));
                continue;
            }
            if (wgt == dist[v][0])
            {
                prod[v][0] += prod[u][id];
                continue;
            }
            if (wgt < dist[v][1])
            {
                dist[v][1] = wgt;
                prod[v][1] = prod[u][id];
                pq.push(triple(dist[v][1], v, 1));
                continue;
            }
            if (wgt == dist[v][1])
            {
                prod[v][1] += prod[u][id];
                continue;
            }
        }
    }
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        reset();
        scanf("%d%d", &n, &m);

        for (int i = 1, u, v, w; i <= m; i++)
            scanf("%d%d%d", &u, &v, &w), addpath(u, v, w);
        scanf("%d%d", &S, &F);
        shortest_path();
        int ans = prod[F][0];
        if (dist[F][1] - 1 == dist[F][0])
            ans += prod[F][1];
        printf("%d\n", ans);
    }
    return 0;
}