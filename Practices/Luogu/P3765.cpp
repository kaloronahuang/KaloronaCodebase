// P3765.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 200, INF = 0x3f3f3f3f;

int n, q, seq[MAX_N];

namespace segment
{

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

struct node
{
    int cnt, mode;
} nodes[MAX_N << 2];

node pushup(const node &ls, const node &rs)
{
    node ret;
    ret.cnt = ret.mode = 0;
    if (ls.mode == rs.mode)
        ret.mode = ls.mode, ret.cnt = ls.cnt + rs.cnt;
    else if (ls.cnt == rs.cnt)
        ret.mode = max(ls.mode, rs.mode);
    else
        ret.mode = ((ls.cnt > rs.cnt) ? (ls.mode) : (rs.mode)), ret.cnt = abs(ls.cnt - rs.cnt);
    return ret;
}

void build(int l, int r, int p)
{
    if (l == r)
    {
        nodes[p].cnt = 1, nodes[p].mode = seq[l];
        return;
    }
    build(l, mid, lson), build(mid + 1, r, rson);
    nodes[p] = pushup(nodes[lson], nodes[rson]);
}

void update(int qx, int l, int r, int p, int val)
{
    if (l == r)
    {
        nodes[p].cnt = 1, nodes[p].mode = val;
        return;
    }
    if (qx <= mid)
        update(qx, l, mid, lson, val);
    else
        update(qx, mid + 1, r, rson, val);
    nodes[p] = pushup(nodes[lson], nodes[rson]);
}

node query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return nodes[p];
    node ret;
    ret.cnt = ret.mode = 0;
    if (ql <= mid)
        ret = query(ql, qr, l, mid, lson);
    if (mid < qr)
        ret = pushup(ret, query(ql, qr, mid + 1, r, rson));
    return ret;
}

#undef mid
#undef rson
#undef lson

} // namespace segment

int ch[MAX_N * 10][2], fa[MAX_N * 10], siz[MAX_N * 10], val[MAX_N * 10], ptot;

struct splay_tree
{

#define lson ch[p][0]
#define rson ch[p][1]

    int root;

    void pushup(int p) { return (void)(siz[p] = siz[lson] + siz[rson] + 1); }

    int check(int p) { return ch[fa[p]][1] == p; }

    void rotate(int x)
    {
        int y = fa[x], z = fa[y], dir = check(x), w = ch[x][dir ^ 1];
        fa[x] = z;
        if (z != 0)
            ch[z][ch[z][1] == y] = x;
        fa[w] = y, ch[y][dir] = w;
        fa[y] = x, ch[x][dir ^ 1] = y;
        pushup(y), pushup(x);
    }

    void splay(int p, int goal = 0)
    {
        for (int fat = fa[p]; (fat = fa[p]) != goal; rotate(p))
            if (fa[fat] != goal)
                rotate(check(p) == check(fat) ? fat : p);
        if (goal == 0)
            root = p;
    }

    void find(int k)
    {
        int p = root;
        if (p == 0)
            return;
        while (ch[p][k > val[p]] && val[p] != k)
            p = ch[p][k > val[p]];
        splay(p);
    }

    int nxtNode(int k, int op)
    {
        find(k);
        int p = root;
        if ((val[p] < k && op == 0) || (val[p] > k && op == 1))
            return p;
        p = ch[p][op];
        while (ch[p][op ^ 1])
            p = ch[p][op ^ 1];
        return p;
    }

    void insert(int v)
    {
        int p = root, fat = 0;
        while (p)
            siz[p]++, fat = p, p = ch[p][v > val[p]];
        int np = ++ptot;
        val[np] = v;
        if (fat != 0)
            ch[fat][v > val[fat]] = np;
        fa[np] = fat, siz[np] = 1, splay(np);
    }

    void del(int p)
    {
        int l = nxtNode(p, 0), r = nxtNode(p, 1);
        splay(l), splay(r, l), ch[r][0] = 0;
        pushup(r), pushup(l);
    }

    int getRk(int x)
    {
        find(x);
        if (val[root] != x)
            x = val[nxtNode(x, 0)];
        int p = root, ans = 0;
        while (true)
        {
            if (val[p] > x)
                p = lson;
            else if (val[p] == x)
            {
                ans += siz[lson], splay(p, 0);
                return ans;
            }
            else
                ans += siz[lson] + 1, p = rson;
        }
    }

#undef rson
#undef lson

} roots[MAX_N];

int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i]), roots[i].insert(-INF), roots[i].insert(INF);
    for (int i = 1; i <= n; i++)
        roots[seq[i]].insert(i);
    segment::build(1, n, 1);
    while (q--)
    {
        int l, r, s, k;
        scanf("%d%d%d%d", &l, &r, &s, &k);
        int mode = segment::query(l, r, 1, n, 1).mode;
        int cnt = roots[mode].getRk(r) - roots[mode].getRk(l - 1);
        if (cnt > ((r - l + 1) >> 1))
            s = mode;
        for (int i = 1; i <= k; i++)
        {
            int pt;
            scanf("%d", &pt);
            segment::update(pt, 1, n, 1, s);
            roots[seq[pt]].del(pt), seq[pt] = s;
            roots[seq[pt]].insert(pt);
        }
        printf("%d\n", s);
    }
    int mode = segment::nodes[1].mode;
    int cnt = roots[mode].getRk(n);
    if (cnt > (n >> 1))
        printf("%d\n", mode);
    else
        puts("-1");
    return 0;
}