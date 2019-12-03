// P4219.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, q, ch[MAX_N][2], siz[MAX_N], fa[MAX_N], tag[MAX_N], sum[MAX_N];
char opt[10];

#define lson ch[p][0]
#define rson ch[p][1]

void pushup(int p)
{
    sum[p] = sum[lson] + sum[rson] + siz[p] + 1;
}

int check(int p) { return p == ch[fa[p]][1]; }

bool isRoot(int p) { return ch[fa[p]][0] != p && ch[fa[p]][1] != p; }

void pushdown(int p)
{
    if (tag[p])
    {
        swap(lson, rson);
        tag[lson] ^= 1, tag[rson] ^= 1;
        tag[p] = 0;
    }
}

void rotate(int x)
{
    int y = fa[x], z = fa[y], dir = check(x), w = ch[x][dir ^ 1];
    fa[x] = z;
    if (!isRoot(y))
        ch[z][ch[z][1] == y] = x;
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
    for (int f = fa[p]; f = fa[p], !isRoot(p); rotate(p))
        if (!isRoot(f))
            rotate(check(f) == check(p) ? f : p);
}

void access(int p)
{
    for (int fat = 0; p != 0; fat = p, p = fa[p])
        splay(p), siz[p] += sum[rson], siz[p] -= sum[rson = fat], pushup(p);
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

void split(int x, int y)
{
    makeRoot(x);
    access(y), splay(y);
}

void link(int x, int y)
{
    split(x, y);
    fa[x] = y, siz[y] += sum[x], pushup(y);
}

int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        sum[i] = 1;
    while (q--)
    {
        char opt[10];
        int x, y;
        scanf("%s%d%d", opt + 1, &x, &y);
        if (opt[1] == 'A')
            link(x, y);
        else
        {
            split(x, y);
            printf("%lld\n", 1LL * (siz[x] + 1) * (siz[y] + 1));
        }
    }
    return 0;
}