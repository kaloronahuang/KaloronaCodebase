// BZ1316.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 10100, RANGE = 1e6 + 20;

typedef pair<int, int> pii;

int n, q, head[MAX_N], current, dist[MAX_N], siz[MAX_N], queries[MAX_N];
bool tag[MAX_N], ansBox[MAX_N];
multiset<int> ms;

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

int root, max_val = 0x7fffffff;

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void dfs(int u, int fa, int capacity)
{
    int mpart = 0;
    siz[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && !tag[edges[i].to])
            dfs(edges[i].to, u, capacity), siz[u] += siz[edges[i].to], mpart = max(mpart, siz[edges[i].to]);
    mpart = max(mpart, capacity - siz[u]);
    if (mpart < max_val)
        max_val = mpart, root = u;
}

int findRoot(int entryPoint, int capacity) { return root = 0, max_val = 0x7fffffff, dfs(entryPoint, 0, capacity), root; }

void mark(int u, int fa, int delta)
{
    if (delta == 1)
        ms.insert(dist[u]);
    else
        ms.erase(ms.find(dist[u]));
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && !tag[edges[i].to])
            dist[edges[i].to] = dist[u] + edges[i].weight, mark(edges[i].to, u, delta);
}

void collect(int u, int fa)
{
    for (int i = 1; i <= q; i++)
        if (queries[i] >= dist[u])
            ansBox[i] |= ms.find(queries[i] - dist[u]) != ms.end();
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && !tag[edges[i].to])
            collect(edges[i].to, u);
}

void solve(int u, int capacity)
{
    tag[u] = true, ms.insert(0);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (!tag[edges[i].to])
            dist[edges[i].to] = edges[i].weight, mark(edges[i].to, u, 1);
    for (int i = 1; i <= q; i++)
        ansBox[i] |= ms.find(queries[i]) != ms.end();
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (!tag[edges[i].to])
            mark(edges[i].to, u, -1), collect(edges[i].to, u), mark(edges[i].to, u, 1);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (!tag[edges[i].to])
            dist[edges[i].to] = edges[i].weight, mark(edges[i].to, u, -1);
    ms.clear();
    for (int i = head[u], tmp; i != -1; i = edges[i].nxt)
        if (!tag[edges[i].to])
            tmp = siz[edges[i].to], solve(findRoot(edges[i].to, tmp), tmp);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &q);
    for (int i = 1, u, v, w; i <= n - 1; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
    for (int i = 1; i <= q; i++)
        scanf("%d", &queries[i]);
    solve(findRoot(1, n), n);
    for (int i = 1; i <= q; i++)
        puts(ansBox[i] ? "Yes" : "No");
    return 0;
}