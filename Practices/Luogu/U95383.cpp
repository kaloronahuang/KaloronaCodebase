// U95383.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, m, Q, head[MAX_N], current, dist[MAX_N], fa[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 2];

struct seg
{
    int from, to, weight;
    bool operator<(const seg &nd) const { return weight < nd.weight; }
} segs[MAX_N << 2];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

void dfs(int u, int fat)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fat)
            dist[edges[i].to] = dist[u] ^ edges[i].weight, dfs(edges[i].to, u);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &m, &Q);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &segs[i].from, &segs[i].to, &segs[i].weight);
    sort(segs + 1, segs + 1 + m);
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    for (int i = 1; i <= m; i++)
        if (find(segs[i].from) != find(segs[i].to))
        {
            addpath(segs[i].from, segs[i].to, segs[i].weight), addpath(segs[i].to, segs[i].from, segs[i].weight);
            fa[find(segs[i].from)] = find(segs[i].to);
        }
    dfs(1, 0);
    while (Q--)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        printf("%d\n", dist[x] ^ dist[y]);
    }
    return 0;
}