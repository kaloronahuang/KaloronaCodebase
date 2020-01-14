// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;
typedef long long ll;

int n, k, ptot;

struct tup
{
    ll x, y;
    bool operator<(const tup &rhs) const { return 0LL + x + y < 0LL + rhs.x + rhs.y; }
} tups[MAX_N];

void fileIO()
{
    freopen("shoes.in", "r", stdin);
    freopen("shoes.out", "w", stdout);
}

struct node
{
    int lson, rson;
    ll val, cnt;
} nodes[MAX_N * 40];

#define mid ((l + r) >> 1)

int update(int qx, int l, int r, int pre)
{
    int p = ++ptot;
    nodes[p] = nodes[pre], nodes[p].cnt++, nodes[p].val += qx;
    if (l == r)
        return p;
    if (qx <= mid)
        nodes[p].lson = update(qx, l, mid, nodes[pre].lson);
    else
        nodes[p].rson = update(qx, mid + 1, r, nodes[pre].rson);
    return p;
}

int main()
{
    fileIO();
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld%lld", &tups[i].x, &tups[i].y);
        tups[i].x += 1e9 + 1, tups[i].y += 1e9 + 1;
        if (tups[i].x > tups[i].y)
            swap(tups[i].x, tups[i].y);
    }
    sort(tups + 1, tups + 1 + n);
    return 0;
}