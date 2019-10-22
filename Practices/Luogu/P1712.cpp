// P1712.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

int n, m;
int nodes[MAX_N << 2], tag[MAX_N << 2];
struct segment
{
    int l, r, len;
    bool operator<(const segment &target) const { return len < target.len; }
} segments[MAX_N];
vector<int> mp;

int getId(int x) { return lower_bound(mp.begin(), mp.end(), x) - mp.begin() + 1; }

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void pushdown(int p, int l, int r)
{
    if (tag[p] != 0)
    {
        nodes[lson] += tag[p], nodes[rson] += tag[p];
        tag[lson] += tag[p], tag[rson] += tag[p];
        tag[p] = 0;
    }
}

void update(int ql, int qr, int l, int r, int p, int val)
{
    if (ql <= l && r <= qr)
    {
        tag[p] += val, nodes[p] += val;
        return;
    }
    pushdown(p, l, r);
    if (ql <= mid)
        update(ql, qr, l, mid, lson, val);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, val);
    nodes[p] = max(nodes[lson], nodes[rson]);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &segments[i].l, &segments[i].r), mp.push_back(segments[i].l), mp.push_back(segments[i].r);
    sort(mp.begin(), mp.end()), mp.erase(unique(mp.begin(), mp.end()), mp.end());
    for (int i = 1; i <= n; i++)
    {
        segments[i].len = segments[i].r - segments[i].l;
        segments[i].l = getId(segments[i].l), segments[i].r = getId(segments[i].r);
    }
    sort(segments + 1, segments + 1 + n);
    int upper = mp.size(), ans = 0x3f3f3f3f;
    for (int i = 1, lower = 1; i <= n; i++)
    {
        update(segments[i].l, segments[i].r, 1, upper, 1, 1);
        while (nodes[1] >= m)
        {
            update(segments[lower].l, segments[lower].r, 1, upper, 1, -1);
            ans = min(ans, segments[i].len - segments[lower].len), lower++;
        }
    }
    printf("%d", ans == 0x3f3f3f3f ? -1 : ans);
    return 0;
}