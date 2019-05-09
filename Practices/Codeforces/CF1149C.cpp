// CF1149C.cpp
#include <bits/stdc++.h>
#define mid ((l + r) >> 1)
#define lson (p << 1)
#define rson ((p << 1) | 1)
using namespace std;

const int MAX_N = 101000;

struct node
{
    int dep, da, dadb, db, dbdc, ans;
} nodes[MAX_N << 2];

const node lft_default = node{1, 1, 0, 0, 1, 1}, rig_default = {-1, 0, 2, 2, 1, 1};

char source[MAX_N << 1];
int n, q, ndt;

void pushup(int l, int r, int p)
{
    nodes[p].dep = nodes[lson].dep + nodes[rson].dep;
    nodes[p].da = max(nodes[lson].da, nodes[lson].dep + nodes[rson].da);
    nodes[p].db = max(nodes[lson].db, nodes[rson].db - 2 * nodes[lson].dep);
}

void build(int l, int r, int p)
{
    if (l == r)
    {
        if (source[l] == '(')
            nodes[p] = lft_default;
        else
            nodes[p] = rig_default;
        return;
    }
    build(l, mid, lson), build(mid + 1, r, rson);
}

int main()
{
    scanf("%d%d%s", &n, &q, source + 1), ndt = (n >> 1) + 1;

    return 0;
}