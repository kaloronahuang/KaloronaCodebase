// CF765F.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4e5 + 200, INF = 0x3f3f3f3f;

int n, ai[MAX_N], m, prod[MAX_N << 2], ansBox[MAX_N];
vector<int> nodes[MAX_N << 2];

struct queryInfo
{
    int l, r, id;
    bool operator<(const queryInfo &rhs) { return r < rhs.r; }
} queries[MAX_N];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void build(int l, int r, int p)
{
    for (int i = l; i <= r; i++)
        nodes[p].push_back(ai[i]);
    sort(nodes[p].begin(), nodes[p].end());
    prod[p] = INF;
    if (l == r)
        return;
    build(l, mid, lson), build(mid + 1, r, rson);
}

int query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return prod[p];
    int ret = 0x7fffffff;
    if (ql <= mid)
        ret = min(ret, query(ql, qr, l, mid, lson));
    if (mid < qr)
        ret = min(ret, query(ql, qr, mid + 1, r, rson));
    return ret;
}

int gret;

void update(int qx, int l, int r, int p, int val)
{
    if (r <= qx)
    {
        vector<int>::iterator it = upper_bound(nodes[p].begin(), nodes[p].end(), val);
        if (it != nodes[p].end())
            prod[p] = min(prod[p], abs(val - *it));
        if (it != nodes[p].begin())
            prod[p] = min(prod[p], abs(val - *(--it)));
        if (gret <= prod[p])
            return;
        if (l == r)
            return (void)(gret = min(gret, prod[p]));
    }
    if (qx > mid)
        update(qx, mid + 1, r, rson, val);
    update(qx, l, mid, lson, val);
    prod[p] = min(prod[p], min(prod[lson], prod[rson]));
    gret = min(gret, prod[p]);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    scanf("%d", &m), build(1, n, 1);
    for (int i = 1; i <= m; i++)
        scanf("%d%d", &queries[i].l, &queries[i].r), queries[i].id = i;
    sort(queries + 1, queries + 1 + m);
    for (int i = 2, qptr = 1; i <= n; i++)
    {
        gret = INF, update(i - 1, 1, n, 1, ai[i]);
        while (qptr <= m && queries[qptr].r <= i)
            ansBox[queries[qptr].id] = query(queries[qptr].l, i, 1, n, 1), qptr++;
    }
    for (int i = 1; i <= m; i++)
        printf("%d\n", ansBox[i]);
    return 0;
}