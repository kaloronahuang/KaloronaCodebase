// P1099.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 3030;
int head[MAX_N], dist[MAX_N], root, fat[MAX_N], bottom, n, s, rdist[MAX_N];
struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];
int farest, val, current, tmpx, tmpy, tmpz, color[MAX_N];

void addPath(int u, int v, int w)
{
    edges[current].to = v, edges[current].nxt = head[u];
    edges[current].weight = w, head[u] = current++;
}

void dfs_diameter(int u, int fa, int di)
{
    if (di > val)
        val = di, farest = u;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs_diameter(edges[i].to, u, di + edges[i].weight);
}

void initialize(int u)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fat[u])
            fat[edges[i].to] = u, rdist[edges[i].to] = rdist[u] + edges[i].weight, initialize(edges[i].to);
}

int getDist(int u)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fat[u])
            getDist(edges[i].to), dist[u] = max(dist[u], dist[edges[i].to] + edges[i].weight);
    return dist[u];
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &s);
    for (int i = 1; i <= n - 1; i++)
        scanf("%d%d%d", &tmpx, &tmpy, &tmpz), addPath(tmpx, tmpy, tmpz), addPath(tmpy, tmpx, tmpz);
    dfs_diameter(1, 0, 0), root = farest;
    farest = val = 0;
    dfs_diameter(root, 0, 0), bottom = farest;
    initialize(root);
    for (int u = bottom; u != 0; u = fat[u])
        color[u] = true;
    for (int u = bottom; u != 0; u = fat[u])
    {
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (!color[edges[i].to])
                dist[u] = max(dist[u], getDist(edges[i].to) + edges[i].weight);
    }
    int ans = val;
    for (int u = bottom; u != 0; u = fat[u])
    {
        int center_dist = max(val - rdist[u], dist[u]);
        for (int t = u; t != 0; t = fat[t])
        {
            int curt_dist = rdist[u] - rdist[t];
            if (curt_dist > s)
                break;
            ans = min(ans, max(center_dist, max(dist[t], rdist[t])));
            center_dist = max(center_dist, dist[t]);
        }
        ans = min(ans, max(max(val - rdist[u], dist[u]), rdist[u]));
    }
    printf("%d", ans);
    return 0;
}