// D.cpp
#include <bits/stdc++.h>
#define mid ((l + r) >> 1)
#define lson (p << 1)
#define rson ((p << 1) | 1)

using namespace std;

const int MAX_N = 5e5 + 2000;

struct node
{
    int sum, lft, rgt, lazy;
} nodes[MAX_N << 2];

int original_chain[MAX_N], cursor = 1, wise_direction = 1, n, c, q;

void build(int l, int r, int p)
{
    if (l == r)
    {
        nodes[p].sum = 1, nodes[p].lft = nodes[p].rgt = original_chain[l];
        return;
    }
    build(l, mid, lson), build(mid + 1, r, rson);
    nodes[p].lft = nodes[lson].lft, nodes[p].rgt = nodes[rson].rgt;
    nodes[p].sum = nodes[lson].sum + nodes[rson].sum - ((nodes[lson].rgt == nodes[rson].lft) ? 1 : 0);
    return;
}

void pushdown(int l, int r, int p)
{
    if (nodes[p].lazy)
    {
        nodes[lson].lazy = nodes[rson].lazy = nodes[p].lazy;
        nodes[lson].sum = nodes[rson].sum = 1;
        nodes[lson].lft = nodes[lson].rgt = nodes[p].lazy;
        nodes[rson].lft = nodes[rson].rgt = nodes[p].lazy;
        nodes[p].lazy = 0;
    }
}

void update(int ql, int qr, int l, int r, int p, int val)
{
    if (ql <= l && r <= qr)
    {
        nodes[p].lazy = val;
        nodes[p].lft = nodes[p].rgt = val, nodes[p].sum = 1;
        return;
    }
    pushdown(l, r, p);
    if (ql <= mid)
        update(ql, qr, l, mid, lson, val);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, val);
    nodes[p].lft = nodes[lson].lft, nodes[p].rgt = nodes[rson].rgt;
    nodes[p].sum = nodes[lson].sum + nodes[rson].sum - ((nodes[lson].rgt == nodes[rson].lft) ? 1 : 0);
}

node query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return nodes[p];
    pushdown(l, r, p);
    node ans, tmpl, tmpr;
    if (ql <= mid)
        tmpl = query(ql, qr, l, mid, lson), ans = tmpl;
    if (mid < qr)
        tmpr = query(ql, qr, mid + 1, r, rson), ans = tmpr;
    if (ql <= mid && mid < qr)
        ans.lft = tmpl.lft, ans.sum -= ((tmpl.rgt == tmpr.lft) ? 1 : 0) - tmpl.sum;
    return ans;
}

char opt[20];

int main()
{
    scanf("%d%d", &n, &c);
    for (int i = 1; i <= n; i++)
        scanf("%d", &original_chain[i]);
    build(1, n, 1);
    scanf("%d", &q);
    while (q--)
    {
        int tmpx, tmpy, tmpz;
        scanf("%s", opt + 1);
        if (opt[1] == 'R')
            scanf("%d", &tmpx), cursor = (cursor - 1 + tmpx) % n + 1;
        else if (opt[1] == 'F')
            wise_direction *= -1;
        else if (opt[1] == 'S')
        {
            scanf("%d%d", &tmpx, &tmpy);
            tmpx = (tmpx - 1 - wise_direction * (cursor - 1) + n) % n + 1;
            tmpy = (tmpy - 1 - wise_direction * (cursor - 1) + n) % n + 1;
            int c1 = query(tmpx, tmpx, 1, n, 1).lft, c2 = query(tmpy, tmpy, 1, n, 1).lft;
            update(tmpx, tmpx, 1, n, 1, c2), update(tmpy, tmpy, 1, n, 1, c1);
        }
        else if (opt[1] == 'P')
        {
            scanf("%d%d%d", &tmpx, &tmpy, &tmpz);
            tmpx = (tmpx - 1 - wise_direction * (cursor - 1) + n) % n + 1;
            tmpy = (tmpy - 1 - wise_direction * (cursor - 1) + n) % n + 1;
            if (tmpx > tmpy)
                update(1, tmpx, 1, n, 1, tmpz), update(tmpy, n, 1, n, 1, tmpz);
            else
                update(tmpx, tmpy, 1, n, 1, tmpz);
        }
        else if (opt[1] == 'C' && opt[2] == 'S')
        {
            scanf("%d%d", &tmpx, &tmpy);
            tmpx = (tmpx - 1 - wise_direction * (cursor - 1) + n) % n + 1;
            tmpy = (tmpy - 1 - wise_direction * (cursor - 1) + n) % n + 1;
            if (tmpx > tmpy)
            {
                node ans1 = query(1, tmpx, 1, n, 1), ans2 = query(tmpy, n, 1, n, 1);
                printf("%d\n", ans1.sum + ans2.sum - ((ans1.lft == ans2.rgt) ? 1 : 0));
            }
            else
            {
                printf("%d\n", query(tmpx, tmpy, 1, n, 1).sum);
                continue;
            }
        }
        else
        {
            node ans = nodes[1];
            printf("%d\n", ans.sum - ((ans.lft == ans.rgt) ? 1 : 0));
        }
    }
    return 0;
}