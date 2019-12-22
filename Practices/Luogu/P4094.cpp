// P4094.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, q;
char str[MAX_N];

namespace SAM
{

struct node
{
    int link, dep, ch[26];
} nodes[MAX_N << 1];

int ptot = 1, last_ptr = 1;

void insert(int c)
{
    int pre = last_ptr, p = last_ptr = ++ptot;
    nodes[p].dep = nodes[pre].dep + 1;
    while (pre != 0 && nodes[pre].ch[c] == 0)
        nodes[pre].ch[c] = p, pre = nodes[pre].link;
    if (pre == 0)
        nodes[p].link = 1;
    else
    {
        int q = nodes[pre].ch[c];
        if (nodes[q].dep == nodes[pre].dep + 1)
            nodes[p].link = q;
        else
        {
            int clone = ++ptot;
            nodes[clone] = nodes[q], nodes[clone].dep = nodes[pre].dep + 1;
            nodes[q].link = nodes[p].link = clone;
            while (pre != 0 && nodes[pre].ch[c] == q)
                nodes[pre].ch[c] = clone, pre = nodes[pre].link;
        }
    }
}

} // namespace SAM

namespace SegmentTree
{

struct node
{
    int lson, rson, sum;
} nodes[MAX_N << 6];

int ptot;

void pushup(int p) { nodes[p].sum = nodes[nodes[p].lson].sum + nodes[nodes[p].rson].sum; }

int merge(int x, int y, int l, int r)
{
    if (x == 0)
        return y;
    if (y == 0)
        return x;
    if (l == r)
    {
        nodes[x].sum += nodes[y].sum;
        return x;
    }
    int mid = (l + r) >> 1, p = ++ptot;
    nodes[p].lson = merge(nodes[x].lson, nodes[y].lson, l, mid);
    nodes[p].rson = merge(nodes[x].rson, nodes[y].rson, mid + 1, r);
    pushup(p);
    return p;
}

int update(int qx, int l, int r, int p)
{
    if (p == 0)
        p = ++ptot;
    if (l == r)
    {
        nodes[p].sum++;
        return p;
    }
    int mid = (l + r) >> 1;
    if (qx <= mid)
        nodes[p].lson = update(qx, l, mid, nodes[p].lson);
    else
        nodes[p].rson = update(qx, mid + 1, r, nodes[p].rson);
    pushup(p);
    return p;
}

int query(int ql, int qr, int l, int r, int p)
{
    if (p == 0)
        return 0;
    if (ql <= l && r <= qr)
        return nodes[p].sum;
    int mid = (l + r) >> 1, ret = 0;
    if (ql <= mid)
        ret += query(ql, qr, l, mid, nodes[p].lson);
    if (mid < qr)
        ret += query(ql, qr, mid + 1, r, nodes[p].rson);
    return ret;
}

} // namespace SegmentTree

int roots[MAX_N << 1], pos[MAX_N], perm[MAX_N << 1], fa[21][MAX_N << 1], bucket[MAX_N << 1];

bool compare(const int &rhs1, const int &rhs2)
{
    return SAM::nodes[rhs1].dep < SAM::nodes[rhs2].dep;
}

bool check(int mid, int p, int l, int r)
{
    for (int i = 20; i >= 0; i--)
        if (SAM::nodes[fa[i][p]].dep >= mid && fa[i][p])
            p = fa[i][p];
    return SegmentTree::query(l + mid - 1, r, 1, n, roots[p]) > 0;
}

int main()
{
    scanf("%d%d%s", &n, &q, str + 1);
    reverse(str + 1, str + 1 + n);
    for (int i = 1; i <= n; i++)
    {
        SAM::insert(str[i] - 'a');
        roots[SAM::last_ptr] = SegmentTree::update(i, 1, n, roots[SAM::last_ptr]);
        pos[i] = SAM::last_ptr;
    }
    for (int i = 1; i <= SAM::ptot; i++)
        perm[i] = i;
    for (int i = 1; i <= SAM::ptot; i++)
        bucket[SAM::nodes[i].dep]++;
    for (int i = 1; i <= SAM::ptot; i++)
        bucket[i] += bucket[i - 1];
    for (int i = 1; i <= SAM::ptot; i++)
        perm[bucket[SAM::nodes[i].dep]--] = i;
    for (int i = SAM::ptot; i >= 1; i--)
        if (SAM::nodes[perm[i]].link != 0)
        {
            roots[SAM::nodes[perm[i]].link] =
                SegmentTree::merge(roots[SAM::nodes[perm[i]].link], roots[perm[i]], 1, n);
        }
    for (int i = 1; i <= SAM::ptot; i++)
        fa[0][i] = SAM::nodes[i].link;
    for (int i = 1; i <= 20; i++)
        for (int j = 1; j <= SAM::ptot; j++)
            fa[i][j] = fa[i - 1][fa[i - 1][j]];
    while (q--)
    {
        int a, b, c, d;
        scanf("%d%d%d%d", &a, &b, &c, &d);
        a = n - a + 1, b = n - b + 1;
        c = n - c + 1, d = n - d + 1;
        int l = 0, r = min(a - b + 1, c - d + 1), ret = 0;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            if (check(mid, pos[c], b, a))
                l = mid + 1, ret = mid;
            else
                r = mid - 1;
        }
        printf("%d\n", ret);
    }
    return 0;
}