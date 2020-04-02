// P3759.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 50500, mod = 1e9 + 7;

typedef pair<int, int> pii;

int n, q, ptot, roots[MAX_N], pos[MAX_N], pages[MAX_N];

struct node
{
    int lson, rson;
    pii sum;
} nodes[MAX_N * 200];

pii merge(pii a, pii b) { return make_pair((0LL + a.first + b.first) % mod, (0LL + a.second + b.second) % mod); }

inline int lowbit(int x) { return x & (-x); }

#define mid ((l + r) >> 1)

int update(int qx, int l, int r, int p, pii val)
{
    if (p == 0)
        p = ++ptot;
    nodes[p].sum = merge(nodes[p].sum, val);
    if (l == r)
        return p;
    if (qx <= mid)
        nodes[p].lson = update(qx, l, mid, nodes[p].lson, val);
    else
        nodes[p].rson = update(qx, mid + 1, r, nodes[p].rson, val);
    return p;
}

void update(int x, int y, pii val)
{
    for (; x <= n; x += lowbit(x))
        roots[x] = update(y, 1, n, roots[x], val);
}

pii query(int ql, int qr, int l, int r, int p)
{
    if (p == 0)
        return make_pair(0, 0);
    if (ql <= l && r <= qr)
        return nodes[p].sum;
    pii ret = make_pair(0, 0);
    if (ql <= mid)
        ret = merge(ret, query(ql, qr, l, mid, nodes[p].lson));
    if (mid < qr)
        ret = merge(ret, query(ql, qr, mid + 1, r, nodes[p].rson));
    return ret;
}

pii query(int xl, int xr, int yl, int yr)
{
    if (xl > xr)
        return make_pair(0, 0);
    pii rig = make_pair(0, 0), lft = make_pair(0, 0);
    for (int x = xr; x; x -= lowbit(x))
        rig = merge(rig, query(yl, yr, 1, n, roots[x]));
    for (int x = xl - 1; x; x -= lowbit(x))
        lft = merge(lft, query(yl, yr, 1, n, roots[x]));
    return make_pair((0LL + rig.first + mod - lft.first) % mod, (0LL + rig.second + mod - lft.second) % mod);
}

int main()
{
    scanf("%d%d", &n, &q);
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &pos[i], &pages[i]);
        update(i, pos[i], make_pair(pages[i], 1));
        pii res = query(1, i - 1, pos[i] + 1, n);
        ans = (0LL + ans + res.first + 1LL * res.second * pages[i] % mod) % mod;
    }
    while (q--)
    {
        int x, y, a, b;
        scanf("%d%d", &x, &y);
        if (x > y)
            swap(x, y);
        a = pos[x], b = pos[y];
        pii ret1 = query(x + 1, y - 1, a + 1, n), ret2 = query(x + 1, y - 1, 1, a - 1);
        ret1.first = (0LL + ret1.first + mod - ret2.first) % mod;
        ret1.second = (0LL + ret1.second + mod - ret2.second) % mod;
        ans = (0LL + ans + ret1.first + 1LL * ret1.second * pages[x] % mod) % mod;

        ret1 = query(x + 1, y - 1, 1, b - 1), ret2 = query(x + 1, y - 1, b + 1, n);
        ret1.first = (0LL + ret1.first + mod - ret2.first) % mod;
        ret1.second = (0LL + ret1.second + mod - ret2.second) % mod;
        ans = (0LL + ans + ret1.first + 1LL * ret1.second * pages[y] % mod) % mod;

        if (a < b)
            ans = (0LL + ans + pages[x] + pages[y]) % mod;
        else if (a > b)
            ans = (0LL + ans + mod - (0LL + pages[x] + pages[y]) % mod) % mod;
        update(x, pos[x], make_pair(mod - pages[x], mod - 1)), update(y, pos[y], make_pair(mod - pages[y], mod - 1));
        swap(pos[x], pos[y]), swap(pages[x], pages[y]);
        update(x, pos[x], make_pair(pages[x], 1)), update(y, pos[y], make_pair(pages[y], 1));
        printf("%d\n", ans);
    }
    return 0;
}