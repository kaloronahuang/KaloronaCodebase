// card.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4e5 + 200;

int n, k, ai[MAX_N], bi[MAX_N], ki[MAX_N], nodes[MAX_N << 2], upper, timeStamp[MAX_N], ntot, ansBox[MAX_N];
vector<int> mp;

int ripe(int x) { return lower_bound(mp.begin(), mp.end(), x) - mp.begin() + 1; }

inline char nc()
{
    static char buf[100000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
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

struct node
{
    int id, xtime, ytime;
    bool operator<(const node &rhs) const { return xtime > rhs.xtime || (xtime == rhs.xtime && id < rhs.id); }
} pts[MAX_N];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void update(int qx, int l, int r, int p, int val)
{
    if (l == r)
        return (void)(nodes[p] = max(nodes[p], val));
    if (qx <= mid)
        update(qx, l, mid, lson, val);
    else
        update(qx, mid + 1, r, rson, val);
    nodes[p] = max(nodes[lson], nodes[rson]);
}

int query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return nodes[p];
    int ret = 0;
    if (ql <= mid)
        ret = max(ret, query(ql, qr, l, mid, lson));
    if (mid < qr)
        ret = max(ret, query(ql, qr, mid + 1, r, rson));
    return ret;
}

#undef mid
#undef rson
#undef lson

// fenwick tree;

int fnodes[MAX_N];

inline int lowbit(int x) { return x & (-x); }

void update(int x, int d)
{
    for (; x <= upper; x += lowbit(x))
        fnodes[x] += d;
}

int query(int x, int ret = 0)
{
    for (; x; x -= lowbit(x))
        ret += fnodes[x];
    return ret;
}

int main()
{
    n = read(), k = read();
    for (int i = 1; i <= n; i++)
        ai[i] = read(), mp.push_back(ai[i]), bi[i] = read(), mp.push_back(bi[i]);
    for (int i = 1; i <= k; i++)
        ki[i] = read(), mp.push_back(ki[i]);
    sort(mp.begin(), mp.end()), mp.erase(unique(mp.begin(), mp.end()), mp.end());
    upper = mp.size();
    for (int i = 1; i <= n; i++)
        ai[i] = ripe(ai[i]), bi[i] = ripe(bi[i]);
    for (int i = 1; i <= k; i++)
        ki[i] = ripe(ki[i]), update(ki[i], 1, upper, 1, i);
    for (int i = 1; i <= n; i++)
    {
        int lft = min(ai[i], bi[i]), rig = max(ai[i], bi[i]) - 1;
        if (lft <= rig)
            timeStamp[i] = query(lft, rig, 1, upper, 1);
    }
    for (int i = 1; i <= n; i++)
        pts[++ntot] = node{i, timeStamp[i], max(ai[i], bi[i])};
    for (int i = 1; i <= k; i++)
        pts[++ntot] = node{0, i, ki[i]};
    sort(pts + 1, pts + 1 + ntot);
    for (int i = 1; i <= ntot; i++)
        if (pts[i].id == 0)
            update(pts[i].ytime, 1);
        else
            ansBox[pts[i].id] = query(upper) - query(pts[i].ytime - 1);
    long long ans = 0;
    for (int i = 1; i <= n; i++)
    {
        int situation[2] = {ai[i], bi[i]};
        if (timeStamp[i] != 0)
            situation[0] = max(ai[i], bi[i]), situation[1] = min(ai[i], bi[i]);
        if (ansBox[i] & 1)
            swap(situation[0], situation[1]);
        ans += mp[situation[0] - 1];
    }
    printf("%lld\n", ans);
    return 0;
}