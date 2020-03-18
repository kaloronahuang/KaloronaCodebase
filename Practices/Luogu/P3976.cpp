// P3976.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e4 + 200, INF = 0x3f3f3f3f;

int n, m;

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

namespace LCT
{

int ch[MAX_N][2], fa[MAX_N], pi[MAX_N], siz[MAX_N], lmax[MAX_N], rmax[MAX_N], gmax[MAX_N], gmin[MAX_N], val[MAX_N];
int tag[MAX_N];
bool revTag[MAX_N];

#define lson (ch[p][0])
#define rson (ch[p][1])

void pushup(int p)
{
    gmax[p] = max(val[p], max(gmax[lson], gmax[rson]));
    gmin[p] = min(val[p], min(gmin[lson], gmin[rson]));
    lmax[p] = max(max(lmax[lson], lmax[rson]), max(gmax[lson], val[p]) - min(gmin[rson], val[p]));
    rmax[p] = max(max(rmax[lson], rmax[rson]), max(gmax[rson], val[p]) - min(gmin[lson], val[p]));
}

void modify(int p, int v) { gmax[p] += v, gmin[p] += v, val[p] += v, tag[p] += v; }

void reverse(int p) { swap(lmax[p], rmax[p]), swap(lson, rson), revTag[p] ^= 1; }

void pushdown(int p)
{
    if (tag[p])
    {
        if (lson)
            modify(lson, tag[p]);
        if (rson)
            modify(rson, tag[p]);
        tag[p] = 0;
    }
    if (revTag[p])
    {
        if (lson)
            reverse(lson);
        if (rson)
            reverse(rson);
        revTag[p] ^= 1;
    }
}

bool isRoot(int p) { return ch[fa[p]][0] != p && ch[fa[p]][1] != p; }

int check(int p) { return ch[fa[p]][1] == p; }

void rotate(int x)
{
    int y = fa[x], z = fa[y], dir = check(x), w = ch[x][dir ^ 1];
    fa[x] = z;
    if (!isRoot(y))
        ch[z][check(y)] = x;
    fa[y] = x, ch[x][dir ^ 1] = y;
    fa[w] = y, ch[y][dir] = w;
    pushup(y), pushup(x);
}

void update(int p)
{
    if (fa[p])
        update(fa[p]);
    pushdown(p);
}

void splay(int p)
{
    update(p);
    for (int fat = fa[p]; fat = fa[p], !isRoot(p); rotate(p))
        if (!isRoot(fat))
            rotate(check(fat) == check(p) ? fat : p);
    pushup(p);
}

void access(int p)
{
    for (int pre = 0; p; pre = p, p = fa[p])
        splay(p), rson = pre, pushup(p);
}

void makeRoot(int p) { access(p), splay(p), reverse(p); }

void split(int x, int y) { makeRoot(y), access(x), splay(x); }

void link(int x, int y) { split(x, y), fa[y] = x; }

} // namespace LCT

int main()
{
    LCT::gmin[0] = INF, LCT::gmax[0] = -INF, n = read();
    for (int i = 1; i <= n; i++)
        LCT::gmax[i] = LCT::gmin[i] = LCT::val[i] = read();
    for (int i = 1; i < n; i++)
        LCT::link(read(), read());
    m = read();
    while (m--)
    {
        int x = read(), y = read(), w = read();
        LCT::split(x, y), printf("%d\n", LCT::lmax[x]), LCT::modify(x, w);
    }
    return 0;
}