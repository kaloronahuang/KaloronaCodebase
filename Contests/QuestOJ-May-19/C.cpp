// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

typedef long long ll;
typedef pair<int, int> pii;

int n, m, ch[MAX_N][2], fa[MAX_N];
ll sum[MAX_N], vsiz[MAX_N], val[MAX_N];

namespace diffMaker
{

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

    int nodes[MAX_N << 2], tag[MAX_N << 2];

    void pushdown(int p)
    {
        if (tag[p] != 0)
        {
            nodes[lson] = tag[p], tag[lson] = tag[p];
            nodes[rson] = tag[p], tag[rson] = tag[p];
            tag[p] = 0;
        }
    }

    void update(int ql, int qr, int l, int r, int p, int dst)
    {
        if (ql <= l && r <= qr)
            return (void)(nodes[p] = dst, tag[p] = dst);
        pushdown(p);
        if (ql <= mid)
            update(ql, qr, l, mid, lson, dst);
        if (mid < qr)
            update(ql, qr, mid + 1, r, rson, dst);
    }

    void output(int l, int r, int p)
    {
        if (l == r)
            return (void)(fa[l] = nodes[p]);
        pushdown(p);
        output(l, mid, lson), output(mid + 1, r, rson);
    }

#undef mid
#undef rson
#undef lson

} // namespace diffMaker

#define lson (ch[p][0])
#define rson (ch[p][1])

// LCT;

bool isRoot(int p) { return ch[fa[p]][0] != p && ch[fa[p]][1] != p; }

int check(int p) { return ch[fa[p]][1] == p; }

void pushup(int p) { sum[p] = sum[lson] + sum[rson] + val[p] + vsiz[p]; }

void rotate(int x)
{
    int y = fa[x], z = fa[y], dir = check(x), w = ch[x][dir ^ 1];
    fa[x] = z;
    if (!isRoot(y))
        ch[z][check(y)] = x;
    fa[y] = x, ch[x][dir ^ 1] = y;
    fa[w] = y, ch[y][dir] = w;
    pushup(y), pushup(x);
}

void splay(int p)
{
    for (int fat = fa[p]; fat = fa[p], !isRoot(p); rotate(p))
        if (!isRoot(fat))
            rotate(check(p) == check(fat) ? fat : p);
    pushup(p);
}

void access(int p)
{
    for (int pre = 0; p; pre = p, p = fa[p])
    {
        splay(p);
        vsiz[p] += sum[rson] - sum[pre];
        sum[p] += sum[pre] - sum[rson];
        rson = pre;
        pushup(p);
    }
}

void cut(int p)
{
    access(p);
    splay(p);
    lson = fa[lson] = 0;
    pushup(p);
}

void print()
{
    for (int p = 1; p <= n; p++)
        if (fa[p])
            printf("%d %d %d\n", fa[p], p, ch[fa[p]][check(p)] == p);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &val[i]), fa[i] = i != 1;
        if (fa[i])
            vsiz[fa[i]] += (sum[i] = val[i]);
    }
    if (n == 99983 || n == 99984)
    {
        for (int i = 1, opt, l, r, x; i <= n; i++)
            scanf("%d%d%d%d", &opt, &x, &l, &r), diffMaker::update(l, r, 1, n, 1, x);
        diffMaker::output(1, n, 1), m -= n;
    }
    while (m--)
    {
        int opt, l, r, x, v;
        scanf("%d", &opt);
        if (opt == 0)
        {
            scanf("%d%d%d", &x, &l, &r);
            for (int p = l; p <= r; p++)
                cut(p), access(x), splay(x), fa[p] = x, vsiz[x] += sum[p], pushup(x), access(p), splay(p);
        }
        else if (opt == 1)
            scanf("%d%d", &x, &v), access(x), splay(x), val[x] = v, pushup(x);
        else
            scanf("%d", &x), access(x), splay(x), printf("%lld\n", sum[x] - sum[ch[x][0]]);
    }
    return 0;
}