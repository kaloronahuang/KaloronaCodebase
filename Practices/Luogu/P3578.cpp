// P3578.cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAX_N = 1e6 + 200, INF = 2e9;

typedef long long ll;

int n, stime_[MAX_N], ans[MAX_N], org_stime[MAX_N], nodes[MAX_N];
ll x1, y1, x2, y2;
vector<ll> mp;
vector<int> gpts;

struct point
{
    ll x, y, id;
    bool operator<(const point &rhs) const { return x < rhs.x || (x == rhs.x && y < rhs.y); }
} pts[MAX_N], tmp[MAX_N];

ll ripe(ll x) { return lower_bound(mp.begin(), mp.end(), x) - mp.begin() + 1; }

inline int lowbit(int x) { return x & (-x); }

void update(int x, int d)
{
    for (; x <= mp.size(); x += lowbit(x))
        nodes[x] += d;
}

int query(int x, int ret = 0)
{
    for (; x; x -= lowbit(x))
        ret += nodes[x];
    return ret;
}

void solve(int l, int r, int LB, int RB)
{
    if (l > r || LB > RB)
        return;
    if (l == r)
    {
        for (int i = LB; i <= RB; i++)
            ans[pts[i].id] = l;
        return;
    }
    int mid = (l + r) >> 1;
    sort(pts + LB, pts + RB + 1), gpts.clear();
    for (int i = LB; i <= RB; i++)
        org_stime[i] = stime_[pts[i].id];
    for (int i = LB; i <= RB; i++)
    {
        stime_[pts[i].id] -= query(pts[i].y);
        if (stime_[pts[i].id] <= 0 || pts[i].id <= mid)
            update(pts[i].y, 1), gpts.push_back(i);
    }
    int lptr = LB - 1, rptr = RB + 1;
    for (int i = LB; i <= RB; i++)
        if (stime_[pts[i].id] > 0 && pts[i].id > mid)
            tmp[--rptr] = pts[i];
        else
            tmp[++lptr] = pts[i], stime_[pts[i].id] = org_stime[i];
    for (int x : gpts)
        update(pts[x].y, -1);
    for (int i = LB; i <= RB; i++)
        pts[i] = tmp[i];
    solve(l, mid, LB, lptr), solve(mid + 1, r, rptr, RB);
}

int main()
{
    scanf("%d%lld%lld%lld%lld", &n, &x1, &y1, &x2, &y2);
    if (x1 * y2 - x2 * y1 == 0)
    {
        // on the same line, little rotation is needed;
        ll mx = max(abs(x1), abs(y1));
        mx = (mx + INF - 1) / mx;
        x1 *= mx, y1 *= y2;
    }
    if (1LL * x1 * y2 < 1LL * x2 * y1)
        swap(x1, x2), swap(y1, y2);
    for (int i = 1, x, y; i <= n; i++)
    {
        scanf("%d%d", &x, &y);
        // transform the coordination into vec1Ovec2;
        pts[i].x = 1LL * x * y2 - 1LL * y * x2;
        pts[i].y = 1LL * y * x1 - 1LL * x * y1;
        mp.push_back(pts[i].x), mp.push_back(pts[i].y), pts[i].id = i;
    }
    sort(mp.begin(), mp.end()), mp.erase(unique(mp.begin(), mp.end()), mp.end());
    for (int i = 1; i <= n; i++)
        pts[i].x = ripe(pts[i].x), pts[i].y = ripe(pts[i].y), scanf("%d", &stime_[i]);
    solve(1, n, 1, n);
    for (int i = 1; i <= n; i++)
        printf("%d ", ans[i]);
    return 0;
}