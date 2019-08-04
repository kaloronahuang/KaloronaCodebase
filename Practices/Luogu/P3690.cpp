// P3690.cpp
#include <bits/stdc++.h>
#define lson ch[p][0]
#define rson ch[p][1]

using namespace std;

const int MAX_N = 3e5 + 200;

int ch[MAX_N][2], val[MAX_N], size[MAX_N], fa[MAX_N], reverseTag[MAX_N];
int xorsum[MAX_N], n, m;

inline bool isRoot(int p) { return ch[fa[p]][0] != p && ch[fa[p]][1] != p; }

inline int check(int p) { return ch[fa[p]][1] == p; }

inline void clear(int p) { lson = rson = fa[p] = val[p] = size[p] = reverseTag[p] = xorsum[p] = 0; }

inline void pushUp(int p)
{
    clear(0);
    size[p] = 1 + size[lson] + size[rson];
    xorsum[p] = xorsum[lson] ^ xorsum[rson] ^ val[p];
}

inline void pushDown(int p)
{
    if (reverseTag[p])
    {
        if (lson)
            reverseTag[lson] ^= 1, swap(ch[lson][0], ch[lson][1]);
        if (rson)
            reverseTag[rson] ^= 1, swap(ch[rson][0], ch[rson][1]);
        reverseTag[p] = 0;
    }
}

inline void update(int x)
{
    if (!isRoot(x))
        update(fa[x]);
    pushDown(x);
}

inline void rotate(int x)
{
    int y = fa[x], z = fa[y], dir = check(x), w = ch[x][dir ^ 1];
    fa[x] = z;
    if (!isRoot(y))
        ch[z][check(y)] = x;
    ch[y][dir] = w, fa[w] = y;
    ch[x][dir ^ 1] = y, fa[y] = x;
    pushUp(y), pushUp(x), pushUp(z);
}

inline void splay(int x)
{
    update(x);
    for (int fat = fa[x]; fat = fa[x], !isRoot(x); rotate(x))
        if (!isRoot(fat))
            rotate(check(fat) == check(x) ? fat : x);
}

inline void access(int x)
{
    for (int fat = 0; x != 0; fat = x, x = fa[x])
        splay(x), ch[x][1] = fat, pushUp(x);
}

inline void makeRoot(int p)
{
    access(p), splay(p);
    swap(lson, rson), reverseTag[p] ^= 1;
}

inline int find(int p)
{
    access(p), splay(p);
    while (lson)
        p = lson;
    splay(p);
    return p;
}

inline void link(int x, int y)
{
    makeRoot(x);
    if (find(y) == x)
        return;
    fa[x] = y;
}

inline void split(int x, int y)
{
    makeRoot(x);
    access(y), splay(y);
}

inline void cut(int x, int y)
{
    makeRoot(x);
    if (find(y) != x || size[x] > 2)
        return;
    fa[y] = ch[x][1] = 0;
    pushUp(x);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &val[i]);
    while (m--)
    {
        int opt, x, y;
        scanf("%d%d%d", &opt, &x, &y);
        switch (opt)
        {
        case 0:
            split(x, y), printf("%d\n", xorsum[y]);
            break;
        case 1:
            link(x, y);
            break;
        case 2:
            cut(x, y);
            break;
        case 3:
            splay(x), val[x] = y, pushUp(x);
            break;
        }
    }
    return 0;
}

// P3690.cpp