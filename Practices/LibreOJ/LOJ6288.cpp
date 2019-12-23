// LOJ6288.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4e5 + 200;

int roots[MAX_N << 1], n, dp[MAX_N << 1], top[MAX_N << 1];
char str[MAX_N << 1];

namespace SegmentTree
{

struct node
{
    int lson, rson, sum;
} nodes[MAX_N * 25];

#define mid ((l + r) >> 1)

int ptot;

int update(int qx, int l, int r, int p)
{
    if (p == 0)
        p = ++ptot;
    nodes[p].sum++;
    if (l == r)
        return p;
    if (qx <= mid)
        nodes[p].lson = update(qx, l, mid, nodes[p].lson);
    else
        nodes[p].rson = update(qx, mid + 1, r, nodes[p].rson);
    return p;
}

int merge(int x, int y, int l, int r)
{
    if (x == 0 || y == 0)
        return x + y;
    int p = ++ptot;
    nodes[p].sum = nodes[x].sum + nodes[y].sum;
    if (l == r)
        return p;
    nodes[p].lson = merge(nodes[x].lson, nodes[y].lson, l, mid);
    nodes[p].rson = merge(nodes[x].rson, nodes[y].rson, mid + 1, r);
    return p;
}

int query(int ql, int qr, int l, int r, int p)
{
    if (p == 0)
        return 0;
    if (ql <= l && r <= qr)
        return nodes[p].sum;
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
    int ch[26], dep, link, pos;
} nodes[MAX_N << 1];

int ptot = 1, last_ptr = 1, bucket[MAX_N << 1], rnk[MAX_N << 1];

void insert(int c, int idx)
{
    int pre = last_ptr, p = last_ptr = ++ptot;
    nodes[p].dep = nodes[pre].dep + 1, nodes[p].pos = idx;
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
    for (int i = ptot; i >= 1; i--)
        if (nodes[rnk[i]].link != 0)
            roots[nodes[rnk[i]].link] = SegmentTree::merge(roots[nodes[rnk[i]].link], roots[rnk[i]], 1, n);
}

} // namespace SAM

int main()
{
    scanf("%s", str + 1), n = strlen(str + 1);
    for (int i = 1; i <= n; i++)
    {
        SAM::insert(str[i] - 'a', i);
        roots[SAM::last_ptr] = SegmentTree::update(i, 1, n, roots[SAM::last_ptr]);
    }
    SAM::radixSort();
    int ans = 1;
    for (int i = 2; i <= SAM::ptot; i++)
    {
        int p = SAM::rnk[i], fa = SAM::nodes[p].link;
        if (fa == 1)
        {
            dp[p] = 1, top[p] = p;
            continue;
        }
        int x = SegmentTree::query(SAM::nodes[p].pos - SAM::nodes[p].dep + SAM::nodes[top[fa]].dep, SAM::nodes[p].pos - 1, 1, n, roots[top[fa]]);
        if (x > 0)
            dp[p] = dp[fa] + 1, top[p] = p;
        else
            dp[p] = dp[fa], top[p] = top[fa];
        ans = max(ans, dp[p]);
    }
    printf("%d\n", ans);
    return 0;
}