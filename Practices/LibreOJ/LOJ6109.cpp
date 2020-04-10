// LOJ6109.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

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

typedef long long ll;

int n, ai[MAX_N], q, ptot, root;

struct node
{
    int lson, rson, tag, val, siz;
    ll sum;
} nodes[MAX_N * 350];

#define ls nodes[p].lson
#define rs nodes[p].rson

void pushup(int p)
{
    nodes[p].siz = nodes[ls].siz + nodes[rs].siz + 1;
    nodes[p].sum = nodes[ls].sum + nodes[rs].sum + nodes[p].val;
}

int rd() { return (1ll * rand() * rand() % INT_MAX + rand()) % INT_MAX; }

void pushdown(int p)
{
    if (nodes[p].tag)
    {
        if (ls)
            nodes[++ptot] = nodes[ls], ls = ptot, nodes[ls].tag += nodes[p].tag, nodes[ls].sum += 1LL * nodes[ls].siz * nodes[p].tag, nodes[ls].val += nodes[p].tag;
        if (rs)
            nodes[++ptot] = nodes[rs], rs = ptot, nodes[rs].tag += nodes[p].tag, nodes[rs].sum += 1LL * nodes[rs].siz * nodes[p].tag, nodes[rs].val += nodes[p].tag;
        nodes[p].tag = 0;
    }
}

void split(int p, int siz, int &x, int &y)
{
    if (p == 0)
        return (void)(x = y = 0);
    pushdown(p);
    if (nodes[ls].siz >= siz)
    {
        nodes[y = ++ptot] = nodes[p];
        split(ls, siz, x, nodes[y].lson);
        pushup(y);
    }
    else
    {
        nodes[x = ++ptot] = nodes[p];
        split(rs, siz - nodes[ls].siz - 1, nodes[x].rson, y);
        pushup(x);
    }
}

int merge(int x, int y)
{
    if (x == 0 || y == 0)
        return x + y;
    if (rd() % (nodes[x].siz + nodes[y].siz) < nodes[x].siz)
    {
        pushdown(x), nodes[x].rson = merge(nodes[x].rson, y), pushup(x);
        return x;
    }
    else
    {
        pushdown(y), nodes[y].lson = merge(x, nodes[y].lson), pushup(y);
        return y;
    }
}

int merge_new(int x, int y)
{
    if (x == 0 || y == 0)
        return x + y;
    if (rd() % (nodes[x].siz + nodes[y].siz) < nodes[x].siz)
    {
        pushdown(x), nodes[++ptot] = nodes[x], x = ptot;
        nodes[x].rson = merge(nodes[x].rson, y), pushup(x);
        return x;
    }
    else
    {
        pushdown(y), nodes[++ptot] = nodes[y], y = ptot;
        nodes[y].lson = merge(x, nodes[y].lson), pushup(y);
        return y;
    }
}

ll query(int l, int r)
{
    int x, y, z;
    split(root, r, x, z), split(x, l - 1, x, y);
    return nodes[y].sum;
}

void updateAdd(int l, int r, int d)
{
    int x, y, z;
    split(root, r, x, z), split(x, l - 1, x, y);
    nodes[y].tag += d, nodes[y].sum += nodes[y].siz * d, nodes[y].val += d;
    root = merge(merge(x, y), z);
}

void updateReplace(int l, int r, int len)
{
    int x, y, z, a, b, c;
    split(root, l + len, x, z), split(x, l - 1, x, y);
    split(root, r + len, a, c), split(a, r - 1, a, b);
    root = merge_new(merge_new(a, y), c);
}

int main()
{
    srand(time(NULL)), n = read(), q = read();
    for (int i = 1; i <= n; i++)
        ai[i] = read(), nodes[++ptot] = {0, 0, 0, ai[i], 1, ai[i]}, root = merge(root, ptot);
    while (q--)
    {
        int opt = read(), l = read(), r = read(), x;
        if (opt == 1)
            x = read(), updateAdd(l, r, x);
        else if (opt == 2)
            x = read(), updateReplace(l, r, x);
        else
            printf("%lld\n", query(l, r));
    }
    return 0;
}