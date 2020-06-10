// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200, INF = 1e9;

int n, m, ptot;
char cmdlet[10];

struct node
{
    int lson, rson, tag;
} nodes[MAX_N * 120];

#define mid ((l + r) >> 1)

int update(int ql, int qr, int l, int r, int pre)
{
    int p = ++ptot;
    nodes[p] = nodes[pre];
    if (ql <= l && r <= qr)
        return nodes[p].tag++, p;
    if (ql <= mid)
        nodes[p].lson = update(ql, qr, l, mid, nodes[pre].lson);
    if (mid < qr)
        nodes[p].rson = update(ql, qr, mid + 1, r, nodes[pre].rson);
    return p;
}

int query(int qx, int l, int r, int p)
{
    if (p == 0)
        return 0;
    int ret = nodes[p].tag;
    if (l == r)
        return ret;
    if (qx <= mid)
        ret += query(qx, l, mid, nodes[p].lson);
    else
        ret += query(qx, mid + 1, r, nodes[p].rson);
    return ret;
}

struct axisManager
{

    int ptr, org[MAX_N], roots[MAX_N], pre[MAX_N], pre_prod[MAX_N], suf[MAX_N];

    void moveLeft()
    {
        if (ptr == 1)
            return;
        roots[ptr] = roots[ptr + 1], suf[ptr] = suf[ptr + 1] + org[ptr];
        int lft = min(suf[ptr] - org[ptr], suf[ptr]), rig = max(suf[ptr] - org[ptr], suf[ptr]);
        roots[ptr] = update(lft, rig, -INF, INF, roots[ptr]), ptr--;
    }

    void moveRight()
    {
        if (ptr == n)
            return;
        ptr++;
        pre[ptr] = pre[ptr - 1] + org[ptr];
        pre_prod[ptr] = pre_prod[ptr - 1] + ((pre[ptr] > 0) ^ (pre[ptr - 1] > 0));
    }

    void build()
    {
        ptr = 0, org[0] = pre[0] = 1;
        for (int i = 1; i <= n; i++)
            moveRight();
        for (int i = n; i > 1; i--)
            moveLeft();
    }

    void updateOnAxis(int d)
    {
        org[ptr] = d, pre[ptr] = pre[ptr - 1] + org[ptr];
        pre_prod[ptr] = pre_prod[ptr - 1] + ((pre[ptr] > 0) ^ (pre[ptr - 1] > 0));
    }

    int queryOnAxis() { return query(pre[ptr] + suf[ptr + 1], -INF, INF, roots[ptr + 1]) + pre_prod[ptr]; }

} dr[2];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &dr[0].org[i], &dr[1].org[i]);
    dr[0].build(), dr[1].build(), scanf("%d", &m);
    while (m--)
    {
        scanf("%s", cmdlet + 1);
        if (cmdlet[1] == 'B')
            dr[0].moveLeft(), dr[1].moveLeft();
        else if (cmdlet[1] == 'C')
        {
            int nx, ny;
            scanf("%d%d", &nx, &ny);
            dr[0].updateOnAxis(nx), dr[1].updateOnAxis(ny);
        }
        else if (cmdlet[1] == 'F')
            dr[0].moveRight(), dr[1].moveRight();
        else if (cmdlet[1] == 'Q')
            printf("%d\n", dr[0].queryOnAxis() + dr[1].queryOnAxis());
    }
    return 0;
}