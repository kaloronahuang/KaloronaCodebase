// CF848C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;
typedef long long ll;

int n, q, ai[MAX_N], pre[MAX_N], nxt[MAX_N], qcnt;
ll nodes[MAX_N], ans[MAX_N];
set<int> tr[MAX_N];

struct tup
{
    int typ, x, y, val, id;
    bool operator<(const tup &rhs) const
    {
        if (typ != rhs.typ)
            return typ < rhs.typ;
        if (typ)
            return y < rhs.y;
        return x < rhs.x;
    }
} queries[MAX_N * 10];

inline int lowbit(int x) { return x & (-x); }

ll query(int x, ll ret = 0)
{
    for (; x; x -= lowbit(x))
        ret += nodes[x];
    return ret;
}

void update(int x, ll d)
{
    if (x == 0)
        return;
    for (; x <= n; x += lowbit(x))
        nodes[x] += d;
}

void modify(int u, int v)
{
    queries[++qcnt] = tup{0, u, pre[u], pre[u] - u, 0};
    pre[u] = v;
    queries[++qcnt] = tup{0, u, pre[u], u - pre[u], 0};
}

void solve(int l, int r)
{
    if (l == r)
        return;
    int mid = (l + r) >> 1, ptr = l - 1;
    solve(l, mid), solve(mid + 1, r);
    for (int i = mid + 1; i <= r; i++)
        if (queries[i].typ)
        {
            while (ptr < mid && (queries[ptr + 1].typ || queries[ptr + 1].x <= queries[i].y))
            {
                ptr++;
                if (queries[ptr].typ == 0)
                    update(queries[ptr].y, queries[ptr].val);
            }
            ans[queries[i].id] += query(n) - query(queries[i].x - 1);
        }
    for (int i = l; i <= ptr; i++)
        if (queries[i].typ == 0)
            update(queries[i].y, -queries[i].val);
    sort(queries + l, queries + r + 1);
}

int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), tr[ai[i]].insert(i);
    for (int i = 1; i <= n; i++)
        tr[i].insert(0), tr[i].insert(n + 1);
    // calc the pre;
    for (int i = 1; i <= n; i++)
        pre[i] = *(--tr[ai[i]].lower_bound(i)), nxt[i] = *(tr[ai[i]].upper_bound(i));
    for (int i = 1; i <= n; i++)
        queries[++qcnt] = tup{0, i, pre[i], i - pre[i], 0};
    int caseTot = 0;
    while (q--)
    {
        int opt, x, y;
        scanf("%d%d%d", &opt, &x, &y);
        if (opt == 1)
        {
            // a[x] -> y;
            if (ai[x] == y)
                continue;
            int n_pre = *(--tr[y].lower_bound(x)), n_nxt = *(tr[y].upper_bound(x));
            tr[ai[x]].erase(x), tr[y].insert(x), ai[x] = y;
            // update;
            if (nxt[x] != n + 1)
                modify(nxt[x], pre[x]);
            if (pre[x] != 0)
                nxt[pre[x]] = nxt[x];
            if (n_pre != 0)
                nxt[n_pre] = x;
            if (n_nxt != n + 1)
                modify(n_nxt, x);
            modify(x, n_pre), nxt[x] = n_nxt;
        }
        else
            // query on [x, y];
            queries[++qcnt] = tup{1, x, y, 0, ++caseTot};
    }
    solve(1, qcnt);
    for (int i = 1; i <= caseTot; i++)
        printf("%lld\n", ans[i]);
    return 0;
}