// BZ3413.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, m, pos[MAX_N << 1];
char org[MAX_N];

namespace SegmentTree
{

    struct node
    {
        int lson, rson, val;
    } nodes[MAX_N * 60];

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

    int query(int ql, int qr, int l, int r, int p)
    {
        if (ql > qr)
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

} // namespace SegmentTree

struct node
{
    int ch[10], link, dep;
} nodes[MAX_N << 1];

int ptot = 1, last_ptr = 1, bucket[MAX_N << 1], rnk[MAX_N << 1], roots[MAX_N << 1];

void insert(int c)
{
    int pre = last_ptr, p = last_ptr = ++ptot;
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
        rnk[bucket[nodes[i].dep]--] = i;
    for (int i = ptot; i >= 2; i--)
    {
        if (pos[rnk[i]] != 0)
            roots[rnk[i]] = SegmentTree::update(pos[rnk[i]], 1, n, roots[rnk[i]]);
        roots[nodes[rnk[i]].link] = SegmentTree::merge(roots[nodes[rnk[i]].link], roots[rnk[i]]);
        if (pos[rnk[i]] == 0)
            pos[rnk[i]] = 1e9;
    }
    for (int i = ptot; i >= 2; i--)
        pos[nodes[rnk[i]].link] = min(pos[rnk[i]], pos[nodes[rnk[i]].link]);
}

int main()
{
    scanf("%d%s", &n, org + 1);
    for (int i = 1; i <= n; i++)
        insert(org[i] - '0'), pos[last_ptr] = i;
    radixSort(), scanf("%d", &m);
    while (m--)
    {
        int qlen = 0, p = 1, ans = 0, bound = 0;
        scanf("%s", org + 1), qlen = strlen(org + 1);
        // get the node id;
        bool flag = true;
        for (int i = 1; i <= qlen && flag; i++)
        {
            int c = org[i] - '0';
            if (nodes[p].ch[c] == 0)
                flag = false;
            else
                p = nodes[p].ch[c];
        }
        if (!flag)
            ans += n;
        else
            bound = pos[p], ans += bound - qlen;
        p = 1;
        for (int i = 1; i <= qlen; i++)
        {
            int c = org[i] - '0';
            if (nodes[p].ch[c] == 0)
                break;
            p = nodes[p].ch[c];
            ans += SegmentTree::query(i, flag ? min(n, bound + i - qlen) : n, 1, n, roots[p]);
        }
        printf("%d\n", ans);
    }
    return 0;
}