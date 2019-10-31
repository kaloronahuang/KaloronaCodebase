// B.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e5 + 200;

int n, m, limit, ai[MAX_N], poses[MAX_N];
vector<int> vec;

struct node
{
    ll sum;
    int val;
} nodes[MAX_N << 2];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

node pushup(node ls, node rs)
{
    node curt;
    curt.sum = ls.sum + rs.sum;
    curt.val = ls.val + rs.val;
    return curt;
}

void update(int qx, int l, int r, int p, int val)
{
    if (l == r)
    {
        nodes[p].val += val, nodes[p].sum += val * vec[l - 1];
        return;
    }
    if (qx <= mid)
        update(qx, l, mid, lson, val);
    else
        update(qx, mid + 1, r, rson, val);
    nodes[p] = pushup(nodes[lson], nodes[rson]);
}

pair<int, int> queryRank(int k, int l, int r, int p)
{
    if (l == r)
        return make_pair(l, k);
    int lval = nodes[lson].val;
    if (k <= lval)
        return queryRank(k, l, mid, lson);
    else
        return queryRank(k - lval, mid + 1, r, rson);
}

node query(int ql, int qr, int l, int r, int p)
{
    if (ql > qr)
        return node{0, 0};
    if (ql <= l && r <= qr)
        return nodes[p];
    node curt;
    curt.val = curt.sum = 0;
    if (ql <= mid)
        curt = pushup(curt, query(ql, qr, l, mid, lson));
    if (mid < qr)
        curt = pushup(curt, query(ql, qr, mid + 1, r, rson));
    return curt;
}

#undef lson
#undef rson
#undef mid

int main()
{
    scanf("%d%d%d", &n, &m, &limit);
    ll gans = 0;
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), vec.push_back(ai[i]);
    sort(vec.begin(), vec.end()), vec.erase(unique(vec.begin(), vec.end()), vec.end());
    int upper = vec.size();
    for (int i = 1; i <= n; i++)
    {
        int pos = lower_bound(vec.begin(), vec.end(), ai[i]) - vec.begin() + 1;
        poses[i] = pos;
        update(pos, 1, upper, 1, 1);
        if (i > m)
            update(poses[i - m], 1, upper, 1, -1);
        if (i >= m)
        {
            pair<int, int> res = queryRank(limit, 1, upper, 1);
            node res1 = query(1, res.first - 1, 1, upper, 1);
            ll pans = res1.sum + 1LL * vec[res.first - 1] * res.second;
            gans += pans;
        }
    }
    printf("%lld", gans);
    return 0;
}