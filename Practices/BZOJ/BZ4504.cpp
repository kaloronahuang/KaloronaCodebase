// BZ4504.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4e5 + 200, LOG = 30, INF = 0x3f3f3f3f;

typedef long long ll;
typedef pair<ll, int> pli;

const ll INFL = 0x3f3f3f3f3f3f3f3f;

int n, kth, ai[MAX_N], pre[MAX_N], roots[MAX_N], ptot;
map<int, int> mp;

struct node
{
    pli val;
    int lson, rson;
    ll tag;
} nodes[MAX_N * LOG];

#define mid ((l + r) >> 1)

int build(int l, int r)
{
    int p = ++ptot;
    nodes[p].tag = 0, nodes[p].val = make_pair(0LL, l);
    if (l == r)
        return p;
    nodes[p].lson = build(l, mid), nodes[p].rson = build(mid + 1, r);
    return p;
}

int update(int ql, int qr, int l, int r, int pre, int val)
{
    if (ql > qr)
        return 0;
    int p = ++ptot;
    nodes[p] = nodes[pre];
    if (ql <= l && r <= qr)
        return nodes[p].tag += val, nodes[p].val.first += val, p;
    if (ql <= mid)
        nodes[p].lson = update(ql, qr, l, mid, nodes[pre].lson, val);
    if (mid < qr)
        nodes[p].rson = update(ql, qr, mid + 1, r, nodes[pre].rson, val);
    nodes[p].val = max(nodes[nodes[p].lson].val, nodes[nodes[p].rson].val);
    nodes[p].val.first += nodes[p].tag;
    return p;
}

pli query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return nodes[p].val;
    pli ret = make_pair(-INFL, -INF);
    if (ql <= mid)
        ret = max(ret, query(ql, qr, l, mid, nodes[p].lson));
    if (mid < qr)
        ret = max(ret, query(ql, qr, mid + 1, r, nodes[p].rson));
    return make_pair(ret.first + nodes[p].tag, ret.second);
}

struct element
{
    int o, l, r, t;
    ll sum;
    bool operator<(const element &rhs) const { return sum < rhs.sum; }
};

int main()
{
    scanf("%d%d", &n, &kth), nodes[0].val = make_pair(-INFL, -INF);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), pre[i] = mp[ai[i]], mp[ai[i]] = i;
    roots[0] = build(1, n);
    for (int i = 1; i <= n; i++)
        roots[i] = update(pre[i] + 1, i, 1, n, roots[i - 1], ai[i]);
    priority_queue<element> pq;
    for (int i = 1; i <= n; i++)
    {
        pli res = query(1, i, 1, n, roots[i]);
        pq.push(element{res.second, 1, i, i, res.first});
        // printf("%lld %d\n", res.first, res.second);
    }
    kth--;
    while (kth--)
    {
        element u = pq.top();
        pq.pop();
        if (u.l < u.o)
        {
            pli res = query(u.l, u.o - 1, 1, n, roots[u.t]);
            pq.push(element{res.second, u.l, u.o - 1, u.t, res.first});
        }
        if (u.o < u.r)
        {
            pli res = query(u.o + 1, u.r, 1, n, roots[u.t]);
            pq.push(element{res.second, u.o + 1, u.r, u.t, res.first});
        }
    }
    printf("%lld\n", pq.top().sum);
    return 0;
}