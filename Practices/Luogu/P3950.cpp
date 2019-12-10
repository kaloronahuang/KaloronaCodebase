// P3950.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 300100;

int ch[MAX_N][2], fa[MAX_N], n, m, xi[MAX_N], yi[MAX_N], cnt;
char opt[20];
bool tag[MAX_N];

// splay tree;

#define lson ch[p][0]
#define rson ch[p][1]

void pushdown(int p)
{
    if (tag[p])
    {
        tag[lson] ^= 1, tag[rson] ^= 1;
        swap(lson, rson);
        tag[p] = 0;
    }
}

int check(int p) { return ch[fa[p]][1] == p; }

bool isRoot(int p) { return ch[fa[p]][0] != p && ch[fa[p]][1] != p; }

void rotate(int x)
{
    int y = fa[x], z = fa[y], dir = check(x), w = ch[x][dir ^ 1];
    fa[x] = z;
    if (!isRoot(y))
        ch[z][ch[z][1] == y] = x;
    fa[y] = x, ch[x][dir ^ 1] = y;
    if (w)
        fa[w] = y;
    ch[y][dir] = w;
}

void update(int p)
{
    static int stk[MAX_N];
    int tail = 0;
    stk[++tail] = p;
    while (!isRoot(p))
        stk[++tail] = p = fa[p];
    while (tail)
        pushdown(stk[tail--]);
}

void splay(int p)
{
    update(p);
    for (int fat = fa[p]; fat = fa[p], !isRoot(p); rotate(p))
        if (!isRoot(fat))
            rotate(check(fat) == check(p) ? fat : p);
}

// LCT;

void access(int p)
{
    for (int pre = 0; p != 0; pre = p, p = fa[p])
        splay(p), rson = pre;
}

void makeRoot(int p) { access(p), splay(p), tag[p] ^= 1, pushdown(p); }

int find(int p)
{
    access(p), splay(p), pushdown(p);
    while (lson)
        pushdown(p = lson);
    return p;
}

void split(int x, int y)
{
    makeRoot(x), access(y), splay(y);
}

void link(int x, int y) { makeRoot(x), fa[x] = y; }

void cut(int x, int y) { split(x, y), fa[x] = ch[y][0] = 0; }

int main()
{
    
    freopen("testdata (7).in", "r", stdin);
    freopen("test.out", "w", stdout);
    
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), link(u, v);
    while (m--)
    {
        int x, y;
        scanf("%s%d", opt + 1, &x);
        if (opt[1] == 'Q')
        {
            scanf("%d", &y), makeRoot(x);
            puts(find(y) == x ? "Yes" : "No");
        }
        else if (opt[1] == 'C')
            scanf("%d", &y), cut(x, y), xi[++cnt] = x, yi[cnt] = y;
        else
            link(xi[x], yi[x]);
    }
    return 0;
}