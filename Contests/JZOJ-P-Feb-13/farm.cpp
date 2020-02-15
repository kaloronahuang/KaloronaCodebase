// farm.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200;

int W, H, n, gans, lstk[MAX_N], rstk[MAX_N];

struct point
{
    int x, y;
    bool operator<(const point &rhs) const { return y < rhs.y || (y == rhs.y && x < rhs.x); }
} pts[MAX_N];

void fileIO()
{
	freopen("farm.in", "r", stdin);
	freopen("farm.out", "w", stdout);
}

namespace SegmentTree
{

int nodes[MAX_N << 2], tag[MAX_N << 2];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void pushdown(int p)
{
    if (tag[p] != 0)
    {
        nodes[lson] += tag[p], nodes[rson] += tag[p];
        tag[lson] += tag[p], tag[rson] += tag[p];
        tag[p] = 0;
    }
}

void pushup(int p) { nodes[p] = max(nodes[lson], nodes[rson]); }

void clear() { memset(nodes, 0, sizeof(nodes)), memset(tag, 0, sizeof(tag)); }

void update(int ql, int qr, int l, int r, int p, int val)
{
    if (qr < l || r < ql)
        return;
    if (ql <= l && r <= qr)
        return (void)(nodes[p] += val, tag[p] += val);
    pushdown(p);
    if (ql <= mid)
        update(ql, qr, l, mid, lson, val);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, val);
    pushup(p);
}

#undef mid
#undef rson
#undef lson

} // namespace SegmentTree

void calc()
{
    SegmentTree::clear();
    for (int i = 1; i <= n; i++)
        SegmentTree::update(i, i, 1, n, 1, -pts[i].y);
    int ltail = 0, rtail = 0;
    for (int i = 1; i <= n; i++)
    {
        if (i > 1)
            SegmentTree::update(i - 1, i - 1, 1, n, 1, W);
        gans = max(gans, pts[i].y + SegmentTree::nodes[1]);
        if (pts[i].x <= (W >> 1))
        {
            SegmentTree::update(lstk[ltail], i - 1, 1, n, 1, -pts[i].x);
            while (ltail && pts[lstk[ltail]].x < pts[i].x)
                SegmentTree::update(lstk[ltail - 1], lstk[ltail] - 1, 1, n, 1, pts[lstk[ltail]].x - pts[i].x), ltail--;
            lstk[++ltail] = i;
        }
        else
        {
            SegmentTree::update(rstk[rtail], i - 1, 1, n, 1, pts[i].x - W);
            while (rtail && pts[rstk[rtail]].x > pts[i].x)
                SegmentTree::update(rstk[rtail - 1], rstk[rtail] - 1, 1, n, 1, pts[i].x - pts[rstk[rtail]].x), rtail--;
            rstk[++rtail] = i;
        }
    }
}

int main()
{
    fileIO();
    scanf("%d%d%d", &W, &H, &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &pts[i].x, &pts[i].y);
    pts[++n] = point{0, 0}, pts[++n] = point{W, H};
    sort(pts + 1, pts + 1 + n), calc();
    for (int i = 1; i <= n; i++)
        swap(pts[i].x, pts[i].y);
    swap(W, H), sort(pts + 1, pts + 1 + n), calc();
    printf("%d\n", gans << 1);
    return 0;
}