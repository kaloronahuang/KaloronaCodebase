// P4633.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

int n, xi[MAX_N], qtot, level;
vector<int> vec;

struct quad
{
    int x, y1, y2, flag;

    bool operator<(const quad &rhs) const { return x < rhs.x; }
} quads[MAX_N << 2];

int ripe(int x) { return lower_bound(vec.begin(), vec.end(), x) - vec.begin() + 1; }

namespace SegmentTree
{

int nodes[MAX_N << 2], tag[MAX_N << 2];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void pushdown(int p)
{
    if (tag[p])
    {
        tag[lson] += tag[p], tag[rson] += tag[p];
        nodes[lson] += tag[p], nodes[rson] += tag[p];
        tag[p] = 0;
    }
}

void pushup(int p) { nodes[p] = min(nodes[lson], nodes[rson]); }

void update(int ql, int qr, int l, int r, int p, int val)
{
    if (ql <= l && r <= qr)
        return (void)(nodes[p] += val, tag[p] += val);
    pushdown(p);
    if (ql <= mid)
        update(ql, qr, l, mid, lson, val);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, val);
    pushup(p);
}

int query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return nodes[p];
    pushdown(p);
    int ret = 0x7fffffff;
    if (ql <= mid)
        ret = min(ret, query(ql, qr, l, mid, lson));
    if (mid < qr)
        ret = min(ret, query(ql, qr, mid + 1, r, rson));
    return ret;
}

} // namespace SegmentTree

int main()
{
    scanf("%d", &n);
    for (int i = 1, ptot; i <= n; i++)
    {
        scanf("%d", &ptot);
        for (int j = 1; j <= ptot; j++)
            scanf("%d", &xi[j]);
        for (int j = 3; j < ptot; j += 2)
        {
            quads[++qtot] = quad{xi[j], xi[j - 1], xi[j + 1], xi[j - 1] < xi[j + 1] ? -1 : 1};
            vec.push_back(xi[j - 1]), vec.push_back(xi[j + 1]);
        }
        quads[++qtot] = quad{xi[1], xi[2], xi[ptot], xi[2] < xi[ptot] ? 1 : -1};
        vec.push_back(xi[2]), vec.push_back(xi[ptot]);
    }
    sort(vec.begin(), vec.end()), vec.erase(unique(vec.begin(), vec.end()), vec.end());
    sort(quads + 1, quads + 1 + qtot), level = qtot;
    int ans = 0;
    for (int i = 1; i <= qtot; i++)
    {
        int y1 = ripe(quads[i].y1), y2 = ripe(quads[i].y2), upper = max(y1, y2), lower = min(y1, y2);
        SegmentTree::update(lower, upper, 1, level, 1, quads[i].flag);
        ans = max(ans, SegmentTree::query(lower, upper, 1, level, 1));
    }
    printf("%d\n", ans);
    return 0;
}