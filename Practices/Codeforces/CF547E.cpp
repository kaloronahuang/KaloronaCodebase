// CF547E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4e5 + 20;

int n, q, pos[MAX_N];
char str[MAX_N];

namespace SegmentTree
{

struct node
{
    int val, lson, rson;
} nodes[MAX_N * 40];

int ptot;

#define mid ((l + r) >> 1)

int update(int qx, int l, int r, int p)
{
    if (p == 0)
        p = ++ptot;
    nodes[p].val++;
    if (l == r)
        return p;
    if (qx <= mid)
        nodes[p].lson = update(qx, l, mid, nodes[p].lson);
    else
        nodes[p].rson = update(qx, mid + 1, r, nodes[p].rson);
    return p;
}

int merge(int x, int y)
{
    if (x == 0 || y == 0)
        return x + y;
    int p = ++ptot;
    nodes[p].val = nodes[x].val + nodes[y].val;
    nodes[p].lson = merge(nodes[x].lson, nodes[y].lson);
    nodes[p].rson = merge(nodes[x].rson, nodes[y].rson);
    return p;
}

int query(int ql, int qr, int l, int r, int p)
{
    if (p == 0)
        return 0;
    if (ql <= l && r <= qr)
        return nodes[p].val;
    int ret = 0;
    if (ql <= mid)
        ret += query(ql, qr, l, mid, nodes[p].lson);
    if (mid < qr)
        ret += query(ql, qr, mid + 1, r, nodes[p].rson);
    return ret;
}

} // namespace SegmentTree

namespace SAM
{

struct node
{
    int ch[26], link, dep;
} nodes[MAX_N];

int ptot = 1, last_ptr = 1, roots[MAX_N], bucket[MAX_N], idx[MAX_N];

void insert(int c)
{
    int pre = last_ptr;
    if (nodes[pre].ch[c] != 0)
    {
        int q = nodes[pre].ch[c];
        if (nodes[q].dep == nodes[pre].dep + 1)
            return (void)(last_ptr = q);
        int clone = last_ptr = ++ptot;
        nodes[clone] = nodes[q], nodes[clone].dep = nodes[pre].dep + 1;
        nodes[q].link = clone;
        while (pre && nodes[pre].ch[c] == q)
            nodes[pre].ch[c] = clone, pre = nodes[pre].link;
        return;
    }
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

void radixSort()
{
    for (int i = 1; i <= ptot; i++)
        bucket[nodes[i].dep]++;
    for (int i = 1; i <= ptot; i++)
        bucket[i] += bucket[i - 1];
    for (int i = 1; i <= ptot; i++)
        idx[bucket[nodes[i].dep]--] = i;
    for (int i = ptot; i >= 1; i--)
        if (nodes[idx[i]].link != 0)
            roots[nodes[idx[i]].link] = SegmentTree::merge(roots[nodes[idx[i]].link], roots[idx[i]]);
}

} // namespace SAM

int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
    {
        SAM::last_ptr = 1, scanf("%s", str + 1);
        for (int j = 1; str[j]; j++)
            SAM::insert(str[j] - 'a'), SAM::roots[SAM::last_ptr] = SegmentTree::update(i, 1, n, SAM::roots[SAM::last_ptr]);
        pos[i] = SAM::last_ptr;
    }
    SAM::radixSort();
    while (q--)
    {
        int l, r, id;
        scanf("%d%d%d", &l, &r, &id);
        printf("%d\n", SegmentTree::query(l, r, 1, n, SAM::roots[pos[id]]));
    }
    return 0;
}