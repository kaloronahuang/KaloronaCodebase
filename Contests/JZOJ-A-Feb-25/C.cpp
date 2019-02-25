// C.cpp
#include <bits/stdc++.h>
#define mid ((l + r) >> 1)
#define lson (p << 1)
#define rson ((p << 1) | 1)
using namespace std;
const int MAX_N = 200200, INF = 0x3f3f3f3f;
int n, m, tree_l[MAX_N << 2], tree_r[MAX_N << 2], tree_len[MAX_N << 2], tree_pt[MAX_N << 2], park[(int)1e6 + 2000];
int getFirst(int a, int b, int c, int d)
{
    if (a > 0)
        return a;
    if (b > 0)
        return b;
    if (c > 0)
        return c;
    if (d > 0)
        return d;
    return d;
}
void update(int qx, int l, int r, int p)
{
    if (l == r && l == qx)
    {
        tree_l[p] = l, tree_r[p] = r, tree_len[p] = 0, tree_pt[p] = 0;
        return;
    }
    if (qx <= mid)
        update(qx, l, mid, lson);
    else
        update(qx, mid + 1, r, rson);
    tree_l[p] = getFirst(tree_l[lson], tree_r[lson], tree_l[rson], tree_r[rson]);
    tree_r[p] = getFirst(tree_r[rson], tree_l[rson], tree_r[lson], tree_l[lson]);
    // check three intervals;
    // first;
    tree_len[p] = tree_len[lson], tree_pt[p] = tree_pt[lson];
    if (tree_l[rson] > 0 && tree_r[lson] > 0 && ((tree_l[rson] - tree_r[lson]) >> 1) > tree_len[p])
        tree_len[p] = (tree_l[rson] - tree_r[lson]) >> 1, tree_pt[p] = (tree_r[lson] + tree_l[rson]) >> 1;
    if (tree_len[rson] > tree_len[p])
        tree_len[p] = tree_len[rson], tree_pt[p] = tree_pt[rson];
}
void remove(int qx, int l, int r, int p)
{
    if (l == r && l == qx)
    {
        tree_l[p] = tree_r[p] = tree_len[p] = tree_pt[p] = 0;
        return;
    }
    if (qx <= mid)
        remove(qx, l, mid, lson);
    else
        remove(qx, mid + 1, r, rson);
    tree_l[p] = getFirst(tree_l[lson], tree_r[lson], tree_l[rson], tree_r[rson]);
    tree_r[p] = getFirst(tree_r[rson], tree_l[rson], tree_r[lson], tree_l[lson]);
    // check three intervals;
    // first;
    tree_len[p] = tree_len[lson], tree_pt[p] = tree_pt[lson];
    if (tree_l[rson] > 0 && tree_r[lson] > 0 && ((tree_l[rson] - tree_r[lson]) >> 1) > tree_len[p])
        tree_len[p] = (tree_l[rson] - tree_r[lson]) >> 1, tree_pt[p] = (tree_r[lson] + tree_l[rson]) >> 1;
    if (tree_len[rson] > tree_len[p])
        tree_len[p] = tree_len[rson], tree_pt[p] = tree_pt[rson];
}
int main()
{
    scanf("%d%d", &n, &m);
    while (m--)
    {
        int opt, x;
        scanf("%d%d", &opt, &x);
        if (opt == 1)
        {
            if (tree_l[1] > 0)
            {
                int tmp = tree_len[1], key = tree_pt[1];
                if (tree_l[1] - 1 >= tmp)
                    key = 1, tmp = tree_l[1] - 1;
                if (n - tree_r[1] > tmp)
                    key = n, tmp = n - tree_r[1];
                park[x] = key;
            }
            else
                park[x] = 1;
            printf("%d\n", park[x]), update(park[x], 1, n, 1);
        }
        else
            remove(park[x], 1, n, 1);
    }
    return 0;
}