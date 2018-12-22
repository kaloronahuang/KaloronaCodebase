// BZ2200.cpp
#include <iostream>
#include <queue>
#include <cstring>
#include <cstdio>
#define pr pair<int, int>
using namespace std;
const int MX_N = 25020;
int head[MX_N], current, dist[MX_N], T, R, P, S, fa[MX_N], deg[MX_N];
struct edge
{
    int to, nxt, weight;
} edges[500000];
void addpath(int src, int dst, int w)
{
    edges[current].to = dst, edges[current].weight = w;
    edges[current].nxt = head[src], head[src] = current++;
}
bool vis[MX_N];
queue<int> topoq;
void djisktra(int bk)
{
    priority_queue<pr, vector<pr>, greater<pr> > q;
    for (int i = 1; i <= T; i++)
        if (fa[i] == bk)
            q.push(make_pair(dist[i], i));
    while (!q.empty())
    {
        pr ct = q.top();
        q.pop();
        int curt = ct.second, val = ct.first;
        if (vis[curt])
            continue;
        vis[curt] = true;
        for (int i = head[curt]; i != -1; i = edges[i].nxt)
            if (dist[edges[i].to] > dist[curt] + edges[i].weight && fa[curt] == fa[edges[i].to])
                dist[edges[i].to] = dist[curt] + edges[i].weight, q.push(make_pair(dist[edges[i].to], edges[i].to));
            else if (fa[curt] != fa[edges[i].to])
            {
                dist[edges[i].to] = min(dist[edges[i].to], dist[curt] + edges[i].weight);
                deg[fa[edges[i].to]]--;
                if (deg[fa[edges[i].to]] == 0)
                    topoq.push(fa[edges[i].to]);
            }
    }
}
void dfs(int u, int id)
{
    if (vis[u])
        return;
    vis[u] = true, fa[u] = id;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        dfs(edges[i].to, id);
}
int blocktot;
void toposort()
{
    dist[S] = 0;
    for (int i = 1; i <= blocktot; i++)
        if (deg[i] == 0)
            topoq.push(i);
    while (!topoq.empty())
    {
        djisktra(topoq.front());
        topoq.pop();
    }
}
int main()
{
    scanf("%d%d%d%d", &T, &R, &P, &S);
    for (int i = 0; i <= T; i++)
        head[i] = -1;
    for (int i = 0; i < R; i++)
    {
        int src, dst, w;
        scanf("%d%d%d", &src, &dst, &w);
        addpath(src, dst, w), addpath(dst, src, w);
    }
    for (int i = 1; i <= T; i++)
        if (!vis[i])
            dfs(i, ++blocktot);
    memset(dist, 0x3f, sizeof(dist));
    memset(vis, false, sizeof(vis));
    for (int i = 0; i < P; i++)
    {
        int src, dst, w;
        scanf("%d%d%d", &src, &dst, &w);
        addpath(src, dst, w);
        deg[fa[dst]]++;
    }
    toposort();
    for (int i = 1; i <= T; i++)
        if (dist[i] >= 1000000000)
            printf("NO PATH\n");
        else
            printf("%d\n", dist[i]);
    return 0;
}