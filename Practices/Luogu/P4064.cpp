// P4064.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 200100;

int n, m, k, delta, T, seq[MAX_N], req[MAX_N], tree[MAX_N];

struct segment
{
    int l, r;
    bool operator<(const segment &seg) const { return r < seg.r || (r == seg.r && l < seg.l); }
} segs[MAX_N];

bool compare(segment &a, segment &b) { return a.l < b.l || (a.l == b.l && a.r < b.r); }

inline int lowbit(int x) { return x & (-x); }

int query(int x, int ans = 0)
{
    for (; x; x -= lowbit(x))
        ans += tree[x];
    return ans;
}

void update(int x, int d)
{
    for (; x <= n; x += lowbit(x))
        tree[x] += d;
}

bool check(int mid)
{
    memset(tree, 0, sizeof(tree));
    priority_queue<segment> pq;
    for (int i = 1; i <= n; i++)
        update(i, seq[i]), update(i + 1, -seq[i]);
    int inc_val = 0;
    for (int i = 1, cur = 1; i <= n; i++)
    {
        while (cur <= m && segs[cur].l <= i)
            pq.push(segs[cur++]);
        while (query(i) < mid)
        {
            if (pq.empty())
                return false;
            segment s = pq.top();
            pq.pop();
            if (s.r < i)
                return false;
            update(s.l, delta), update(s.r + 1, -delta), inc_val++;
            if (inc_val > k)
                return false;
        }
    }
    return true;
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%d%d", &n, &m, &k, &delta);
        for (int i = 1; i <= n; i++)
            scanf("%d", &seq[i]);
        for (int i = 1; i <= m; i++)
            scanf("%d%d", &segs[i].l, &segs[i].r);
        sort(segs + 1, segs + 1 + m, compare);
        int l = 1e8 + 200, r = 1e8 + 200, ans = 0;
        for (int i = 1; i <= n; i++)
            l = min(l, seq[i]);
        r = l + delta * k;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            if (check(mid))
                l = mid + 1, ans = mid;
            else
                r = mid - 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}