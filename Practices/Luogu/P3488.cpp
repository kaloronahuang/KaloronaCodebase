// P3488.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 200;

typedef long long ll;

int n, m, k, d;

struct node
{
    ll lft, rig, sum, seg;
} nodes[MAX_N << 2];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void pushup(int p)
{
    nodes[p].sum = nodes[lson].sum + nodes[rson].sum;
    nodes[p].lft = max(nodes[lson].lft, nodes[lson].sum + nodes[rson].lft);
    nodes[p].rig = max(nodes[rson].rig, nodes[rson].sum + nodes[lson].rig);
    nodes[p].seg = max(nodes[lson].rig + nodes[rson].lft, max(nodes[lson].seg, nodes[rson].seg));
}

void build(int l, int r, int p)
{
    if (l == r)
    {
        nodes[p] = node{0, 0, -k, -k};
        return;
    }
    build(l, mid, lson), build(mid + 1, r, rson);
    pushup(p);
}

void update(int qx, int l, int r, int p, int val)
{
    if (l == r)
    {
        nodes[p].sum += val, nodes[p].seg += val;
        nodes[p].lft = nodes[p].rig = max(0LL, nodes[p].sum);
        return;
    }
    if (qx <= mid)
        update(qx, l, mid, lson, val);
    else
        update(qx, mid + 1, r, rson, val);
    pushup(p);
}

#undef mid
#undef rson
#undef lson

int main()
{
    scanf("%d%d%d%d", &n, &m, &k, &d), build(1, n, 1);
    for (int i = 1; i <= m; i++)
    {
        int xpos, val;
        scanf("%d%d", &xpos, &val), update(xpos, 1, n, 1, val);
        puts(nodes[1].seg <= 1LL * d * k ? "TAK" : "NIE");
    }
    return 0;
}