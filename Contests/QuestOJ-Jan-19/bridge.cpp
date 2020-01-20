// bridge.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4e5 + 200;

struct query
{
    int l, r, id;
    bool operator<(const query &rhs) const { return r < rhs.r || (r == rhs.r && l < rhs.l); }
} queries[MAX_N];

struct node
{
    vector<int> vec;
    int min_id;
} nodes[MAX_N << 2];

int n, ai[MAX_N], q, ansBox[MAX_N];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void build(int l, int r, int p)
{
    for (int i = l; i <= r; i++)
        nodes[p].vec.push_back(ai[i]);
    sort(nodes[p].vec.begin(), nodes[p].vec.end());
    nodes[p].min_id = 0x3f3f3f3f;
    if (l == r)
        return;
    build(l, mid, lson), build(mid + 1, r, rson);
}

int global_ans;

void update(int qx, int l, int r, int p, int val)
{
    if (r <= qx)
    {
        vector<int>::iterator it = upper_bound(nodes[p].vec.begin(), nodes[p].vec.end(), val);
        if (it != nodes[p].vec.end())
            nodes[p].min_id = min(nodes[p].min_id, abs(val - *it));
        if (it != nodes[p].vec.begin())
            nodes[p].min_id = min(nodes[p].min_id, abs(val - *(it - 1)));
        if (global_ans <= nodes[p].min_id)
            return;
        if (l == r)
            return (void)(global_ans = min(global_ans, nodes[p].min_id));
    }
    if (qx > mid)
        update(qx, mid + 1, r, rson, val);
    update(qx, l, mid, lson, val);
    nodes[p].min_id = min(nodes[p].min_id, min(nodes[lson].min_id, nodes[rson].min_id));
    global_ans = min(global_ans, nodes[p].min_id);
}

int query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return nodes[p].min_id;
    int ret = 0x3f3f3f3f;
    if (ql <= mid)
        ret = min(ret, query(ql, qr, l, mid, lson));
    if (mid < qr)
        ret = min(ret, query(ql, qr, mid + 1, r, rson));
    return ret;
}

#undef mid
#undef rson
#undef lson

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    build(1, n, 1), scanf("%d", &q);
    for (int i = 1; i <= q; i++)
        scanf("%d%d", &queries[i].l, &queries[i].r), queries[i].id = i;
    sort(queries + 1, queries + 1 + q);
    for (int query_ptr = 1, right_point = 2; right_point <= n; right_point++)
    {
        global_ans = 0x3f3f3f3f;
        update(right_point - 1, 1, n, 1, ai[right_point]);
        while (query_ptr <= q && queries[query_ptr].r <= right_point)
            ansBox[queries[query_ptr].id] = query(queries[query_ptr].l, queries[query_ptr].r, 1, n, 1), query_ptr++;
    }
    for (int i = 1; i <= q; i++)
        printf("%d\n", ansBox[i]);
    return 0;
}