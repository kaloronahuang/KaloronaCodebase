// ScanningLine.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4e5 + 200;

int n, ptot, nodes[MAX_N << 2], tag[MAX_N << 2], min_val[MAX_N << 2], upper;
vector<int> mp;

struct frame
{
    int x, l, r, opt;
    bool operator<(const frame &rhs) const { return x < rhs.x; }
};
vector<frame> frames;

int ripe(int x) { return lower_bound(mp.begin(), mp.end(), x) - mp.begin() + 1; }

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void pushup(int p)
{
    min_val[p] = min(min_val[lson], min_val[rson]);
    nodes[p] = nodes[lson] * (min_val[p] == min_val[lson]) + nodes[rson] * (min_val[p] == min_val[rson]);
}

void pushdown(int p)
{
    if (tag[p])
    {
        min_val[lson] += tag[p], min_val[rson] += tag[p];
        tag[lson] += tag[p], tag[rson] += tag[p];
        tag[p] = 0;
    }
}

void build(int l, int r, int p)
{
    if (l == r)
        return (void)(nodes[p] = mp[l - 1] - ((l - 2 >= 0) ? mp[l - 2] : 0));
    build(l, mid, lson), build(mid + 1, r, rson);
    pushup(p);
}

void update(int ql, int qr, int l, int r, int p, int val)
{
    if (ql > qr)
        return;
    if (ql <= l && r <= qr)
        return (void)(min_val[p] += val, tag[p] += val);
    pushdown(p);
    if (ql <= mid)
        update(ql, qr, l, mid, lson, val);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, val);
    pushup(p);
}

int main()
{
    scanf("%d", &n);
    vector<int> fid;
    for (int i = 1; i <= n; i++)
    {
        int l1, r1, l2, r2;
        scanf("%d%d%d%d", &l1, &l2, &r1, &r2);
        frames.push_back(frame{l1, l2, r2, 1});
        frames.push_back(frame{r1, l2, r2, -1});
        mp.push_back(l2), mp.push_back(r2), fid.push_back(l1), fid.push_back(r1);
    }
    sort(frames.begin(), frames.end());
    sort(mp.begin(), mp.end()), mp.erase(unique(mp.begin(), mp.end()), mp.end());
    sort(fid.begin(), fid.end()), fid.erase(unique(fid.begin(), fid.end()), fid.end());
    upper = mp.size(), build(1, upper, 1);
    int last = fid[0], ptr = 0, siz = frames.size();
    long long ans = 0;
    for (int curt : fid)
    {
        ans += 1LL * (curt - last) * (mp.back() - nodes[1]), last = curt;
        while (ptr < siz && frames[ptr].x == curt)
            update(ripe(frames[ptr].l) + 1, ripe(frames[ptr].r), 1, upper, 1, frames[ptr].opt), ptr++;
    }
    printf("%lld\n", ans);
    return 0;
}