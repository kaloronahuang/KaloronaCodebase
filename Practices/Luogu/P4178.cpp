// P4178.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e5 + 200, MAX_DOM = 20000;

int n, k, head[MAX_N], current, siz[MAX_N], nodes[MAX_DOM];
bool tag[MAX_N];
ll ans;

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

inline int lowbit(int x) { return x & -x; }

void update(int x, int d)
{
    for (; x <= k; x += lowbit(x))
        nodes[x] += d;
}

int query(int qx, int ret = 0)
{
    for (; qx > 0; qx -= lowbit(qx))
        ret += nodes[qx];
    return ret;
}

int root, rt_val;

void find_root(int u, int fa, int capacity)
{
    siz[u] = 1;
    int mx = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && tag[edges[i].to] == false)
        {
            find_root(edges[i].to, u, capacity);
            siz[u] += siz[edges[i].to], mx = max(siz[edges[i].to], mx);
        }
    if (max(capacity - siz[u], mx) < rt_val)
        root = u, rt_val = max(capacity - siz[u], mx);
}

int find_root(int u, int capacity)
{
    root = 0, rt_val = 0x3f3f3f3f;
    find_root(u, 0, capacity);
    return root;
}

void dfs_collect(int u, int fa, int dist)
{
    if (dist > k)
        return;
    ans += query(k - dist) + (dist <= k);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && tag[edges[i].to] == false)
            dfs_collect(edges[i].to, u, dist + edges[i].weight);
}

void dfs_apply(int u, int fa, int dist)
{
    if (dist > k)
        return;
    update(dist, 1);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && tag[edges[i].to] == false)
            dfs_apply(edges[i].to, u, dist + edges[i].weight);
}

void solve(int u, int capacity)
{
    memset(nodes, 0, sizeof(nodes));
    u = find_root(u, capacity);
    tag[u] = true;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (!tag[edges[i].to])
        {
            dfs_collect(edges[i].to, u, edges[i].weight);
            dfs_apply(edges[i].to, u, edges[i].weight);
        }
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (!tag[edges[i].to])
            solve(edges[i].to, siz[edges[i].to]);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1, u, v, w; i <= n - 1; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
    scanf("%d", &k);
    solve(1, n), printf("%lld\n", ans);
    return 0;
}