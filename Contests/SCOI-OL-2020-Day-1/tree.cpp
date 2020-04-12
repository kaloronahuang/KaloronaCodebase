// tree.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

typedef long long ll;

const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, q, ch[MAX_N][2], fa[MAX_N];
ll lmx[MAX_N], rmx[MAX_N], val[MAX_N], siz[MAX_N];
multiset<ll> vmax[MAX_N];
bool tag[MAX_N];

inline char nc()
{
    static char buf[100000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
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

#define lson (ch[p][0])
#define rson (ch[p][1])

// LCT;

void pushup(int p)
{
    siz[p] = siz[lson] + siz[rson] + val[p];
    lmx[p] = max(lmx[lson], siz[lson] + val[p] + max(lmx[rson], max(0LL, vmax[p].empty() ? 0 : *vmax[p].rbegin())));
    rmx[p] = max(rmx[rson], siz[rson] + val[p] + max(rmx[lson], max(0LL, vmax[p].empty() ? 0 : *vmax[p].rbegin())));
}

int check(int p) { return ch[fa[p]][1] == p; }

bool isRoot(int p) { return ch[fa[p]][0] != p && ch[fa[p]][1] != p; }

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

/*

void pushdown(int p)
{
    if (tag[p])
    {
        tag[lson] ^= 1, tag[rson] ^= 1;
        swap(lson, rson), tag[p] = true;
        swap(vmax[lson], vmax[rson]);
    }
}

void update(int p)
{
    if (!isRoot(p))
        update(fa[p]);
    pushdown(p);
}

*/

void splay(int p)
{
    // update(p);
    for (int fat = fa[p]; fat = fa[p], !isRoot(p); rotate(p))
        if (!isRoot(fat))
            rotate(check(fat) == check(p) ? fat : p);
}

void access(int p)
{
    for (int pre = 0; p; pre = p, p = fa[p])
    {
        splay(p);
        if (rson)
            vmax[p].insert(lmx[rson]);
        if (pre)
            vmax[p].erase(vmax[p].find(lmx[pre]));
        rson = pre, pushup(p);
    }
}

int main()
{
    n = read(), q = read();
    for (int i = 2; i <= n; i++)
        fa[i] = read();
    for (int i = 1; i <= n; i++)
        val[i] = read();
    lmx[0] = rmx[0] = -INF;
    for (int i = n; i >= 1; i--)
    {
        pushup(i);
        if (fa[i] != 0)
            vmax[fa[i]].insert(lmx[i]);
    }
    while (q--)
    {
        int opt = read(), u = read(), x = opt == 1 ? 0 : read();
        if (opt == 1)
            access(u), splay(u), printf("%lld\n", rmx[u]);
        else
            access(u), splay(u), val[u] = x, pushup(u);
    }
    return 0;
}