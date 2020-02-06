// SP8791.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, q;

namespace LCT
{

int ch[MAX_N][2], fa[MAX_N];
bool revTag[MAX_N];

#define lson (ch[p][0])
#define rson (ch[p][1])

// splay func;

void pushdown(int p)
{
    if (revTag[p])
    {
        swap(lson, rson);
        revTag[lson] ^= 1, revTag[rson] ^= 1;
        revTag[p] = 0;
    }
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
    for (int fat = fa[p]; fat = fa[p], !isRoot(p); rotate(p))
        if (!isRoot(fat))
            rotate(check(p) == check(fat) ? fat : p);
}

int access(int p)
{
    int pre = 0;
    for (; p; pre = p, p = fa[p])
        splay(p), rson = pre;
    return pre;
}

void makeRoot(int p) { access(p), splay(p), revTag[p] ^= 1, pushdown(p); }

void link(int x, int y) { makeRoot(x), fa[x] = y; }

void cut(int p) { access(p), splay(p), lson = fa[lson] = 0; }

} // namespace LCT

char cmdlet[10];

int main()
{
    scanf("%d%d", &n, &q);
    while (q--)
    {
        int a, b;
        scanf("%s%d", cmdlet + 1, &a);
        if (cmdlet[2] == 'i')
            // link;
            scanf("%d", &b), LCT::link(a, b);
        else if (cmdlet[2] == 'u')
            LCT::cut(a);
        else
            scanf("%d", &b), LCT::access(a), printf("%d\n", LCT::access(b));
    }
    return 0;
}