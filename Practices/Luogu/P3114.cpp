// P3114.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 5e5 + 200;

struct triple
{
    int l, r, height;
    bool operator<(const triple &tp) const { return height < tp.height; }
} tps[MAX_N];

vector<ll> vec;
int n, xi[MAX_N], spd[MAX_N], nodes[MAX_N << 2];
bool toggle[MAX_N << 2], tag[MAX_N << 2];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void pushup(int p)
{
    return (void)(nodes[p] = max(nodes[lson], nodes[rson]));
}

void build(int l, int r, int p)
{
    if (l == r)
        return (void)(nodes[p] = 0x3f3f3f3f);
    build(l, mid, lson), build(mid + 1, r, rson);
    pushup(p);
}

void pushdown(int p)
{
    if (toggle[p])
    {
        toggle[p] = false;
        nodes[lson] = nodes[rson] = tag[p];
        tag[lson] = tag[rson] = tag[p];
        tag[p] = 0, toggle[lson] = toggle[rson] = true;
    }
}

int query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return nodes[p];
    pushdown(p);
    int ans = -1;
    if (ql <= mid)
        ans = max(query(ql, qr, l, mid, lson), ans);
    if (mid < qr)
        ans = max(query(ql, qr, mid + 1, r, rson), ans);
    return ans;
}

void update(int ql, int qr, int l, int r, int p, int val)
{
    if (ql <= l && r <= qr)
        return (void)(nodes[p] = tag[p] = val, toggle[p] = true);
    pushdown(p);
    if (ql <= mid)
        update(ql, qr, l, mid, lson, val);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, val);
    pushup(p);
}

#undef lson
#undef rson
#undef mid

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d%d", &xi[i], &tps[i].height, &spd[i]);
        // queue time;
        vec.push_back(1LL * (-xi[i] - 1) * spd[i]);
        vec.push_back(1LL * (-xi[i]) * spd[i]);
    }
    sort(vec.begin(), vec.end()), vec.erase(unique(vec.begin(), vec.end()), vec.end());
    for (int i = 1; i <= n; i++)
    {
        tps[i].l = lower_bound(vec.begin(), vec.end(), 1LL * (-xi[i] - 1) * spd[i]) - vec.begin() + 1;
        tps[i].r = lower_bound(vec.begin(), vec.end(), 1LL * (-xi[i]) * spd[i]) - vec.begin() + 1;
    }
    int upper = vec.size();
    sort(tps + 1, tps + 1 + n), build(1, upper, 1);
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        int tmp = query(tps[i].l, tps[i].r - 1, 1, upper, 1);
        if (tmp == 0x3f3f3f3f)
            ans++;
        update(tps[i].l, tps[i].r - 1, 1, upper, 1, tps[i].height);
    }
    printf("%d", ans);
    return 0;
}