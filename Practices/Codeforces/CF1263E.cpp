// CF1263E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4e6 + 200;

int n, seq[MAX_N], tag[MAX_N];
char opt[MAX_N];

struct node
{
    int mx, mi, sum;
} nodes[MAX_N];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void update(int qx, int l, int r, int p, int val)
{
    if (l == r)
    {
        nodes[p].sum = nodes[p].mx = nodes[p].mi = val;
        return;
    }
    if (qx <= mid)
        update(qx, l, mid, lson, val);
    else
        update(qx, mid + 1, r, rson, val);
    nodes[p].sum = nodes[lson].sum + nodes[rson].sum;
    nodes[p].mx = max(nodes[lson].mx, nodes[rson].mx + nodes[lson].sum);
    nodes[p].mi = min(nodes[lson].mi, nodes[rson].mi + nodes[lson].sum);
}

int main()
{
    scanf("%d%s", &n, opt + 1);
    int ptr = 1;
    for (int i = 1; i <= n; i++)
    {
        if (opt[i] == 'L')
        {
            if (ptr > 1)
                ptr--;
        }
        else if (opt[i] == 'R')
            ptr++;
        else if (opt[i] == '(')
            update(ptr, 1, n, 1, 1);
        else if (opt[i] == ')')
            update(ptr, 1, n, 1, -1);
        else
            update(ptr, 1, n, 1, 0);
        node ret = nodes[1];
        if (ret.mi < 0 || ret.sum != 0)
            printf("-1 ");
        else
            printf("%d ", ret.mx);
    }
    return 0;
}