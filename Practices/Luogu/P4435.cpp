// P4435.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

typedef pair<int, int> pii;
typedef long long ll;

int n, ai[MAX_N], q;

struct node
{
    vector<pii> pre, suf;
    ll sum;
    node() { pre.clear(), suf.clear(), sum = 0; }
} nodes[MAX_N << 2];

int gcd(int a, int b) { return __gcd(a, b); }

vector<pii> merge(vector<pii> &lft, vector<pii> &rig, bool mode)
{
    if (lft.empty())
        return rig;
    if (rig.empty())
        return lft;
    if (mode)
        reverse(lft.begin(), lft.end()), reverse(rig.begin(), rig.end());
    vector<pii> ret;
    ret.clear();
    int lsiz = lft.size(), rsiz = rig.size();
    pii tmp;
    for (int i = 0; i < lsiz; i++)
        tmp = lft[i], ret.push_back(tmp);
    for (int i = 0; i < rsiz; i++)
    {
        int d = gcd(lft[lsiz - 1].first, rig[i].first);
        if (d == tmp.first)
            tmp.second = rig[i].second, ret[ret.size() - 1].second = tmp.second + lft[lsiz - 1].second;
        else
            tmp.first = d, tmp.second = rig[i].second, ret.push_back(make_pair(tmp.first, tmp.second + lft[lsiz - 1].second));
    }
    if (mode)
        reverse(ret.begin(), ret.end());
    return ret;
}

node merge(node &lft, node &rig)
{
    node ret;
    ret.sum = lft.sum + rig.sum;
    // merge the middle;
    ret.pre = merge(lft.pre, rig.pre, false), ret.suf = merge(rig.suf, lft.suf, true);
    if (lft.suf.empty() || rig.pre.empty())
        return ret;
    for (int i = 0, siz = lft.suf.size(), j = 0, siz_ = rig.pre.size(); i < siz; i++)
    {
        while (j < siz_ && gcd(lft.suf[i].first, rig.pre[j].first) > 1)
            j++;
        int len = lft.suf[i].second;
        if (i < siz - 1)
            len -= lft.suf[i + 1].second;
        if (j > 0)
            ret.sum += 1LL * len * rig.pre[j - 1].second;
    }
    return ret;
}

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

// segment tree;

void pushup(int p) { nodes[p] = merge(nodes[lson], nodes[rson]); }

void build(int l, int r, int p)
{
    if (l == r)
    {
        nodes[p].pre.clear(), nodes[p].suf.clear();
        nodes[p].sum = ai[l] > 1;
        nodes[p].pre.push_back(make_pair(ai[l], 1)), nodes[p].suf.push_back(make_pair(ai[l], 1));
        return;
    }
    build(l, mid, lson), build(mid + 1, r, rson);
    pushup(p);
}

void update(int qx, int l, int r, int p)
{
    if (l == r)
    {
        nodes[p].pre.clear(), nodes[p].suf.clear();
        nodes[p].sum = ai[l] > 1;
        nodes[p].pre.push_back(make_pair(ai[l], 1)), nodes[p].suf.push_back(make_pair(ai[l], 1));
        return;
    }
    if (qx <= mid)
        update(qx, l, mid, lson);
    else
        update(qx, mid + 1, r, rson);
    pushup(p);
}

node query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return nodes[p];
    node ret;
    if (ql <= mid && mid < qr)
    {
        node ls = query(ql, qr, l, mid, lson), rs = query(ql, qr, mid + 1, r, rson);
        ret = merge(ls, rs);
        return ret;
    }
    if (ql <= mid)
        ret = query(ql, qr, l, mid, lson);
    else if (mid < qr)
        ret = query(ql, qr, mid + 1, r, rson);
    return ret;
}

#undef mid
#undef rson
#undef lson

int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    build(1, n, 1);
    while (q--)
    {
        int opt, x, y;
        scanf("%d%d%d", &opt, &x, &y);
        if (opt == 1)
            ai[x] = y, update(x, 1, n, 1);
        else
            printf("%lld\n", query(x, y, 1, n, 1).sum);
    }
    return 0;
}