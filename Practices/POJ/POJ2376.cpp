// POJ2376.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define mid ((l + r) >> 1)
#define lson (p << 1)
#define rson ((p << 1) | 1)
using namespace std;
const int MAX_N = 100006, INF = 0x3f3f3f3f;
struct node
{
    int l, r;
    bool operator<(const node &nd) const { return r < nd.r; }
} stickers[MAX_N];
vector<int> mapping;
int n, edt, tree[MAX_N << 2], dp[MAX_N];

void build(int l, int r, int p)
{
    if (l == r)
    {
        tree[p] = INF;
        if (l == 0)
            tree[p] = 0;
        return;
    }
    build(l, mid, lson), build(mid + 1, r, rson);
    tree[p] = min(tree[lson], tree[rson]);
}

void update(int qx, int l, int r, int p, int val)
{
    if (l == r)
    {
        tree[p] = val;
        return;
    }
    if (qx <= mid)
        update(qx, l, mid, lson, val);
    if (mid < qx)
        update(qx, mid + 1, r, rson, val);
    tree[p] = min(tree[lson], tree[rson]);
}

int query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return tree[p];
    int ans = INF;
    if (ql <= mid)
        ans = min(ans, query(ql, qr, l, mid, lson));
    if (mid < qr)
        ans = min(ans, query(ql, qr, mid + 1, r, rson));
    return ans;
}

void print()
{
    for (int i = 0, siz = mapping.size(); i < siz; i++)
        printf("%d ", mapping[i]);
}

int main()
{
    scanf("%d%d", &n, &edt);
    mapping.push_back(1);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &stickers[i].l, &stickers[i].r);
        mapping.push_back(stickers[i].l), mapping.push_back(stickers[i].r);
        mapping.push_back(stickers[i].l + 1), mapping.push_back(stickers[i].r + 1);
    }
    mapping.push_back(edt);
    sort(mapping.begin(), mapping.end());
    mapping.erase(unique(mapping.begin(), mapping.end()), mapping.end());
    while (mapping.back() > edt)
        mapping.pop_back();

    edt = lower_bound(mapping.begin(), mapping.end(), edt) - mapping.begin() + 1;
    build(0, mapping.size(), 1);
    sort(stickers + 1, stickers + 1 + n);
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;
    int tot = mapping.size();
    for (int i = 1; i <= n; i++)
    {
        stickers[i].l = lower_bound(mapping.begin(), mapping.end(), stickers[i].l) - mapping.begin() + 1;
        stickers[i].r = lower_bound(mapping.begin(), mapping.end(), stickers[i].r) - mapping.begin() + 1;
    }
    for (int i = 1; i <= n; i++)
    {
        int num = query(stickers[i].l - 1, stickers[i].r - 1, 0, tot, 1) + 1;
        if (dp[stickers[i].r] > num)
            dp[stickers[i].r] = num,
            update(stickers[i].r, 0, tot, 1, dp[stickers[i].r]);
    }
    int ans = dp[edt];
    printf("%d", ans == INF ? -1 : ans);
    return 0;
}