// P3380.cpp
#include <bits/stdc++.h>
#define rint register int

using namespace std;

const int MAX_N = 1e7 + 200, INF = 2147483647;

int n, q, seq[MAX_N];

char buf[1 << 22], *p1, *p2;
#define gc()                                                                 \
    (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 22, stdin), p1 == p2) \
         ? EOF                                                               \
         : *p1++)

inline int read()
{
    int x = 0, f = 1;
    char ch = gc();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = gc();
    }
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + ch - '0', ch = gc();
    return x * f;
}

namespace Splay
{

#define lson ch[p][0]
#define rson ch[p][1]

int ch[MAX_N][2], siz[MAX_N], fa[MAX_N], roots[MAX_N], value[MAX_N], cnt[MAX_N], ptot;

inline void clear(int p) { lson = rson = siz[p] = fa[p] = cnt[p] = value[p] = 0; }

inline void pushup(int p) { siz[p] = siz[lson] + siz[rson] + cnt[p]; }

inline int check(int p) { return ch[fa[p]][1] == p; }

inline void rotate(int x)
{
    int y = fa[x], z = fa[y], dir = check(x), w = ch[x][dir ^ 1];
    fa[x] = z;
    if (z != 0)
        ch[z][ch[z][1] == y] = x;
    fa[y] = x, ch[x][dir ^ 1] = y;
    fa[w] = y, ch[y][dir] = w;
    pushup(y), pushup(x);
}

inline void splay(int rootId, int p, int goal = 0)
{
    for (rint fat = fa[p]; (fat = fa[p]) != goal; rotate(p))
        if (fa[fat] != goal)
            rotate(check(p) == check(fat) ? fat : p);
    if (goal == 0)
        roots[rootId] = p;
}

inline int init(int val, int fat)
{
    value[++ptot] = val, fa[ptot] = fat, cnt[ptot] = 1;
    pushup(ptot);
    return ptot;
}

inline void insert(int rootId, int val)
{
    int p = roots[rootId], pre = 0;
    if (p == 0)
    {
        p = init(val, 0), roots[rootId] = p;
        return;
    }
    while (p != 0 && value[p] != val)
        pre = p, p = ch[p][value[p] < val];
    if (value[p] == val && p != 0)
        cnt[p]++;
    else
    {
        p = init(val, pre);
        if (pre)
            ch[pre][val > value[pre]] = p;
    }
    splay(rootId, p);
}

inline void find(int rootId, int val)
{
    int p = roots[rootId];
    if (!p)
        return;
    while (ch[p][value[p] < val] && value[p] != val)
        p = ch[p][value[p] < val];
    splay(rootId, p);
}

inline int getNear(int rootId, int val, int opt)
{
    find(rootId, val);
    int p = roots[rootId];
    if ((opt && value[p] < val) || (!opt && value[p] > val))
        return p;
    p = ch[p][opt ^ 1];
    while (ch[p][opt])
        p = ch[p][opt];
    return p;
}

inline void remove(int rootId, int val)
{
    int pre = getNear(rootId, val, 1), succ = getNear(rootId, val, 0);
    splay(rootId, succ), splay(rootId, pre, succ);
    int target = ch[pre][1];
    if (cnt[target] > 1)
        cnt[target]--, splay(rootId, target);
    else
        ch[pre][1] = 0, clear(target);
    pushup(pre);
}

#undef rson
#undef lson

} // namespace Splay

namespace SegmentTree
{

#define lson (p << 1)
#define rson ((p << 1) | 1)

inline void build(int l, int r, int p)
{
    Splay::insert(p, INF), Splay::insert(p, -INF);
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(l, mid, lson), build(mid + 1, r, rson);
}

inline void insert(int qx, int l, int r, int p, int val)
{
    int mid = (l + r) >> 1;
    Splay::insert(p, val);
    if (l == r)
        return;
    if (qx <= mid)
        insert(qx, l, mid, lson, val);
    else
        insert(qx, mid + 1, r, rson, val);
}

inline int getRank(int ql, int qr, int l, int r, int p, int val)
{
	if (l > qr || r < ql)
		return 0;
    if (ql <= l && r <= qr)
    {
        Splay::find(p, val);
        int u = Splay::roots[p];
        if (Splay::value[u] >= val)
            return Splay::siz[Splay::ch[u][0]] - 1;
        else
            return Splay::siz[Splay::ch[u][0]] + Splay::cnt[u] - 1;
    }
    int mid = (l + r) >> 1, ret = 0;
    return getRank(ql, qr, l, mid, lson, val) + getRank(ql, qr, mid + 1, r, rson, val);
}

inline void update(int qx, int l, int r, int p, int val)
{
    Splay::remove(p, seq[qx]), Splay::insert(p, val);
    if (l == r)
    {
        seq[qx] = val;
        return;
    }
    int mid = (l + r) >> 1;
    if (qx <= mid)
        update(qx, l, mid, lson, val);
    else
        update(qx, mid + 1, r, rson, val);
}

inline int getPre(int ql, int qr, int l, int r, int p, int val)
{
	if (l > qr || r < ql)
		return -INF;
    if (ql <= l && r <= qr)
        return Splay::value[Splay::getNear(p, val, 1)];
    int mid = (l + r) >> 1;
    return max(getPre(ql, qr, l, mid, lson, val), getPre(ql, qr, mid + 1, r, rson, val));
}

inline int getSucc(int ql, int qr, int l, int r, int p, int val)
{
	if (l > qr || r < ql)
		return INF;
    if (ql <= l && r <= qr)
        return Splay::value[Splay::getNear(p, val, 0)];
    int mid = (l + r) >> 1;
    return min(getSucc(ql, qr, l, mid, lson, val), getSucc(ql, qr, mid + 1, r, rson, val));
}

inline int getKth(int ql, int qr, int k)
{
    int l = 0, r = 1e8, mid, check, res;
    while (l <= r)
    {
        mid = (l + r) >> 1, check = getRank(ql, qr, 1, n, 1, mid) + 1;
        if (check > k)
            r = mid - 1;
        else
            l = mid + 1, res = mid;
    }
    return res;
}

#undef mid
#undef rson
#undef lson

} // namespace SegmentTree

int main()
{
    n = read(), q = read();
    SegmentTree::build(1, n, 1);
    for (rint i = 1; i <= n; i++)
        seq[i] = read(), SegmentTree::insert(i, 1, n, 1, seq[i]);
    while (q--)
    {
        int opt, x, y, z;
        opt = read(), x = read(), y = read();
        if (opt == 1)
            z = read(), printf("%d\n", SegmentTree::getRank(x, y, 1, n, 1, z) + 1);
        else if (opt == 2)
            z = read(), printf("%d\n", SegmentTree::getKth(x, y, z));
        else if (opt == 3)
            SegmentTree::update(x, 1, n, 1, y);
        else if (opt == 4)
            z = read(), printf("%d\n", SegmentTree::getPre(x, y, 1, n, 1, z));
        else if (opt == 5)
            z = read(), printf("%d\n", SegmentTree::getSucc(x, y, 1, n, 1, z));
    }
    return 0;
}
