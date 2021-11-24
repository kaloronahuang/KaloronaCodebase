// F.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, m, nodes[MAX_N << 2], tag[MAX_N << 2];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void pushdown(int p, int l, int r)
{
    if (tag[p] == 1)
    {
        nodes[lson] = mid - l + 1, nodes[rson] = r - mid;
        tag[lson] = tag[rson] = tag[p];
    }
    else if (tag[p] == -1)
    {
        nodes[lson] = nodes[rson] = 0;
        tag[lson] = tag[rson] = tag[p];
    }
    tag[p] = 0;
}

void update(int ql, int qr, int l, int r, int p, int opt)
{
    if (ql <= l && r <= qr)
    {
        if (opt == 1)
            nodes[p] = r - l + 1;
        else
            nodes[p] = 0;
        tag[p] = opt;
        return;
    }
    pushdown(p, l, r);
    if (ql <= mid)
        update(ql, qr, l, mid, lson, opt);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, opt);
    nodes[p] = nodes[lson] + nodes[rson];
}

int query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return nodes[p];
    pushdown(p, l, r);
    int ret = 0;
    if (ql <= mid)
        ret += query(ql, qr, l, mid, lson);
    if (mid < qr)
        ret += query(ql, qr, mid + 1, r, rson);
    return ret;
}

int main()
{
    scanf("%d%d", &n, &m);
    while (m--)
    {
        int opt, x, y;
        scanf("%d%d%d", &opt, &x, &y);
        if (opt == 1)
        {
            if ((n - x + 1) - query(x, n, 1, n, 1) < y)
                puts("0");
            else
            {
                int l = x, r = n, lft = -1, rig = -1;
                if (query(x, x, 1, n, 1) == 0)
                    lft = x;
                else
                    while (l <= r)
                    {
                        if (query(x, mid, 1, n, 1) != mid - x + 1)
                            lft = mid, r = mid - 1;
                        else
                            l = mid + 1;
                    }
                l = lft, r = n;
                while (l <= r)
                {
                    if ((mid - lft + 1) - query(lft, mid, 1, n, 1) >= y)
                        rig = mid, r = mid - 1;
                    else
                        l = mid + 1;
                }
                printf("%d %d\n", lft, rig), update(lft, rig, 1, n, 1, 1);
            }
        }
        else
            printf("%d\n", query(x, y, 1, n, 1)), update(x, y, 1, n, 1, -1);
    }
    return 0;
}