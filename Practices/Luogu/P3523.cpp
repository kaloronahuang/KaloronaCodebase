// P3523.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 301000, INF = 0x3f3f3f3f;

int n, m, head[MAX_N], current, f[MAX_N], g[MAX_N];
bool tag[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

inline char nc()
{
    static char buf[1000000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++;
}

int read()
{
    int x = 0, f = 1;
    char ch = nc();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = nc();
    }
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + ch - '0', ch = nc();
    return x * f;
}

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int cnt;

void dfs(int u, int fa, int mid)
{
    f[u] = -INF, g[u] = INF;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dfs(edges[i].to, u, mid);
            f[u] = max(f[u], f[edges[i].to] + 1);
            g[u] = min(g[u], g[edges[i].to] + 1);
        }
    if (tag[u] && g[u] > mid)
        f[u] = max(f[u], 0);
    if (f[u] + g[u] <= mid)
        f[u] = -INF;
    if (f[u] == mid)
        f[u] = -INF, g[u] = 0, cnt++;
}

bool check(int mid)
{
    cnt = 0, dfs(1, 0, mid);
    if (f[1] >= 0)
        cnt++;
    return cnt <= m;
}

int main()
{
    memset(head, -1, sizeof(head));
    n = read(), m = read();
    for (int i = 1, val; i <= n; i++)
        val = read(), tag[i] = (val == 1);
    for (int i = 1, u, v; i <= n - 1; i++)
        u = read(), v = read(), addpath(u, v), addpath(v, u);
    int l = 0, r = n, res;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
            r = mid - 1, res = mid;
        else
            l = mid + 1;
    }
    printf("%d\n", res);
    return 0;
}