// P1501.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200, mod = 51061;

int n, q, ch[MAX_N][2], val[MAX_N], siz[MAX_N], fa[MAX_N], tag[MAX_N], sum[MAX_N], lazy_add[MAX_N], lazy_mul[MAX_N];

bool isRoot(int p) { return ch[fa[p]][0] != p && ch[fa[p]][1] != p; }

int check(int p) { return ch[fa[p]][1] == p; }

#define lson ch[p][0]
#define rson ch[p][1]

void updateAdd(int p, int x)
{
    sum[p] = (1LL * siz[p] * x % mod + 1LL * sum[p]) % mod;
    lazy_add[p] = (1LL * lazy_add[p] + x) % mod, val[p] = (1LL * val[p] + x) % mod;
}

void updateMultiply(int p, int x)
{
    sum[p] = 1LL * sum[p] * x % mod, val[p] = 1LL * val[p] * x % mod;
    lazy_mul[p] = 1LL * lazy_mul[p] * x % mod, lazy_add[p] = 1LL * lazy_add[p] * x % mod;
}

void pushup(int p)
{
    siz[p] = siz[lson] + siz[rson] + 1;
    sum[p] = (1LL * sum[lson] + 1LL * sum[rson] + 1LL * val[p]) % mod;
}

void pushdown(int p)
{
    if (lazy_mul[p] != 1)
    {
        updateMultiply(lson, lazy_mul[p]), updateMultiply(rson, lazy_mul[p]);
        lazy_mul[p] = 1;
    }
    if (lazy_add != 0)
    {
        updateAdd(lson, lazy_add[p]), updateAdd(rson, lazy_add[p]);
        lazy_add[p] = 0;
    }
    if (tag[p])
    {
        tag[lson] ^= 1, tag[rson] ^= 1;
        swap(lson, rson);
        tag[p] = 0;
    }
}

void rotate(int x)
{
    int y = fa[x], z = fa[y], dir = check(x), w = ch[x][dir ^ 1];
    fa[x] = z;
    if (!isRoot(y))
        ch[z][check(y)] = x;
    ch[y][dir] = w, fa[w] = y;
    ch[x][dir ^ 1] = y, fa[y] = x;
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
    for (int f = fa[p]; (f = fa[p]), !isRoot(p); rotate(p))
        if (!isRoot(f))
            rotate(check(p) == check(f) ? f : p);
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

void link(int x, int y)
{
    makeRoot(x);
    if (find(y) == x)
        return;
    fa[x] = y;
}

void split(int x, int y)
{
    makeRoot(x);
    access(y), splay(y);
}

void cut(int x, int y)
{
    makeRoot(x);
    if (find(y) != x || siz[x] > 2)
        return;
    fa[y] = ch[x][1] = 0;
    pushup(x);
}

int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        val[i] = lazy_mul[i] = 1;
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), link(u, v);
    while (q--)
    {
        char opt[5];
        int u, v, a, b;
        scanf("%s", opt + 1);
        if (opt[1] == '+')
            scanf("%d%d%d", &u, &v, &a), split(u, v), updateAdd(v, a % mod);
        else if (opt[1] == '-')
            scanf("%d%d%d%d", &u, &v, &a, &b), cut(u, v), link(a, b);
        else if (opt[1] == '*')
            scanf("%d%d%d", &u, &v, &a), split(u, v), updateMultiply(v, a % mod);
        else if (opt[1] == '/')
            scanf("%d%d", &u, &v), split(u, v), printf("%d\n", sum[v] % mod);
    }
    return 0;
}