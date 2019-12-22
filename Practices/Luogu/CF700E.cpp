// CF700E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 401000;

int n;
char str[MAX_N];

namespace SAM
{

struct node
{
    int dep, link, ch[26], pos;
} nodes[MAX_N << 1];

int ptot = 1, last_ptr = 1;

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

} // namespace SAM

namespace SegmentTree
{

struct node
{
    int sum, lson, rson;
} nodes[MAX_N * 25];

int ptot;

void pushup(int p) { nodes[p].sum = nodes[nodes[p].lson].sum + nodes[nodes[p].rson].sum; }

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

int merge(int x, int y, int l, int r)
{
    if (x == 0 || y == 0)
        return x + y;
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

int roots[MAX_N << 1], bucket[MAX_N << 1], rnk[MAX_N << 1], top[MAX_N << 1], dp[MAX_N << 1];

int main()
{
    scanf("%d%s", &n, str + 1);
    for (int i = 1; i <= n; i++)
        SAM::insert(str[i] - 'a', i), roots[SAM::last_ptr] = SegmentTree::update(i, 1, n, roots[SAM::last_ptr]);
    for (int i = 1; i <= SAM::ptot; i++)
        bucket[SAM::nodes[i].dep]++;
    for (int i = 1; i <= SAM::ptot; i++)
        bucket[i] += bucket[i - 1];
    for (int i = 1; i <= SAM::ptot; i++)
        rnk[bucket[SAM::nodes[i].dep]--] = i;
    for (int i = SAM::ptot; i >= 1; i--)
        if (SAM::nodes[rnk[i]].link != 0)
            roots[SAM::nodes[rnk[i]].link] = SegmentTree::merge(roots[SAM::nodes[rnk[i]].link], roots[rnk[i]], 1, n);
    int ans = 1;
    for (int i = 2; i <= SAM::ptot; i++)
    {
        int u = rnk[i], fa = SAM::nodes[u].link;
        if (fa == 1)
        {
            dp[u] = 1, top[u] = u;
            continue;
        }
        int l = SAM::nodes[u].pos - SAM::nodes[u].dep + SAM::nodes[top[fa]].dep;
        int r = SAM::nodes[u].pos - 1;
        int x = SegmentTree::query(l, r, 1, n, roots[top[fa]]);
        if (x > 0)
            dp[u] = dp[fa] + 1, top[u] = u;
        else
            dp[u] = dp[fa], top[u] = top[fa];
        ans = max(ans, dp[u]);
    }
    printf("%d\n", ans);
    return 0;
}