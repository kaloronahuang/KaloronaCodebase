// LOJ6038.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200;

int typ, n, q, ch[MAX_N][2], fa[MAX_N], siz[MAX_N], mem[MAX_N], pts[MAX_N][2], lastans;
bool tag[MAX_N];

#define lson (ch[p][0])
#define rson (ch[p][1])

// LCT;

int check(int p) { return ch[fa[p]][1] == p; }

bool isRoot(int p) { return ch[fa[p]][0] != p && ch[fa[p]][1] != p; }

void pushup(int p) { siz[p] = siz[lson] + siz[rson] + 1; }

void rotate(int x)
{
    int y = fa[x], z = fa[y], dir = check(x), w = ch[x][dir ^ 1];
    fa[x] = z;
    if (!isRoot(y))
        ch[z][check(y)] = x;
    fa[w] = y, ch[y][dir] = w;
    fa[y] = x, ch[x][dir ^ 1] = y;
    pushup(y), pushup(x);
}

void pushdown(int p)
{
    if (tag[p])
    {
        tag[lson] ^= 1, tag[rson] ^= 1;
        swap(lson, rson);
        tag[p] = false;
    }
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
    for (int fat = fa[p]; fat = fa[p], !isRoot(p); rotate(p))
        if (!isRoot(fat))
            rotate(check(p) == check(fat) ? fat : p);
}

void access(int p)
{
    for (int pre = 0; p; pre = p, p = fa[p])
        splay(p), rson = pre, pushup(p);
}

void makeRoot(int p) { access(p), splay(p), tag[p] ^= 1, pushdown(p); }

void split(int x, int y) { makeRoot(x), access(y), splay(y); }

int find(int x) { return mem[x] == x ? x : mem[x] = find(mem[x]); }

int getDist(int x, int y) { return split(x, y), siz[y] - 1; }

void link(int x, int y)
{
    makeRoot(x), fa[x] = y;
    x = find(x), y = find(y);
    int pt[2] = {pts[x][0], pts[x][1]};
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            if (pt[0] == 0 || getDist(pts[x][i], pts[y][j]) > getDist(pt[0], pt[1]))
                pt[0] = pts[x][i], pt[1] = pts[y][j];
    if (getDist(pts[y][0], pts[y][1]) > getDist(pt[0], pt[1]))
        pt[0] = pts[y][0], pt[1] = pts[y][1];
    mem[x] = y, pts[y][0] = pt[0], pts[y][1] = pt[1];
}

int main()
{
    scanf("%d%d%d", &typ, &n, &q);
    for (int i = 1; i <= n; i++)
        mem[i] = i, pts[i][0] = pts[i][1] = i;
    while (q--)
    {
        int opt, u, v;
        scanf("%d%d", &opt, &u), u ^= lastans * typ;
        if (opt == 1)
            scanf("%d", &v), v ^= lastans * typ, link(u, v);
        else
            printf("%d\n", lastans = max(getDist(u, pts[find(u)][0]), getDist(u, pts[find(u)][1])));
    }
    return 0;
}