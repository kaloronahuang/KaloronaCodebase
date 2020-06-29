// BZ3173.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100100;

int n, ch[MAX_N][2], siz[MAX_N], val[MAX_N], prod[MAX_N], fa[MAX_N], groot, ptot;

#define lson (ch[p][0])
#define rson (ch[p][1])

// Splay;

void pushup(int p) { siz[p] = siz[lson] + siz[rson] + 1, prod[p] = max(val[p], max(prod[lson], prod[rson])); }

int check(int p) { return ch[fa[p]][1] == p; }

void rotate(int x)
{
    int y = fa[x], z = fa[y], dir = check(x), w = ch[x][dir ^ 1];
    fa[x] = z;
    if (z)
        ch[z][check(y)] = x;
    fa[y] = x, ch[x][dir ^ 1] = y;
    fa[w] = y, ch[y][dir] = w;
    pushup(y), pushup(x);
}

void splay(int p, int goal = 0)
{
    for (int fat = fa[p]; (fat = fa[p]) != goal; rotate(p))
        if (fa[fat] != goal)
            rotate(check(p) == check(fat) ? fat : p);
    if (goal == 0)
        groot = p;
}

int kth(int k)
{
    int p = groot;
    while (true)
    {
        if (siz[lson] + 1 > k)
            p = lson;
        else if (siz[lson] + 1 == k)
            return p;
        else
            k -= siz[lson] + 1, p = rson;
    }
}

int insert(int p, int pre, int pos, int delta)
{
    if (p == 0)
    {
        p = ++ptot, fa[p] = pre, val[p] = delta, pushup(p);
        return p;
    }
    int lsiz = siz[lson];
    if (pos <= lsiz + 1)
        lson = insert(lson, p, pos, delta);
    else
        rson = insert(rson, p, pos - lsiz - 1, delta);
    pushup(p);
    return p;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1, pos, cval; i <= n; i++)
    {
        scanf("%d", &pos);
        if (pos == 0)
            cval = 1;
        else if (pos == i - 1)
            cval = prod[groot] + 1;
        else
        {
            splay(kth(pos + 1));
            cval = prod[ch[groot][0]] + 1;
        }
        insert(groot, 0, pos + 1, cval), splay(ptot);
        printf("%d\n", prod[groot]);
    }
    return 0;
}