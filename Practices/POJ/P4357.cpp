// P4357.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 101000, INF = 0x3f3f3f3f;

int n, k, opt, max_val[MAX_N << 1][2], min_val[MAX_N << 1][2], lson[MAX_N << 1], rson[MAX_N << 1], ptot;

struct point
{
    ll x[2];
} pts[MAX_N], tree[MAX_N << 1];

priority_queue<ll> q;

bool compare(const point &a, const point &b) { return a.x[opt] < b.x[opt]; }

void pushup(int p)
{
    for (int i = 0; i < 2; i++)
        max_val[p][i] = min_val[p][i] = tree[p].x[i];
    if (lson[p])
        for (int i = 0; i < 2; i++)
            max_val[p][i] = max(max_val[p][i], max_val[lson[p]][i]), min_val[p][i] = min(min_val[p][i], min_val[lson[p]][i]);
    if (rson[p])
        for (int i = 0; i < 2; i++)
            max_val[p][i] = max(max_val[p][i], max_val[rson[p]][i]), min_val[p][i] = min(min_val[p][i], min_val[rson[p]][i]);
}

int build(int l, int r)
{
    if (l > r)
        return 0;
    int p = ++ptot, mid = (l + r) >> 1;
    opt ^= 1;
    nth_element(pts + l, pts + mid, pts + 1 + r, compare), tree[p] = pts[mid];
    lson[p] = build(l, mid - 1), rson[p] = build(mid + 1, r);
    pushup(p);
    return p;
}

ll pow2(ll bas) { return bas * bas; }

ll getDist(point a, point b) { return pow2(a.x[0] - b.x[0]) + pow2(a.x[1] - b.x[1]); }

ll getMax(point a, int pt)
{
    return max(pow2(a.x[0] - max_val[pt][0]), pow2(a.x[0] - min_val[pt][0])) + max(pow2(a.x[1] - max_val[pt][1]), pow2(a.x[1] - min_val[pt][1]));
}

void query(int p, point pt)
{
    ll lb = -INF, rb = -INF;
    if (lson[p])
        lb = getMax(pt, lson[p]);
    if (rson[p])
        rb = getMax(pt, rson[p]);
    ll b = getDist(pt, tree[p]);
    if (-q.top() < b)
        q.pop(), q.push(-b);
    if (lb > rb)
    {
        if (-q.top() < lb)
            query(lson[p], pt);
        if (-q.top() < rb)
            query(rson[p], pt);
    }
    else
    {
        if (-q.top() < rb)
            query(rson[p], pt);
        if (-q.top() < lb)
            query(lson[p], pt);
    }
}

int main()
{
    srand(time(NULL));
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &pts[i].x[0], &pts[i].x[1]);
    for (int i = 1; i <= 2 * k; i++)
        q.push(0);
    build(1, n);
    for (int i = 1; i <= n; i++)
        query(1, pts[i]);
    printf("%lld\n", -q.top());
    return 0;
} // P4357.cpp