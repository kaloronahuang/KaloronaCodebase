// P2147.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 10100;

int ch[MAX_N][2], fa[MAX_N], siz[MAX_N], n, q;
char cmd[20];
bool tag[MAX_N];

#define lson ch[p][0]
#define rson ch[p][1]

int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch))
    {
        if (ch != '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x * f;
}

int check(int p) { return ch[fa[p]][1] == p; }

bool isRoot(int p) { return ch[fa[p]][0] != p && ch[fa[p]][1] != p; }

void pushup(int p) { return (void)(siz[p] = siz[lson] + siz[rson]); }

void pushdown(int p)
{
    if (tag[p])
    {
        swap(lson, rson);
        tag[lson] ^= 1, tag[rson] ^= 1;
        tag[p] = false;
    }
}

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
}

void access(int p)
{
    for (int fat = 0; p; fat = p, p = fa[p])
        splay(p), ch[p][1] = fat, pushup(p);
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

void cut(int x, int y)
{
    makeRoot(x);
    if (find(y) != x || siz[x] > 2)
        return;
    fa[y] = ch[x][1] = 0;
    pushup(x);
}

void link(int x, int y)
{
    makeRoot(x);
    if (find(y) == x)
        return;
    fa[x] = y;
}

int main()
{
    scanf("%d%d", &n, &q);
    while (q--)
    {
        int u, v;
        scanf("%s", cmd + 1);
        if (cmd[1] == 'C')
            scanf("%d%d", &u, &v), link(u, v);
        else if (cmd[1] == 'D')
            scanf("%d%d", &u, &v), cut(u, v);
        else
            scanf("%d%d", &u, &v), makeRoot(u), puts(find(v) == u ? "Yes" : "No");
    }
    return 0;
}