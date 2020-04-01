// BZ1176.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e6 + 200;

int n, q, init_val, ans[MAX_N], tree[MAX_N], qtot;

struct node
{
    int typ, x1, y1, y2, val, id;
} nodes[MAX_N], tmp[MAX_N];

inline int lowbit(int x) { return x & (-x); }

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

void solve(int l, int r)
{
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    solve(l, mid), solve(mid + 1, r);
    int lptr = mid, rptr = mid + 1;

    for (int i = r; i >= mid + 1; i--)
    {
        while (lptr >= l && nodes[lptr].x1 >= nodes[i].x1)
        {
            if (nodes[lptr].typ == 1)
                update(nodes[lptr].y1, nodes[lptr].val);
            lptr--;
        }
        if (nodes[i].typ == 2)
            ans[nodes[i].id] += nodes[i].val * (query(nodes[i].y2) - query(nodes[i].y1 - 1));
    }

    lptr = mid;
    for (int i = r; i >= mid + 1; i--)
        while (lptr >= l && nodes[lptr].x1 >= nodes[i].x1)
        {
            if (nodes[lptr].typ == 1)
                update(nodes[lptr].y1, -nodes[lptr].val);
            lptr--;
        }

    lptr = l, rptr = mid + 1;
    int cur = l;
    while (lptr <= mid && rptr <= r)
        if (nodes[lptr].x1 < nodes[rptr].x1)
            tmp[cur++] = nodes[lptr++];
        else
            tmp[cur++] = nodes[rptr++];
    while (lptr <= mid)
        tmp[cur++] = nodes[lptr++];
    while (rptr <= r)
        tmp[cur++] = nodes[rptr++];
    for (int i = l; i <= r; i++)
        nodes[i] = tmp[i];
}

int main()
{
    scanf("%d%d", &init_val, &n);
    int opt, xa, ya, xb, yb, val;
    do
    {
        scanf("%d", &opt);
        if (opt == 1)
        {
            scanf("%d%d%d", &xa, &yb, &val);
            nodes[++q] = node{1, xa, yb, yb, val, 0};
        }
        else if (opt == 2)
        {
            scanf("%d%d%d%d", &xa, &ya, &xb, &yb);
            nodes[++q] = node{2, min(xa, xb), min(ya, yb), max(ya, yb), 1, ++qtot};
            nodes[++q] = node{2, max(xa, xb) + 1, min(ya, yb), max(ya, yb), -1, qtot};
        }
    } while (opt != 3);
    solve(1, q);
    for (int i = 1; i <= qtot; i++)
        printf("%d\n", init_val + ans[i]);
    return 0;
}