// CF666E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 200 + 5e4;

int n, m, q, pos[MAX_N];
char str[MAX_N];

namespace SegmentTree
{

struct node
{
    int lson, rson;
    short sum, id;
} nodes[MAX_N * 60];

int ptot, roots[MAX_N << 1];

#define mid ((l + r) >> 1)

node pushup(const node &ls, const node &rs)
{
    node ret = ls;
    if (rs.sum > ls.sum || ret.id == 0)
        ret = rs;
    return ret;
}

void pushup(int p)
{
    if (nodes[p].lson == 0 || nodes[p].rson == 0)
    {
        nodes[p].sum = max(nodes[nodes[p].lson].sum, nodes[nodes[p].rson].sum);
        nodes[p].id = max(nodes[nodes[p].lson].id, nodes[nodes[p].rson].id);
    }
    else
    {
        nodes[p].sum = max(nodes[nodes[p].lson].sum, nodes[nodes[p].rson].sum);
        nodes[p].id = nodes[nodes[p].lson].sum < nodes[nodes[p].rson].sum ? nodes[nodes[p].rson].id : nodes[nodes[p].lson].id;
    }
}

int update(int qx, int l, int r, int p)
{
    if (p == 0)
        p = ++ptot;
    if (l == r)
    {
        nodes[p].id = l, nodes[p].sum++;
        return p;
    }
    if (qx <= mid)
        nodes[p].lson = update(qx, l, mid, nodes[p].lson);
    else
        nodes[p].rson = update(qx, mid + 1, r, nodes[p].rson);
    pushup(p);
    return p;
}

node query(int ql, int qr, int l, int r, int p)
{
    if (p == 0)
        return node{0, 0, 0, 0};
    if (ql <= l && r <= qr)
        return nodes[p];
    node ret = node{0, 0, 0, 0};
    if (ql <= mid)
        ret = query(ql, qr, l, mid, nodes[p].lson);
    if (mid < qr)
        ret = pushup(ret, query(ql, qr, mid + 1, r, nodes[p].rson));
    return ret;
}

int merge(int x, int y, int l, int r)
{
    if (x == 0 || y == 0)
        return x + y;
    int p = ++ptot;
    if (l == r)
    {
        nodes[p].id = l, nodes[p].sum = nodes[x].sum + nodes[y].sum;
        return p;
    }
    nodes[p].lson = merge(nodes[x].lson, nodes[y].lson, l, mid);
    nodes[p].rson = merge(nodes[x].rson, nodes[y].rson, mid + 1, r);
    pushup(p);
    return p;
}

} // namespace SegmentTree

namespace SAM
{

struct node
{
    int ch[26], dep, link;
} nodes[MAX_N << 1];

int ptot = 1, last_ptr = 1, bucket[MAX_N << 1], rnk[MAX_N << 1];
int fa[25][MAX_N << 1];

void insert(int pre, int c)
{
    if (nodes[pre].ch[c] == 0)
    {
        int p = last_ptr = ++ptot;
        nodes[p].dep = nodes[pre].dep + 1;
        while (pre && nodes[pre].ch[c] == 0)
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
                nodes[p].link = nodes[q].link = clone;
                while (pre && nodes[pre].ch[c] == q)
                    nodes[pre].ch[c] = clone, pre = nodes[pre].link;
            }
        }
    }
    else
    {
        int q = nodes[pre].ch[c];
        if (nodes[q].dep == nodes[pre].dep + 1)
            last_ptr = q;
        else
        {
            int clone = last_ptr = ++ptot;
            nodes[clone] = nodes[q], nodes[clone].dep = nodes[pre].dep + 1;
            nodes[q].link = clone;
            while (pre && nodes[pre].ch[c] == q)
                nodes[pre].ch[c] = clone, pre = nodes[pre].link;
        }
    }
}

void radixSort()
{
    using SegmentTree::merge;
    using SegmentTree::roots;
    for (int i = 1; i <= ptot; i++)
        bucket[nodes[i].dep]++;
    for (int i = 1; i <= ptot; i++)
        bucket[i] += bucket[i - 1];
    for (int i = 1; i <= ptot; i++)
        rnk[bucket[nodes[i].dep]--] = i;
    for (int i = ptot; i >= 1; i--)
        if (nodes[rnk[i]].link != 0)
            roots[nodes[rnk[i]].link] = merge(roots[nodes[rnk[i]].link], roots[rnk[i]], 1, m);
    for (int i = 1; i <= ptot; i++)
        fa[0][i] = nodes[i].link;
    for (int i = 1; i <= 24; i++)
        for (int j = 1; j <= ptot; j++)
            fa[i][j] = fa[i - 1][fa[i - 1][j]];
}

} // namespace SAM

int main()
{
    scanf("%s", str + 1), n = strlen(str + 1);
    for (int i = 1; i <= n; i++)
    {
        using namespace SAM;
        insert(last_ptr, str[i] - 'a'), pos[i] = last_ptr;
    }
    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%s", str + 1), SAM::last_ptr = 1;
        for (int idx = 1; str[idx] != '\0'; idx++)
        {
            SAM::insert(SAM::last_ptr, str[idx] - 'a');
            using namespace SegmentTree;
            roots[SAM::last_ptr] = update(i, 1, m, roots[SAM::last_ptr]);
        }
    }
    using namespace SAM;
    radixSort(), scanf("%d", &q);
    while (q--)
    {
        int l, r, pl, pr, p;
        scanf("%d%d%d%d", &l, &r, &pl, &pr), p = pos[pr];
        for (int i = 24; i >= 0; i--)
            if (nodes[fa[i][p]].dep >= pr - pl + 1)
                p = fa[i][p];
        SegmentTree::node res = SegmentTree::query(l, r, 1, m, SegmentTree::roots[p]);
        printf("%d %d\n", max(l, 1 * res.id), res.sum);
    }
    return 0;
}