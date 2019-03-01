// C.cpp
#include <bits/stdc++.h>
#define mid ((l + r) >> 1)
#define lson (p << 1)
#define rson ((p << 1) | 1)
using namespace std;
const int MAX_N = 100006, INF = 2147483647;
struct node
{
    int sum, x, y, tag;
} treeX[MAX_N << 2], treeY[MAX_N << 2];
int T, n, x_1, y_1, x_2, y_2, xi[MAX_N], yi[MAX_N], ans, m;
bool isIn(int x, int y) { return (x <= x_2 && x >= x_1 && y <= y_2 && y >= y_1); }
void merge(int p, node *tree)
{
    tree[p].sum = tree[lson].sum + tree[rson].sum;
    tree[p].x = max(tree[lson].x, tree[rson].x);
    tree[p].y = max(tree[lson].y, tree[rson].y);
    tree[p].tag = 0;
}
void build(int l, int r, int p, node *tree)
{
    if (l == r)
    {
        tree[p].sum = 0, tree[p].tag = 0;
        tree[p].x = tree[p].y = -INF;
        if (tree == treeX)
        {
            if (xi[l] < x_1)
                tree[p].x = xi[l];
            else if (xi[l] <= x_2)
                tree[p].y = xi[l];
        }
        else if (yi[l] < y_1)
            tree[p].x = yi[l];
        else if (yi[l] <= y_2)
            tree[p].y = yi[l];
        if (isIn(xi[l], yi[l]))
            tree[p].sum = 1;
        return;
    }
    build(l, mid, lson, tree), build(mid + 1, r, rson, tree);
    merge(p, tree);
}
void updateTag(int p, node *tree)
{
    if (tree[p].tag)
    {
        if (tree[lson].x > -INF)
            tree[lson].x += tree[p].tag;
        if (tree[lson].y > -INF)
            tree[lson].y += tree[p].tag;

        if (tree[rson].x > -INF)
            tree[rson].x += tree[p].tag;
        if (tree[rson].y > -INF)
            tree[rson].y += tree[p].tag;

        tree[lson].tag += tree[p].tag, tree[rson].tag += tree[p].tag;
        tree[p].tag = 0;
    }
}
void update(int ql, int qr, int l, int r, int p, int c, node *tree)
{
    if (ql == l && r == qr)
    {
        if (tree[p].x > -INF)
            tree[p].x += c;
        if (tree[p].y > -INF)
            tree[p].y += c;
        tree[p].tag += c;
        return;
    }
    updateTag(p, treeX), updateTag(p, treeY);
    if (qr <= mid)
        update(ql, qr, l, mid, lson, c, tree);
    else if (ql > mid)
        update(ql, qr, mid + 1, r, rson, c, tree);
    else
        update(ql, mid, l, mid, lson, c, tree), update(mid + 1, qr, mid + 1, r, rson, c, tree);
    merge(p, tree);
}
void add(int l, int r, int p, int c)
{
    if (l == r)
    {
        if (c == 1)
        {
            if (treeY[p].y <= y_2 && treeY[p].y >= y_1)
                treeX[p].sum = 1;
            else
                treeX[p].sum = 0;
            treeX[p].y = treeX[p].x, treeX[p].x = -INF;
        }
        else
        {
            if (treeX[p].y <= x_2 && treeX[p].y >= x_1)
                treeX[p].sum = 1;
            else
                treeX[p].sum = 0;
            treeY[p].y = treeY[p].x, treeY[p].x = -INF;
        }
        return;
    }
    updateTag(p, treeX), updateTag(p, treeY);
    if (c == 1)
        if (treeX[lson].x >= x_1)
            add(l, mid, lson, c);
        else
            add(mid + 1, r, rson, c);
    else if (treeY[lson].x >= y_1)
        add(l, mid, lson, c);
    else
        add(mid + 1, r, rson, c);
    merge(p, treeX), merge(p, treeY);
}
void remove(int l, int r, int p, int c)
{
    if (l == r)
    {
        treeX[p].x = treeX[p].y = treeY[p].x = treeY[p].y = -INF, treeX[p].sum = 0;
        return;
    }
    updateTag(p, treeX), updateTag(p, treeY);
    if (c == 1)
        if (treeX[lson].y > x_2)
            remove(l, mid, lson, c);
        else
            remove(mid + 1, r, rson, c);
    else if (treeY[lson].y > y_2)
        remove(l, mid, lson, c);
    else
        remove(mid + 1, r, rson, c);
    merge(p, treeX), merge(p, treeY);
}
void query(int ql, int qr, int l, int r, int p)
{
    if (ql == l && r == qr)
    {
        ans += treeX[p].sum;
        return;
    }
    updateTag(p, treeX), updateTag(p, treeY);
    if (qr <= mid)
        query(ql, qr, l, mid, lson);
    else if (ql > mid)
        query(ql, qr, mid + 1, r, rson);
    else
        query(ql, mid, l, mid, lson), query(mid + 1, qr, mid + 1, r, rson);
    merge(p, treeX), merge(p, treeY);
}
int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%d%d%d", &n, &x_1, &y_1, &x_2, &y_2);
        for (int i = 1; i <= n; i++)
            scanf("%d%d", &xi[i], &yi[i]);
        build(1, n, 1, treeX), build(1, n, 1, treeY);
        scanf("%d", &m);
        while (m--)
        {
            int d, l, r, c;
            scanf("%d%d%d", &d, &l, &r);
            if (d != 3)
            {
                scanf("%d", &c);
                if (d == 1)
                {
                    update(l, r, 1, n, 1, c, treeX);
                    while (treeX[1].x >= x_1)
                        add(1, n, 1, 1);
                    while (treeX[1].y > x_2)
                        remove(1, n, 1, 1);
                }
                else
                {
                    update(l, r, 1, n, 1, c, treeY);
                    while (treeY[1].x >= y_1)
                        add(1, n, 1, 2);
                    while (treeY[1].y > y_2)
                        remove(1, n, 1, 2);
                }
                continue;
            }
            ans = 0;
            query(l, r, 1, n, 1), printf("%d\n", ans);
        }
    }
    return 0;
}