// P3690.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200;

int n, q, ch[MAX_N][2], fa[MAX_N], sum[MAX_N], val[MAX_N], siz[MAX_N];
bool tag[MAX_N];

#define lson (ch[p][0])
#define rson (ch[p][1])

// LCT;

int check(int p) { return ch[fa[p]][1] == p; }

bool isRoot(int p) { return ch[fa[p]][0] != p && ch[fa[p]][1] != p; }

void pushup(int p) { sum[p] = sum[lson] ^ sum[rson] ^ val[p], siz[p] = siz[lson] + siz[rson] + 1; }

void rotate(int x)
{
    int y = fa[x], z = fa[y], dir = check(x), w = ch[x][dir ^ 1];
    fa[x] = z;
    if (!isRoot(y))
        ch[z][check(y)] = x;
    fa[y] = x, ch[x][dir ^ 1] = y;
    fa[w] = y, ch[y][dir] = w;
    pushup(y), pushup(x), pushup(z);
}

void pushdown(int p)
{
    if (tag[p])
    {
        tag[lson] ^= 1, tag[rson] ^= 1;
        swap(lson, rson), tag[p] = 0;
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
    pushup(p);
}

void access(int p)
{
    for (int pre = 0; p; pre = p, p = fa[p])
        splay(p), rson = pre, pushup(p);
}

void makeRoot(int p) { access(p), splay(p), tag[p] ^= 1, pushdown(p); }

int find(int p)
{
    access(p), splay(p), pushdown(p);
    while (lson)
        pushdown(p = lson);
    splay(p);
    return p;
}

void link(int x, int y)
{
    makeRoot(x);
    if (find(x) != find(y))
        fa[x] = y;
}

void cut(int x, int y)
{
    makeRoot(x);
    if (find(y) != x || siz[x] > 2)
        return;
    fa[y] = ch[x][1] = 0, pushup(x);
}

void split(int x, int y) { makeRoot(x), access(y), splay(y); }

int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", &val[i]), sum[i] = val[i];
    while (q--)
    {
        int opt, x, y;
        scanf("%d%d%d", &opt, &x, &y);
        if (opt == 0)
        {
            split(x, y);
            printf("%d\n", sum[y] ^ sum[ch[y][1]]);
        }
        else if (opt == 1)
            link(x, y);
        else if (opt == 2)
            cut(x, y);
        else
            splay(x), val[x] = y, pushup(x);
    }
    return 0;
}