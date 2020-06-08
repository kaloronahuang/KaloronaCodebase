// P4384.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, INF = 0x7fffffff;

int n, q, pos[MAX_N], roots[MAX_N];
char str[MAX_N];

typedef long long ll;

namespace SegmentTree
{

    struct node
    {
        int max_val, min_val;
        ll sum[2];
        void clear() { max_val = min_val = sum[0] = sum[1] = 0; }
    } nodes[MAX_N * 40];

    int ptot, lson[MAX_N * 30], rson[MAX_N * 30];

    node pushup(node ls, node rs)
    {
        node ret;
        ret.clear();
        ret.max_val = max(ls.max_val, rs.max_val);
        ret.min_val = min(ls.min_val, rs.min_val);
        ret.sum[0] = ls.sum[0] + rs.sum[0] + 1LL * rs.min_val * (rs.min_val - ls.max_val);
        ret.sum[1] = ls.sum[1] + rs.sum[1] + rs.min_val - ls.max_val;
        return ret;
    }

#define mid ((l + r) >> 1)

    int queryMax(int ql, int qr, int l, int r, int p)
    {
        if (p == 0)
            return 0;
        if (ql <= l && r <= qr)
            return nodes[p].max_val;
        int ret = 0;
        if (ql <= mid)
            ret = max(ret, queryMax(ql, qr, l, mid, lson[p]));
        if (mid < qr)
            ret = max(ret, queryMax(ql, qr, mid + 1, r, rson[p]));
        return ret;
    }

    int queryMin(int ql, int qr, int l, int r, int p)
    {
        if (p == 0)
            return INF;
        if (ql <= l && r <= qr)
            return nodes[p].min_val;
        int ret = INF;
        if (ql <= mid)
            ret = min(ret, queryMin(ql, qr, l, mid, lson[p]));
        if (mid < qr)
            ret = min(ret, queryMin(ql, qr, mid + 1, r, rson[p]));
        return ret;
    }

    void query(int ql, int qr, int l, int r, int p, node &ret)
    {
        if (p == 0)
            return;
        if (ql <= l && r <= qr)
        {
            if (ret.min_val == 0)
                ret = nodes[p];
            else
                ret = pushup(ret, nodes[p]);
            return;
        }
        if (ql <= mid)
            query(ql, qr, l, mid, lson[p], ret);
        if (mid < qr)
            query(ql, qr, mid + 1, r, rson[p], ret);
    }

    int update(int qx, int l, int r, int p)
    {
        if (p == 0)
            p = ++ptot;
        if (l == r)
        {
            nodes[p].max_val = qx, nodes[p].min_val = qx;
            nodes[p].sum[0] = nodes[p].sum[1] = 0;
            return p;
        }
        if (qx <= mid)
            lson[p] = update(qx, l, mid, lson[p]);
        else
            rson[p] = update(qx, mid + 1, r, rson[p]);
        if (lson[p] && rson[p])
            nodes[p] = pushup(nodes[lson[p]], nodes[rson[p]]);
        else if (lson[p])
            nodes[p] = nodes[lson[p]];
        else
            nodes[p] = nodes[rson[p]];
        return p;
    }

    int merge(int x, int y)
    {
        if (x == 0 || y == 0)
            return x + y;
        int p = ++ptot;
        lson[p] = merge(lson[x], lson[y]);
        rson[p] = merge(rson[x], rson[y]);
        if (lson[p] && rson[p])
            nodes[p] = pushup(nodes[lson[p]], nodes[rson[p]]);
        else
            nodes[p] = lson[p] ? nodes[lson[p]] : nodes[rson[p]];
        return p;
    }

#undef mid

} // namespace SegmentTree

namespace SAM
{

    struct node
    {
        int ch[10], link, dep;
    } nodes[MAX_N];

    int ptot = 1, last_ptr = 1, up[20][MAX_N], bucket[MAX_N], idx[MAX_N];

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
            idx[bucket[nodes[i].dep]--] = i;
        for (int i = 2; i <= ptot; i++)
            up[0][i] = nodes[i].link;
        for (int i = ptot; i >= 2; i--)
            roots[nodes[idx[i]].link] =
                SegmentTree::merge(roots[nodes[idx[i]].link], roots[idx[i]]);
        for (int i = 1; i < 20; i++)
            for (int j = 1; j <= ptot; j++)
                up[i][j] = up[i - 1][up[i - 1][j]];
    }

    int jump(int l, int r)
    {
        int p = pos[r];
        for (int i = 19; i >= 0; i--)
            if (nodes[up[i][p]].dep >= (r - l + 1))
                p = up[i][p];
        return p;
    }

} // namespace SAM

ll binomial2(int n) { return (1LL * n * (n - 1)) >> 1; }

ll query(int l, int r)
{
    int p = SAM::jump(l, r), len = r - l + 1;
    int lft = SegmentTree::nodes[roots[p]].min_val;
    int rig = SegmentTree::nodes[roots[p]].max_val;
    if (lft < rig - (len << 1) + 1 && SegmentTree::queryMax(lft, rig - len, 1, n, roots[p]) - len + 1 > lft)
        return binomial2(n - 1);
    if (rig - len + 1 <= lft)
    {
        SegmentTree::node rnd = SegmentTree::nodes[roots[p]];
        int lm = rig - len + 1;
        ll ret = rnd.sum[0] - rnd.sum[1] * lm + binomial2(lft - lm) + 1LL * (lft - lm) * (n - len);
        return binomial2(n - 1) - ret;
    }
    else
    {
        SegmentTree::node rnd;
        rnd.clear();
        int lm = rig - len + 1, poslm = SegmentTree::queryMax(1, lm, 1, n, roots[p]);
        SegmentTree::query(poslm, lft + len - 1, 1, n, roots[p], rnd);
        int p1 = SegmentTree::queryMax(1, lft + len - 1, 1, n, roots[p]);
        int p2 = SegmentTree::queryMin(lft + len, n, 1, n, roots[p]);
        ll ret = rnd.sum[0] - rnd.sum[1] * lm + (p2 > lm ? 1LL * (lft - (p1 - len + 1)) * (p2 - lm) : 0);
        return binomial2(n - 1) - ret;
    }
}

int main()
{
    scanf("%d%d%s", &n, &q, str + 1);
    for (int i = 1; i <= n; i++)
    {
        SAM::insert(str[i] - '0'), pos[i] = SAM::last_ptr;
        roots[pos[i]] = SegmentTree::update(i, 1, n, roots[pos[i]]);
    }
    SAM::radixSort();
    while (q--)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%lld\n", query(l, r));
    }
    return 0;
}