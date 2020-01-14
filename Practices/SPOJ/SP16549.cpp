// SP16549.cpp
#include <bits/stdc++.h>
#pragma GCC optimize(2)

using namespace std;

const int MAX_N = 2e5 + 200;

int head[MAX_N], current, n, q, father[MAX_N], color[MAX_N];

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

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

struct LCT
{
    int ch[MAX_N][2], siz[MAX_N], vsiz[MAX_N], fa[MAX_N];

#define lson (ch[p][0])
#define rson (ch[p][1])

    // LCT;

    int check(int p) { return ch[fa[p]][1] == p; }

    bool isRoot(int p) { return ch[fa[p]][0] != p && ch[fa[p]][1] != p; }

    void pushup(int p) { siz[p] = siz[lson] + siz[rson] + 1 + vsiz[p]; }

    void rotate(int x)
    {
        int y = fa[x], z = fa[y], dir = check(x), w = ch[x][dir ^ 1];
        fa[x] = z;
        if (!isRoot(y))
            ch[z][check(y)] = x;
        fa[y] = x, ch[x][dir ^ 1] = y;
        fa[w] = y, ch[y][dir] = y;
        pushup(y), pushup(x);
    }

    void splay(int p)
    {
        for (int fat = fa[p]; fat = fa[p], !isRoot(p); rotate(p))
            if (!isRoot(fat))
                rotate(check(fat) == check(p) ? fat : p);
        pushup(p);
    }

    void access(int p)
    {
        for (int pre = 0; p != 0; pre = p, p = fa[p])
        {
            splay(p);
            if (rson)
                vsiz[p] += siz[rson];
            rson = pre;
            if (rson)
                vsiz[p] -= siz[rson];
            pushup(p);
        }
    }

    int find(int p)
    {
        access(p), splay(p);
        while (lson)
            p = lson;
        return p;
    }

    void link(int x, int y)
    {
        if (y == 0)
            return;
        access(x), splay(x), splay(y), fa[x] = y, vsiz[y] += siz[x], pushup(y);
    }

    void cut(int p, int y)
    {
        if (y == 0)
            return;
        access(p), splay(p);
        lson = fa[lson] = 0, pushup(p);
    }

#undef rson
#undef lson

} Tr[2];

void dfs(int u)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != father[u])
            father[edges[i].to] = u, dfs(edges[i].to), Tr[0].link(edges[i].to, u);
}

int main()
{
    memset(head, -1, sizeof(head));
    n = read();
    for (int i = 1, u, v; i <= n - 1; i++)
        u = read(), v = read(), addpath(u, v), addpath(v, u);
    dfs(1), q = read();
    while (q--)
    {
        int opt = read(), x = read();
        if (opt == 1)
            Tr[color[x]].cut(x, father[x]), color[x] ^= 1, Tr[color[x]].link(x, father[x]);
        else
            Tr[color[x]].splay(x), printf("%d\n", Tr[color[x]].siz[x]);
    }
    return 0;
}