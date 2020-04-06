// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e4 + 200;

int n, head[MAX_N], current, ai[MAX_N], siz[MAX_N], dep[MAX_N];

inline char gc()
{
    static char buf[1000000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++;
}

int read()
{
    int x = 0, f = 1;
    char ch = gc();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = gc();
    }
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + ch - '0', ch = gc();
    return f * x;
}

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int root, val, dists[2][MAX_N];

void dfs(int u, int fa, int dist)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u, dist + 1);
    if (dist > val)
        val = dist, root = u;
}

void process(int u, int id, int fa)
{
    dists[id][u] = dists[id][fa] + 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            process(edges[i].to, id, u);
}

int main()
{
    memset(head, -1, sizeof(head));
    n = read();
    for (int i = 1; i <= n; i++)
        ai[i] = read();
    for (int i = 1, u, v; i <= n - 1; i++)
        u = read(), v = read(), addpath(u, v), addpath(v, u);
    int A, B;
    dfs(1, 0, 1), A = root, val = 0;
    dfs(A, 0, 1), B = root, val = 0;
    process(A, 0, 0), process(B, 1, 0);
    long long ans = 0;
    for (int i = 1; i <= n; i++)
        ans = max(ans, 1LL * ai[i] * (max(dists[0][i], dists[1][i]) - 1));
    printf("%lld\n", ans);
    return 0;
}