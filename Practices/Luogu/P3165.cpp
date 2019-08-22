// P3165.cpp
#include <bits/stdc++.h>
#define lson ch[p][0]
#define rson ch[p][1]

using namespace std;

const int MAX_N = 1e5 + 200;

struct unit
{
    int val, id;
    bool operator<(const unit &u) const { return val < u.val || (val == u.val && id < u.id); }
} units[MAX_N];

int fa[MAX_N], siz[MAX_N], tag[MAX_N], ch[MAX_N][2];
int n, root, ptot;

void pushup(int p) { siz[p] = siz[lson] + siz[rson] + 1; }

void pushdown(int p)
{
    if (tag[p])
    {
        if (lson)
            swap(ch[lson][0], ch[lson][1]), tag[lson] ^= 1;
        if (rson)
            swap(ch[rson][0], ch[rson][1]), tag[rson] ^= 1;
        tag[p] ^= 1;
    }
}

int check(int p) { return ch[fa[p]][1] == p; }

void rotate(int x)
{
    int y = fa[x], z = fa[y], dir = check(x), w = ch[x][dir ^ 1];
    pushdown(y), pushdown(x);
    ch[y][dir] = w, fa[w] = y;
    ch[z][check(y)] = x, fa[x] = z;
    ch[x][dir ^ 1] = y, fa[y] = x;
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
    if (!goal)
        root = p;
}

void build(int l, int r, int fat)
{
    if (l > r)
        return;
    int mid = (l + r) >> 1;
    if (mid < fat)
        ch[fat][0] = mid;
    else
        ch[fat][1] = mid;
    siz[mid] = 1, fa[mid] = fat;
    if (l == r)
        return;
    build(l, mid - 1, mid), build(mid + 1, r, mid);
    pushup(mid);
}

int find_k(int k)
{
    int p = root;
    while (p)
    {
        pushdown(p);
        if (siz[lson] + 1 == k)
            return p;
        else if (siz[lson] + 1 < k)
            k -= siz[lson] + 1, p = rson;
        else
            p = lson;
    }
    return p;
}

int main()
{
    scanf("%d", &n);
    units[1].id = 1, units[n + 2].id = n + 2;
    units[1].val = -0x3f3f3f3f, units[n + 2].val = 0x3f3f3f3f;
    for (int i = 2; i <= n + 1; i++)
        scanf("%d", &units[i].val), units[i].id = i;
    sort(units + 1, units + 3 + n);
    build(1, n + 2, 0);
    root = (n + 3) >> 1;
    for (int i = 2; i <= n; i++)
    {
        splay(units[i].id);
        int ans = siz[ch[root][0]] + 1;
        printf("%d ", ans - 1);
        int x = find_k(i - 1), y = find_k(ans + 1);
        splay(x), splay(y, x);
        tag[ch[ch[root][1]][0]] ^= 1;
        swap(ch[ch[ch[root][1]][0]][0], ch[ch[ch[root][1]][0]][1]);
    }
    printf("%d", n);
    return 0;
}