// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200, RANGE = 1e6 + 20;

typedef long long ll;
typedef pair<int, int> pii;

const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, m, p;
ll pre_min[MAX_N], nodes[MAX_N << 2], tag[MAX_N << 2];
pii ai[MAX_N], bi[MAX_N];

struct tup
{
    int x, y, z;
    bool operator<(const tup &rhs) const { return x < rhs.x || (x == rhs.x && y < rhs.y); }
} tups[MAX_N];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void pushdown(int p)
{
    if (tag[p] != 0)
    {
        tag[lson] += tag[p], tag[rson] += tag[p];
        nodes[lson] += tag[p], nodes[rson] += tag[p];
        tag[p] = 0;
    }
}

void pushup(int p) { nodes[p] = max(nodes[lson], nodes[rson]); }

void update(int ql, int qr, int l, int r, int p, ll val)
{
    if (ql <= l && r <= qr)
        return (void)(nodes[p] += val, tag[p] += val);
    pushdown(p);
    if (ql <= mid)
        update(ql, qr, l, mid, lson, val);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, val);
    pushup(p);
}

#undef mid
#undef rson
#undef lson

int main()
{
    scanf("%d%d%d", &n, &m, &p);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &ai[i].first, &ai[i].second);
    for (int i = 1; i <= m; i++)
        scanf("%d%d", &bi[i].first, &bi[i].second);
    for (int i = 1; i <= p; i++)
        scanf("%d%d%d", &tups[i].x, &tups[i].y, &tups[i].z), tups[i].y++, tups[i].x++;
    sort(ai + 1, ai + 1 + n), sort(bi + 1, bi + 1 + m), sort(tups + 1, tups + 1 + p);
    pre_min[m + 1] = INF;
    for (int i = m; i >= 1; i--)
        pre_min[i] = min(pre_min[i + 1], 1LL * bi[i].second);
    int last_pos = 1;
    for (int i = 1; i <= m; i++)
        update(last_pos, bi[i].first, 1, RANGE, 1, -pre_min[i]), last_pos = bi[i].first + 1;
    update(last_pos, RANGE, 1, RANGE, 1, -INF);
    ll ans = -INF;
    for (int i = 1, ptr = 1; i <= n; i++)
    {
        int pos = ai[i].first, cost = ai[i].second;
        while (ptr <= p && tups[ptr].x <= pos)
            update(tups[ptr].y, RANGE, 1, RANGE, 1, tups[ptr].z), ptr++;
        ans = max(ans, nodes[1] - cost);
    }
    printf("%lld\n", ans);
    return 0;
}