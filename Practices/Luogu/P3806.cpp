// P3806.cpp
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 10100, Q_RANGE = 10001000, INF = 0x3f3f3f3f;

int head[MAX_N], current, n, m, tmpx, tmpy, tmpz, k;
int root, root_weight, size[MAX_N], capacity, dtot;
int distances[MAX_N], ans[MAX_N], judge[Q_RANGE];
int queries[MAX_N], q[MAX_N];
bool vis[MAX_N];
struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void get_root(int u, int fa)
{
    size[u] = 1;
    int max_siz = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        if (edges[i].to == fa || vis[edges[i].to])
            continue;
        get_root(edges[i].to, u), size[u] += size[edges[i].to];
        max_siz = max(max_siz, size[edges[i].to]);
    }
    max_siz = max(max_siz, capacity - size[u]);
    if (max_siz < root_weight)
        root_weight = max_siz, root = u;
}

void getDistance(int u, int fa, int dist)
{
    distances[++dtot] = dist;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && !vis[edges[i].to])
            getDistance(edges[i].to, u, dist + edges[i].weight);
}

void solve(int u)
{
    int p = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        if (vis[edges[i].to])
            continue;
        dtot = 0;
        getDistance(edges[i].to, u, edges[i].weight);
        for (int j = dtot; j; j--)
            for (int k = 1; k <= m; k++)
                if (queries[k] >= distances[j])
                    ans[k] |= judge[queries[k] - distances[j]];
        for (int j = dtot; j; j--)
            q[++p] = distances[j], judge[distances[j]] = true;
    }
    for (int i = 1; i <= p; i++)
        judge[q[i]] = false;
}

void pdq(int u)
{
    vis[u] = judge[0] = 1;
    solve(u);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        if (vis[edges[i].to])
            continue;
        if (size[u] > size[edges[i].to])
            capacity = size[edges[i].to];
        else
            capacity = capacity - size[edges[i].to];
        root = 0, root_weight = n;
        get_root(edges[i].to, 0);
        pdq(edges[i].to);
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n - 1; i++)
    {
        scanf("%d%d%d", &tmpx, &tmpy, &tmpz);
        addpath(tmpx, tmpy, tmpz), addpath(tmpy, tmpx, tmpz);
    }
    for (int i = 1; i <= m; i++)
        scanf("%d", &queries[i]);
    capacity = root_weight = n;
    get_root(1, 0);
    pdq(root);

    for (int i = 1; i <= m; i++)
        puts(ans[i] ? "AYE" : "NAY");
    return 0;
}