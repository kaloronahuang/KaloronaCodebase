// SP16580.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int head[MAX_N], current, n, q, val[MAX_N], color[MAX_N], father[MAX_N];

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
    int ch[MAX_N][2], fa[MAX_N], max_val[MAX_N];
    multiset<int> virtualSub[MAX_N];

    int check(int p) { return ch[fa[p]][1] == p; }

    bool isRoot(int p) { return ch[fa[p]][0] != p && ch[fa[p]][1] != p; }

#define lson (ch[p][0])
#define rson (ch[p][1])

    // splay part;

    void pushup(int p)
    {
        max_val[p] = max(max(max_val[lson], max_val[rson]), val[p]);
        if (!virtualSub[p].empty())
            max_val[p] = max(max_val[p], *virtualSub[p].rbegin());
    }

    void rotate(int x)
    {
        int y = fa[x], z = fa[y], dir = check(x), w = ch[x][dir ^ 1];
        fa[x] = z;
        if (!isRoot(y))
            ch[z][check(y)] = x;
        fa[y] = x, ch[x][dir ^ 1] = y;
        fa[w] = y, ch[y][dir] = w;
        pushup(y);
    }

    void splay(int p)
    {
        for (int fat = fa[p]; fat = fa[p], !isRoot(p); rotate(p))
            if (!isRoot(fat))
                rotate(check(p) == check(fat) ? fat : p);
        pushup(p);
    }

    void access(int p)
    {
        for (int pre = 0; p != 0; pre = p, p = fa[p])
        {
            splay(p);
            if (rson)
                virtualSub[p].insert(max_val[rson]);
            rson = pre;
            if (rson)
                virtualSub[p].erase(max_val[rson]);
            pushup(p);
        }
    }

    int find(int p)
    {
        access(p), splay(p);
        while (lson)
            p = lson;
        splay(p);
        return p;
    }

    void link(int x, int y)
    {
        if (y == 0)
            return;
        access(y), splay(y), splay(x), fa[x] = y;
        virtualSub[y].insert(max_val[x]), pushup(y);
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
} tr[2];

void dfs(int u, int fa)
{
    father[u] = fa;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            tr[color[edges[i].to]].link(edges[i].to, u), dfs(edges[i].to, u);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    for (int i = 1; i <= n; i++)
        scanf("%d", &color[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &val[i]);
    tr[0].max_val[0] = tr[1].max_val[0] = -2147483647;
    dfs(1, 0);
    scanf("%d", &q);
    while (q--)
    {
        int opt, x;
        scanf("%d%d", &opt, &x);
        if (opt == 0)
        {
            tr[color[x]].access(x);
            int rt = tr[color[x]].find(x);
            if (color[rt] == color[x])
                printf("%d\n", tr[color[x]].max_val[rt]);
            else
                printf("%d\n", tr[color[x]].max_val[tr[color[x]].ch[tr[color[x]].find(x)][1]]);
        }
        else if (opt == 1)
            tr[color[x]].cut(x, father[x]), color[x] ^= 1, tr[color[x]].link(x, father[x]);
        else
            tr[color[x]].access(x), tr[color[x]].splay(x), scanf("%d", &val[x]), tr[color[x]].pushup(x);
    }
    return 0;
}