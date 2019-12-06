// P4402.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, INF = 0x3f3f3f3f;

struct point
{
    int val, order, id;
    bool operator<(const point &rhs) const { return val < rhs.val || (val == rhs.val && order < rhs.order); }
} pts[MAX_N];

int n, ch[MAX_N][2], fa[MAX_N], siz[MAX_N], perm[MAX_N], root, ptot;
bool tag[MAX_N];

#define lson ch[p][0]
#define rson ch[p][1]

void pushdown(int p)
{
    if (tag[p])
    {
        swap(lson, rson);
        tag[lson] ^= 1, tag[rson] ^= 1;
        tag[p] = 0;
    }
}

void pushup(int p) { siz[p] = siz[lson] + siz[rson] + 1; }

int check(int p) { return ch[fa[p]][1] == p; }

void rotate(int x)
{
    int y = fa[x], z = fa[y], dir = check(x), w = ch[x][dir ^ 1];
    pushdown(y), pushdown(x);
    fa[x] = z;
    if (z != 0)
        ch[z][ch[z][1] == y] = x;
    fa[y] = x, ch[x][dir ^ 1] = y;
    fa[w] = y, ch[y][dir] = w;
    pushup(y), pushup(x);
}

void splay(int p, int goal = 0)
{
    for (int fat = fa[p]; (fat = fa[p]) != goal; rotate(p))
    {
        pushdown(fa[fat]), pushdown(fat), pushdown(p);
        if (fa[fat] != goal)
            rotate(check(p) == check(fat) ? fat : p);
    }
    if (goal == 0)
        root = p;
}

void reverse(int p)
{
    tag[p] ^= 1, pushdown(p);
}

int build(int l, int r, int fat)
{
    if (l > r)
        return 0;
    int mid = (l + r) >> 1, p = ++ptot;
    fa[p] = fat, pts[mid].id = p;
    lson = build(l, mid - 1, p), rson = build(mid + 1, r, p);
    pushup(p);
    return p;
}

int atRank(int k)
{
    int p = root;
    while (true)
    {
        pushdown(p);
        if (k <= siz[lson])
            p = lson;
        else
        {
            k -= siz[lson] + 1;
            if (k <= 0)
                return p;
            p = rson;
        }
    }
}

int getRank(int p)
{
    splay(p);
    return siz[lson];
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &pts[i + 1].val), pts[i + 1].order = i + 1;
    pts[1].val = -INF, pts[n + 2].val = INF;
    pts[1].order = 1, pts[n + 2].order = n + 2;
    root = build(1, n + 2, 0);
    sort(pts + 2, pts + 2 + n);
    for (int i = 2; i <= n + 1; i++)
    {
        int pos;
        printf("%d ", pos = getRank(pts[i].id));
        int l = atRank(i - 1), r = atRank(pos + 2);
        splay(l), splay(r, l);
        reverse(ch[ch[l][1]][0]);
    }
    return 0;
}