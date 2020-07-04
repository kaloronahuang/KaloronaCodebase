// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4e5 + 200;

typedef pair<int, int> pii;

int n, q, ai[MAX_N], pre[MAX_N], diff[MAX_N], ansBox[MAX_N];
vector<pii> buc[MAX_N];

struct queryInfo
{
    int l, r, id;
    bool operator<(const queryInfo &rhs) const { return r < rhs.r; }
} queries[MAX_N];

namespace PST
{

    struct node
    {
        int lson, rson, val;
    } nodes[MAX_N * 50];

    int ptot, roots[MAX_N];

#define mid ((l + r) >> 1)

    int update(int qx, int l, int r, int pre, int val)
    {
        int p = ++ptot;
        nodes[p] = nodes[pre], nodes[p].val += val;
        if (l == r)
            return p;
        if (qx <= mid)
            nodes[p].lson = update(qx, l, mid, nodes[pre].lson, val);
        else
            nodes[p].rson = update(qx, mid + 1, r, nodes[p].rson, val);
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

#undef mid

} // namespace PST

namespace BIT
{

    int nodes[MAX_N];

    inline int lowbit(int x) { return x & (-x); }

    void update(int x, int d)
    {
        for (; x <= n; x += lowbit(x))
            nodes[x] += d;
    }

    int query(int x, int ret = 0)
    {
        for (; x; x -= lowbit(x))
            ret += nodes[x];
        return ret;
    }

} // namespace BIT

struct frame
{
    int x, l, r, delta;
    bool operator<(const frame &rhs) const { return x < rhs.x; }
};
vector<frame> fr;

int main()
{
    /*
    freopen("sample3.in", "r", stdin);
    freopen("sample3.out", "w", stdout);
    */
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &ai[i]), PST::roots[i] = PST::roots[i - 1];
        if (pre[ai[i]] != 0)
            PST::roots[i] = PST::update(pre[ai[i]], 1, n, PST::roots[i], -1);
        diff[i] = i - pre[ai[i]], pre[ai[i]] = i, buc[ai[i]].push_back(make_pair(diff[i], i));
        PST::roots[i] = PST::update(pre[ai[i]], 1, n, PST::roots[i], 1);
    }
    scanf("%d", &q);
    for (int i = 1; i <= q; i++)
        scanf("%d%d", &queries[i].l, &queries[i].r), queries[i].id = i;
    for (int x = 1; x < MAX_N; x++)
        if (!buc[x].empty())
        {
            for (int i = 0, j, siz = buc[x].size(); i < siz; i = j + 1)
            {
                j = i;
                while (j + 1 < siz && buc[x][j + 1].first == buc[x][i].first)
                    j++;
                if (i > 0)
                {
                    // the previous;
                    int lbound, rbound;
                    lbound = (i > 1) ? buc[x][i - 2].second + 1 : 1;
                    rbound = (i + 1 < siz) ? buc[x][i + 1].second - 1 : n;
                    fr.push_back(frame{buc[x][i].second, lbound, buc[x][i].second, 1});
                    fr.push_back(frame{rbound + 1, lbound, buc[x][i].second, -1});
                }
                for (int p = i; p < j; p++)
                {
                    fr.push_back(frame{buc[x][p + 1].second, (i > 0) ? buc[x][i - 1].second + 1 : 1, buc[x][p].second, 1});
                    fr.push_back(frame{p + 2 < siz ? buc[x][p + 2].second : n + 1, (i > 0) ? buc[x][i - 1].second + 1 : 1, buc[x][p].second, -1});
                }
                if (j < siz - 1)
                {
                    // the previous;
                    int lbound, rbound;
                    lbound = (j > 0) ? buc[x][j - 1].second + 1 : 1;
                    rbound = (j + 2 < siz) ? buc[x][j + 2].second - 1 : n;
                    fr.push_back(frame{buc[x][j + 1].second, lbound, buc[x][j].second, 1});
                    fr.push_back(frame{rbound + 1, lbound, buc[x][j].second, -1});
                }
            }
        }
    for (int x = 1; x < MAX_N; x++)
        if (!buc[x].empty())
            for (int i = 0, j, siz = buc[x].size(); i < siz; i++)
            {
                fr.push_back(frame{buc[x][i].second, i > 0 ? buc[x][i - 1].second + 1 : 1, buc[x][i].second, 1});
                fr.push_back(frame{i + 1 < siz ? buc[x][i + 1].second : n + 1, i > 0 ? buc[x][i - 1].second + 1 : 1, buc[x][i].second, -1});
            }
    sort(fr.begin(), fr.end()), sort(queries + 1, queries + 1 + q);
    int fptr = 0;
    for (int i = 1, siz = fr.size(); i <= q; i++)
    {
        while (fptr < siz && fr[fptr].x <= queries[i].r)
            BIT::update(fr[fptr].l, fr[fptr].delta), BIT::update(fr[fptr].r + 1, -fr[fptr].delta), fptr++;
        ansBox[queries[i].id] = -(BIT::query(queries[i].l) > 0);
    }
    for (int i = 1; i <= q; i++)
    {
        int res = PST::query(queries[i].l, n, 1, n, PST::roots[queries[i].r]);
        ansBox[queries[i].id] += 1 + res;
    }
    for (int i = 1; i <= q; i++)
        printf("%d\n", ansBox[i]);
    return 0;
}