// LOJ2386.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, head[MAX_N], current, g[MAX_N], dep[MAX_N], deg[MAX_N], ans[MAX_N], siz[MAX_N], nodes[MAX_N << 1];
bool tag[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

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

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u, int fa)
{
    if (deg[u] == 1)
        g[u] = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u), g[u] = min(g[u], g[edges[i].to] + 1);
}

void overlap(int u, int fa)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            g[edges[i].to] = min(g[edges[i].to], g[u] + 1), overlap(edges[i].to, u);
}

int root, root_val;

void findRoot(int u, int fa, int capacity)
{
    siz[u] = 1;
    int max_com = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && !tag[edges[i].to])
            findRoot(edges[i].to, u, capacity), max_com = max(max_com, siz[edges[i].to]), siz[u] += siz[edges[i].to];
    if (max(max_com, capacity - siz[u]) < root_val)
        root_val = max(max_com, capacity - siz[u]), root = u;
}

int findRoot(int entry, int capacity) { return root = 0, root_val = 0x7fffffff, findRoot(entry, 0, capacity), root; }

inline int lowbit(int x) { return x & (-x); }

void update(int x, int d)
{
    x += MAX_N;
    for (; x <= MAX_N << 1; x += lowbit(x))
        nodes[x] += d;
}

int query(int x, int ret = 0)
{
    x += MAX_N;
    for (; x; x -= lowbit(x))
        ret += nodes[x];
    return ret;
}

void collect(int u, int fa, int dep)
{
    ans[u] += query(dep);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && !tag[edges[i].to])
            collect(edges[i].to, u, dep + 1);
}

void confirm(int u, int fa, int dep)
{
    update(g[u] - dep, 2 - deg[u]);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && !tag[edges[i].to])
            confirm(edges[i].to, u, dep + 1);
}

void clear(int u, int fa, int dep)
{
    update(g[u] - dep, deg[u] - 2), siz[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && !tag[edges[i].to])
            clear(edges[i].to, u, dep + 1), siz[u] += siz[edges[i].to];
}

int cnt;

void solve(int u, int capacity)
{
    tag[u] = true; //, printf("TAGGED Another One: %d\n", cnt), cnt++;
    stack<int> sons;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (!tag[edges[i].to])
            collect(edges[i].to, u, 1), confirm(edges[i].to, u, 1), sons.push(edges[i].to);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (!tag[edges[i].to])
            clear(edges[i].to, u, 1);
    update(g[u], 2 - deg[u]);
    while (!sons.empty())
    {
        int v = sons.top();
        collect(v, u, 1), confirm(v, u, 1), sons.pop();
    }
    ans[u] += query(0), update(g[u], deg[u] - 2);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (!tag[edges[i].to])
            clear(edges[i].to, u, 1);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (!tag[edges[i].to])
            solve(findRoot(edges[i].to, siz[edges[i].to]), siz[edges[i].to]);
}

int main()
{
    /*
    freopen("2.in", "r", stdin);
    freopen("2.out", "w", stdout);
    */
    memset(head, -1, sizeof(head)), memset(g, 0x3f, sizeof(g));
    n = read();
    for (int i = 1, u, v; i <= n - 1; i++)
        u = read(), v = read(), addpath(u, v), addpath(v, u), deg[u]++, deg[v]++;
    dfs(1, 0), overlap(1, 0), solve(findRoot(1, n), n);
    for (int i = 1; i <= n; i++)
        if (deg[i] == 1)
            puts("1");
        else
            printf("%d\n", ans[i]);
    return 0;
}