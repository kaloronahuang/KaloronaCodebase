// CF1261B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, ai[MAX_N], q, nodes[MAX_N << 2], ans[MAX_N];

struct query
{
    int len, pos, id;
    bool operator<(const query &rhs) const { return len < rhs.len; }
} queries[MAX_N];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void build(int l, int r, int p)
{
    if (l == r)
        return (void)(nodes[p] = 1);
    build(l, mid, lson), build(mid + 1, r, rson);
    nodes[p] = nodes[lson] + nodes[rson];
}

void update(int qx, int l, int r, int p, int val)
{
    if (l == r)
        return (void)(nodes[p] += val);
    if (qx <= mid)
        update(qx, l, mid, lson, val);
    else
        update(qx, mid + 1, r, rson, val);
    nodes[p] = nodes[lson] + nodes[rson];
}

int queryPos(int k, int l, int r, int p)
{
    if (l == r)
        return l;
    int lsiz = nodes[lson];
    if (k <= lsiz)
        return queryPos(k, l, mid, lson);
    else
        return queryPos(k - lsiz, mid + 1, r, rson);
}

#undef mid
#undef rson
#undef lson

struct tup
{
    int x, y;
    bool operator<(const tup &rhs) const { return x < rhs.x || (x == rhs.x && y > rhs.y); }
};

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    scanf("%d", &q);
    for (int i = 1; i <= q; i++)
        scanf("%d%d", &queries[i].len, &queries[i].pos), queries[i].id = i;
    sort(queries + 1, queries + 1 + q), reverse(queries + 1, queries + 1 + q);
    multiset<tup> ms;
    for (int i = 1; i <= n; i++)
        ms.insert(tup{ai[i], i});
    build(1, n, 1);
    for (int curt_len = n, qptr = 1; curt_len >= 1; curt_len--)
    {
        while (qptr <= q && queries[qptr].len == curt_len)
        {
            int pos = queryPos(queries[qptr].pos, 1, n, 1);
            ans[queries[qptr].id] = ai[pos], qptr++;
        }
        // prep for nxt round;
        tup del_element = *ms.begin();
        ms.erase(ms.begin());
        update(del_element.y, 1, n, 1, -1);
    }
    for (int i = 1; i <= q; i++)
        printf("%d\n", ans[i]);
    return 0;
}