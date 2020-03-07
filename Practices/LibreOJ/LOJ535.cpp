// LOJ535.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200;

struct frame
{
    int x, y, val;
};

int n, seq[MAX_N], pre_max[MAX_N], suf_min[MAX_N], nodes[MAX_N << 2], tag[MAX_N << 2], tree[MAX_N];
vector<frame> frames[MAX_N];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void pushdown(int p)
{
    if (tag[p])
    {
        nodes[lson] += tag[p], nodes[rson] += tag[p];
        tag[lson] += tag[p], tag[rson] += tag[p];
        tag[p] = 0;
    }
}

void pushup(int p) { nodes[p] = max(nodes[lson], nodes[rson]); }

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

#undef mid
#undef rson
#undef lson

// fenwick tree;

int lowbit(int x) { return x & (-x); }

void update(int x, int d)
{
    for (; x <= n; x += lowbit(x))
        tree[x] += d;
}

int query(int x, int ret = 0)
{
    for (; x; x -= lowbit(x))
        ret += tree[x];
    return ret;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i]), pre_max[i] = max(pre_max[i - 1], seq[i]);
    suf_min[n + 1] = n + 1;
    for (int i = n; i >= 1; i--)
        suf_min[i] = min(suf_min[i + 1], seq[i]);
    for (int i = 1; i <= n; i++)
    {
        int x = 0, y = n + 1, l = 1, r = i - 1;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            if (pre_max[mid] < seq[i])
                x = mid, l = mid + 1;
            else
                r = mid - 1;
        }
        l = i + 1, r = n;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            if (suf_min[mid] > seq[i])
                y = mid, r = mid - 1;
            else
                l = mid + 1;
        }
        if (x + 1 <= i - 1 && i + 1 <= y - 1)
            frames[x + 1].push_back(frame{i + 1, y - 1, 1}), frames[i].push_back(frame{i + 1, y - 1, -1});
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++)
    {
        for (auto x : frames[i])
            update(x.x, x.y, 1, n, 1, x.val);
        ans = max(ans, 1LL * nodes[1]);
    }
    ans = -2 * ans;
    for (int i = 1; i <= n; i++)
        ans += i - 1 - query(seq[i]), update(seq[i], 1);
    printf("%lld\n", ans);
    return 0;
}