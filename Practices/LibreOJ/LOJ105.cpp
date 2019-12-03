// LOJ105.cpp
// Be careful about the memory siz;
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, INF = 0x3f3f3f3f;

int ch[MAX_N][2], tag[MAX_N], siz[MAX_N], fa[MAX_N], root, seq[MAX_N], val[MAX_N], n, q, ptot;

#define lson ch[p][0]
#define rson ch[p][1]

int check(int p)
{
    return ch[fa[p]][1] == p;
}

void pushup(int p)
{
    siz[p] = siz[lson] + siz[rson] + 1;
}

void pushdown(int p)
{
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
    pushdown(y), pushdown(x);
    fa[w] = y, ch[y][dir] = w;
    fa[y] = x, ch[x][dir ^ 1] = y;
    fa[x] = z;
    if (z != 0)
        ch[z][ch[z][1] == y] = x;
    pushup(y), pushup(x);
}

void splay(int p, int goal = 0)
{
    for (int f = fa[p]; (f = fa[p]) != goal; rotate(p))
        if (fa[f] != goal)
            rotate(check(p) == check(f) ? f : p);
    if (goal == 0)
        root = p;
}

int find(int x)
{
    int p = root;
    while (true)
    {
        pushdown(p);
        if (lson && siz[lson] >= x)
            p = lson;
        else
        {
            x -= siz[lson] + 1;
            if (x <= 0)
                return p;
            p = rson;
        }
    }
}

void print(int p)
{
    pushdown(p);
    if (lson)
        print(lson);
    if (val[p] != INF && val[p] != -INF)
        printf("%d ", val[p]);
    if (rson)
        print(rson);
}

int build(int l, int r, int fat)
{
    if (l > r)
        return 0;
    int p = ++ptot, mid = (l + r) >> 1;
    fa[p] = fat, val[p] = seq[mid];
    lson = build(l, mid - 1, p), rson = build(mid + 1, r, p);
    pushup(p);
    return p;
}

int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        seq[i + 1] = i;
    seq[1] = -INF, seq[n + 2] = INF;
    root = build(1, n + 2, 0);
    while (q--)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        l = find(l), splay(l);
        r = find(r + 2), splay(r, l);
        tag[ch[ch[root][1]][0]] ^= 1;
    }
    print(root);
    return 0;
}