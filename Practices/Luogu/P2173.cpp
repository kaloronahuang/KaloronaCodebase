// P2173.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, INF = 0x3f3f3f3f;

int ch[MAX_N][2], fa[MAX_N], siz[MAX_N], val[MAX_N], mx[MAX_N], n, m, c, q, deg[MAX_N];
bool tag[MAX_N];

struct edge
{
    int from, to;
    bool operator<(const edge &rhs) const { return from < rhs.from || (from == rhs.from && to < rhs.to); }
};
map<edge, int> mp;

#define lson ch[p][0]
#define rson ch[p][1]

void pushdown(int p)
{
    if (tag[p])
    {
        swap(lson, rson);
        tag[lson] ^= 1, tag[rson] ^= 1;
        tag[p] = false;
    }
}

void pushup(int p)
{
    siz[p] = siz[lson] + siz[rson] + 1;
    mx[p] = max(max(mx[lson], mx[rson]), val[p]);
}

int check(int p) { return ch[fa[p]][1] == p; }

bool isRoot(int p) { return ch[fa[p]][0] != p && ch[fa[p]][1] != p; }

void rotate(int x)
{
    int y = fa[x], z = fa[y], dir = check(x), w = ch[x][dir ^ 1];
    fa[x] = z;
    if (!isRoot(y))
        ch[z][ch[z][1] == y] = x;
    fa[y] = x, ch[x][dir ^ 1] = y;
    fa[w] = y, ch[y][dir] = w;
    pushup(y), pushup(x);
}

void update(int p)
{
    if (!isRoot(p))
        update(fa[p]);
    pushdown(p);
}

void splay(int p)
{
    update(p);
    for (int fat = fa[p]; (fat = fa[p]), !isRoot(p); rotate(p))
        if (!isRoot(fat))
            rotate(check(fat) == check(p) ? fat : p);
}

void access(int p)
{
    for (int fat = 0; p != 0; fat = p, p = fa[p])
        splay(p), rson = fat, pushup(p);
}

void makeRoot(int p)
{
    access(p), splay(p);
    tag[p] ^= 1, pushdown(p);
}

int find(int p)
{
    access(p), splay(p), pushdown(p);
    while (lson)
        pushdown(p = lson);
    splay(p);
    return p;
}

bool link(int x, int y)
{
    makeRoot(x);
    if (find(y) == x)
        return false;
    fa[x] = y, deg[x]++, deg[y]++;
    return true;
}

bool cut(int x, int y)
{
    makeRoot(x);
    if (find(y) != x || siz[x] > 2)
        return false;
    fa[y] = ch[x][1] = 0;
    deg[x]--, deg[y]--;
    pushup(x);
    return true;
}

void split(int x, int y) { makeRoot(x), access(y), splay(y); }

#undef rson
#undef lson

int main()
{
    mx[0] = -INF;
    scanf("%d%d%d%d", &n, &m, &c, &q);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &val[i]);
        for (int j = 1; j < c; j++)
            val[i + j * n] = val[i];
    }
    for (int i = 1, u, v, w; i <= m; i++)
    {
        scanf("%d%d%d", &u, &v, &w);
        if (u > v)
            swap(u, v);
        mp[edge{u, v}] = w, link(u + w * n, v + w * n);
    }
    while (q--)
    {
        int opt, x, y, w;
        scanf("%d%d%d", &opt, &x, &y);
        if (opt == 0)
            for (int i = 0; i < c; i++)
                val[x + i * n] = y, splay(x + i * n);
        else if (opt == 1)
        {
            scanf("%d", &w);
            if (x > y)
                swap(x, y);
            if (mp.count(edge{x, y}) == 0)
                puts("No such edge.");
            else if (mp[edge{x, y}] == w)
                puts("Success.");
            else if (deg[x + w * n] >= 2 || deg[y + w * n] >= 2)
                puts("Error 1.");
            else if (find(x + w * n) == find(y + w * n))
                puts("Error 2.");
            else
                puts("Success."), cut(x + mp[edge{x, y}] * n, y + mp[edge{x, y}] * n), link(x + w * n, y + w * n), mp[edge{x, y}] = w;
        }
        else
        {
            scanf("%d", &w), swap(w, x);
            if (x > y)
                swap(x, y);
            if (find(x + w * n) != find(y + w * n))
                puts("-1");
            else
                split(x + w * n, y + w * n), printf("%d\n", mx[y + w * n]);
        }
    }
    return 0;
}