// P4847.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 2e5 + 2000;

int ch[MAX_N][2], siz[MAX_N], fa[MAX_N], val[MAX_N], n, q;
ll sum[MAX_N];
char opt[20];

#define lson ch[p][0]
#define rson ch[p][1]

// splay functions;

int check(int p) { return ch[fa[p]][1] == p; }

bool isRoot(int p) { return ch[fa[p]][0] != p && ch[fa[p]][1] != p; }

void pushup(int p) { return (void)(siz[p] = siz[lson] + siz[rson] + 1, sum[p] = sum[lson] + sum[rson] + val[p]); }

void rotate(int x)
{
    int y = fa[x], z = fa[y], dir = check(x), w = ch[x][dir ^ 1];
    fa[x] = z;
    if (!isRoot(y))
        ch[z][ch[z][1] == y] = x;
    fa[y] = x, ch[x][dir ^ 1] = y;
    ch[y][dir] = w;
    if (w)
        fa[w] = y;
    pushup(y), pushup(x);
}

void splay(int p)
{
    for (int fat = fa[p]; fat = fa[p], !isRoot(p); rotate(p))
        if (!isRoot(fat))
            rotate(check(p) == check(fat) ? fat : p);
    pushup(p);
}

// LCT;

void access(int p)
{
    for (int pre = 0; p != 0; pre = p, p = fa[p])
        splay(p), rson = pre;
}

void link(int x, int y)
{
    int p1 = x, p2 = y;
    splay(x);
    while (ch[x][0])
        x = ch[x][0];
    splay(y);
    while (ch[y][0])
        y = ch[y][0];
    if (x == y)
        return;
    while (ch[p2][1])
        p2 = ch[p2][1];
    splay(x), fa[x] = p2;
    while (ch[p1][1])
        p1 = ch[p1][1];
    access(p1);
}

void cut(int x) { splay(x), ch[x][0] = fa[ch[x][0]] = 0, pushup(x); }

ll split(int x, int y)
{
    int tx = x, ty = y;
    splay(x);
    ll siz_x = siz[ch[x][0]], sum_x = sum[ch[x][0]], w_x = val[x];
    while (ch[tx][0])
        tx = ch[tx][0];
    splay(y);
    ll siz_y = siz[ch[y][0]], sum_y = sum[ch[y][0]], w_y = val[y];
    while (ch[ty][0])
        ty = ch[ty][0];
    if (tx != ty)
        return -1;
    return siz_x < siz_y ? sum_y - sum_x + w_y : sum_x - sum_y + w_x;
}

#undef rson
#undef lson

int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", &val[i]);
    while (q--)
    {
        int x, y;
        scanf("%s%d", opt + 1, &x);
        if (opt[1] == 'M')
            scanf("%d", &y), link(x, y);
        else if (opt[1] == 'D')
            cut(x);
        else
            scanf("%d", &y), printf("%lld\n", split(x, y));
    }
    return 0;
}