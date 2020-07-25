// P5161.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

typedef long long ll;

int n, ai[MAX_N], siz[MAX_N], roots[MAX_N];
vector<int> pos[MAX_N];

namespace SGT
{

    int ptot;

    struct node
    {
        int sum, lson, rson;
        ll psum;
    } nodes[MAX_N * 30];

#define mid ((l + r) >> 1)

    int update(int qx, int l, int r, int p)
    {
        if (p == 0)
            p = ++ptot;
        nodes[p].sum++, nodes[p].psum += qx;
        if (l == r)
            return p;
        if (qx <= mid)
            nodes[p].lson = update(qx, l, mid, nodes[p].lson);
        else
            nodes[p].rson = update(qx, mid + 1, r, nodes[p].rson);
        return p;
    }

    int query(int ql, int qr, int l, int r, int p)
    {
        if (ql > qr || p == 0)
            return 0;
        if (ql <= l && r <= qr)
            return nodes[p].sum;
        int ret = 0;
        if (ql <= mid)
            ret += query(ql, qr, l, mid, nodes[p].lson);
        if (mid < qr)
            ret += query(ql, qr, mid + 1, r, nodes[p].rson);
        return ret;
    }

    ll querySum(int ql, int qr, int l, int r, int p)
    {
        if (ql > qr || p == 0)
            return 0;
        if (ql <= l && r <= qr)
            return nodes[p].psum;
        ll ret = 0;
        if (ql <= mid)
            ret += querySum(ql, qr, l, mid, nodes[p].lson);
        if (mid < qr)
            ret += querySum(ql, qr, mid + 1, r, nodes[p].rson);
        return ret;
    }

    int merge(int x, int y)
    {
        if (x == 0 || y == 0)
            return x + y;
        nodes[x].sum += nodes[y].sum;
        nodes[x].psum += nodes[y].psum;
        nodes[x].lson = merge(nodes[x].lson, nodes[y].lson);
        nodes[x].rson = merge(nodes[x].rson, nodes[y].rson);
        return x;
    }

} // namespace SGT

struct node
{
    map<int, int> ch;
    int dep, link;
} nodes[MAX_N];

int ptot = 1, last_ptr = 1, bucket[MAX_N], rnk[MAX_N];

void insert(int c)
{
    int pre = last_ptr, p = last_ptr = ++ptot;
    nodes[p].dep = nodes[pre].dep + 1;
    while (pre && nodes[pre].ch[c] == 0)
        nodes[pre].ch[c] = p, pre = nodes[pre].link;
    if (pre == 0)
        nodes[p].link = 1;
    else
    {
        int q = nodes[pre].ch[c];
        if (nodes[q].dep == nodes[pre].dep + 1)
            nodes[p].link = q;
        else
        {
            int clone = ++ptot;
            nodes[clone] = nodes[q], nodes[clone].dep = nodes[pre].dep + 1;
            nodes[p].link = nodes[q].link = clone;
            while (pre && nodes[pre].ch[c] == q)
                nodes[pre].ch[c] = clone, pre = nodes[pre].link;
        }
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    for (int i = 1; i <= n - 1; i++)
    {
        insert(ai[i + 1] - ai[i]), siz[last_ptr]++, pos[last_ptr].push_back(i);
        roots[last_ptr] = SGT::update(i, 1, n - 1, roots[last_ptr]);
    }
    for (int i = 1; i <= ptot; i++)
        bucket[nodes[i].dep]++;
    for (int i = 1; i <= ptot; i++)
        bucket[i] += bucket[i - 1];
    for (int i = 1; i <= ptot; i++)
        rnk[bucket[nodes[i].dep]--] = i;
    for (int i = ptot; i >= 2; i--)
        siz[nodes[rnk[i]].link] += siz[rnk[i]];
    long long ans = 0;
    for (int i = ptot; i >= 1; i--)
    {
        int u = rnk[i], fa = nodes[u].link;
        if (pos[u].size() > pos[fa].size())
            swap(pos[u], pos[fa]), swap(roots[u], roots[fa]);
        for (int x : pos[u])
        {
            ans += 1LL * nodes[fa].dep * SGT::query(x + 1 + nodes[fa].dep, n - 1, 1, n - 1, roots[fa]);
            ans += 1LL * nodes[fa].dep * SGT::query(1, x - nodes[fa].dep - 1, 1, n - 1, roots[fa]);
            ll sum0 = SGT::query(x + 1, x + nodes[fa].dep, 1, n - 1, roots[fa]);
            ll sum1 = SGT::querySum(x + 1, x + nodes[fa].dep, 1, n - 1, roots[fa]);
            ans += sum1 - 1LL * sum0 * (x + 1);

            sum0 = SGT::query(x - nodes[fa].dep, x - 1, 1, n - 1, roots[fa]);
            sum1 = SGT::querySum(x - nodes[fa].dep, x - 1, 1, n - 1, roots[fa]);
            ans += 1LL * sum0 * (x - 1) - sum1;

            pos[fa].push_back(x);
        }
        roots[fa] = SGT::merge(roots[fa], roots[u]);
    }
    ans += 1LL * n * (n - 1) / 2;
    printf("%lld\n", ans);
    return 0;
}