// LOJ10135.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

inline char GET_CHAR()
{
    static char buf[MAX_N], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, MAX_N, stdin), p1 == p2) ? EOF : *p1++;
}
template <class T>
void read(T &x)
{
    x = 0;
    int f = 0;
    char ch = GET_CHAR();
    while (ch < '0' || ch > '9')
    {
        f |= (ch == '-');
        ch = GET_CHAR();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = GET_CHAR();
    }
    x = f ? -x : x;
    return;
}

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

int n, m, head[MAX_N], current, root, dfn[MAX_N], low[MAX_N], ptot;

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u, int fa)
{
    dfn[u] = low[u] = ++ptot;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u);
    low[u] = ptot;
}

int main()
{
    memset(head, -1, sizeof(head));
    read(n);
    for (int i = 1, a, b; i <= n; i++)
    {
        read(a), read(b);
        if (b == -1)
            root = a;
        else
            addpath(a, b), addpath(b, a);
    }
    dfs(root, 0);
    read(m);
    while (m--)
    {
        int a, b;
        read(a), read(b);
        bool flag = false;
        if (dfn[a] < dfn[b] && dfn[b] <= low[a])
            puts("1");
        else if (dfn[b] < dfn[a] && dfn[a] <= low[b])
            puts("2");
        else
            puts("0");
    }
    return 0;
}