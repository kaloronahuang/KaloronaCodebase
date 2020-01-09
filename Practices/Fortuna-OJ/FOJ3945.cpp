// FOJ3945.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4e5 + 200;

int T, n, k, roots[MAX_N], yupper, gans;

struct point
{
    int x, y, c;
    bool operator<(const point &rhs) const { return x < rhs.x || (x == rhs.x && y < rhs.y); }
} pts[MAX_N];

typedef multiset<point>::iterator mpit;

bool compareByY(const point &rhs1, const point &rhs2) { return rhs1.y < rhs2.y || (rhs1.y == rhs2.y && rhs1.x < rhs2.x); }

vector<point> ptByColor[MAX_N];
vector<int> mpx, mpy;

inline char nc()
{
    static char buf[10000000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 10000000, stdin), p1 == p2) ? EOF : *p1++;
}

int read()
{
    int x = 0, f = 1;
    char ch = nc();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = nc();
    }
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + ch - '0', ch = nc();
    return x * f;
}

namespace PST
{

struct node
{
    int lson, rson, val;
} nodes[MAX_N << 5];

int ptot;

int update(int qx, int l, int r, int pre)
{
    int p = ++ptot;
    nodes[p] = nodes[pre], nodes[p].val++;
    if (l == r)
        return p;
    int mid = (l + r) >> 1;
    if (qx <= mid)
        nodes[p].lson = update(qx, l, mid, nodes[pre].lson);
    else
        nodes[p].rson = update(qx, mid + 1, r, nodes[pre].rson);
    return p;
}

int query(int ql, int qr, int l, int r, int pre, int p)
{
    if (ql > qr)
        return 0;
    if (ql <= l && r <= qr)
        return nodes[p].val - nodes[pre].val;
    int mid = (l + r) >> 1, ret = 0;
    if (ql <= mid)
        ret += query(ql, qr, l, mid, nodes[pre].lson, nodes[p].lson);
    if (mid < qr)
        ret += query(ql, qr, mid + 1, r, nodes[pre].rson, nodes[p].rson);
    return ret;
}

void init()
{
    ptot = 0;
    int last_ptr = 0;
    for (int i = 1, r = 0; i <= n; i = r + 1)
    {
        r = i, roots[pts[i].x] = update(pts[i].y, 1, yupper, last_ptr), last_ptr = roots[pts[i].x];
        while (r + 1 <= n && pts[r + 1].x == pts[i].x)
            r++, roots[pts[i].x] = update(pts[r].y, 1, yupper, last_ptr), last_ptr = roots[pts[i].x];
    }
}

} // namespace PST

int ripe(vector<int> &vec, int x) { return lower_bound(vec.begin(), vec.end(), x) - vec.begin() + 1; }

void processCategory(int color)
{
    using namespace PST;
    if (ptByColor[color].empty())
        return (void)(gans = max(gans, n));
    sort(ptByColor[color].begin(), ptByColor[color].end());
    // horizontal intervals;
    gans = max(gans, query(1, yupper, 1, yupper, 0, roots[ptByColor[color].front().x - 1]));
    for (int i = 1, siz = ptByColor[color].size(); i < siz; i++)
    {
        point pt = ptByColor[color][i];
        gans = max(gans, query(1, yupper, 1, yupper, roots[ptByColor[color][i - 1].x], roots[pt.x - 1]));
        continue;
    }
    gans = max(gans, query(1, yupper, 1, yupper, roots[ptByColor[color].back().x], roots[mpx.size()]));
    // looking up;
    sort(ptByColor[color].begin(), ptByColor[color].end(), compareByY);
    multiset<point> ms;
    for (int siz = ptByColor[color].size(), i = siz - 1; i >= 0; i--)
    {
        mpit curt = ms.insert(ptByColor[color][i]);
        int baseLine = ptByColor[color][i].y + 1;
        int l, r;
        if (curt != ms.begin())
            curt--, l = curt->x, curt++;
        else
            l = 0;
        curt++;
        if (curt != ms.end())
            r = curt->x - 1;
        else
            r = mpx.size();
        curt--;
        gans = max(gans, query(baseLine, yupper, 1, yupper, roots[l], roots[r]));
    }
    ms.clear();
    for (int siz = ptByColor[color].size(), i = 0; i < siz; i++)
    {
        mpit curt = ms.insert(ptByColor[color][i]);
        int baseLine = ptByColor[color][i].y - 1;
        int l, r;
        if (curt != ms.begin())
            curt--, l = curt->x, curt++;
        else
            l = 0;
        curt++;
        if (curt != ms.end())
            r = curt->x - 1;
        else
            r = mpx.size();
        curt--;
        gans = max(gans, query(1, baseLine, 1, yupper, roots[l], roots[r]));
    }
}

int main()
{
    T = read();
    while (T--)
    {
        n = read(), k = read();
        mpx.clear(), mpy.clear(), gans = 0;
        for (int i = 1; i <= n; i++)
        {
            pts[i].x = read(), pts[i].y = read(), pts[i].c = read();
            mpx.push_back(pts[i].x), mpy.push_back(pts[i].y);
        }
        sort(mpx.begin(), mpx.end()), mpx.erase(unique(mpx.begin(), mpx.end()), mpx.end());
        sort(mpy.begin(), mpy.end()), mpy.erase(unique(mpy.begin(), mpy.end()), mpy.end());
        yupper = mpy.size();
        for (int i = 1; i <= k; i++)
            ptByColor[i].clear();
        for (int i = 1; i <= n; i++)
        {
            pts[i].x = ripe(mpx, pts[i].x), pts[i].y = ripe(mpy, pts[i].y);
            ptByColor[pts[i].c].push_back(pts[i]);
        }
        sort(pts + 1, pts + 1 + n), PST::init();
        for (int i = 1; i <= k; i++)
            processCategory(i);
        printf("%d\n", gans);
    }
    return 0;
}