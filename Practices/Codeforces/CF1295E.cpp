// CF1295E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

typedef long long ll;

int n, pi[MAX_N], ai[MAX_N];
ll nodes[MAX_N << 2], tag[MAX_N << 2];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

// Segment tree;

void pushup(int p) { nodes[p] = min(nodes[lson], nodes[rson]); }

void pushdown(int p, int l, int r)
{
    if (tag[p])
    {
        nodes[lson] += tag[p], nodes[rson] += tag[p];
        tag[lson] += tag[p], tag[rson] += tag[p];
        tag[p] = 0;
    }
}

void update(int ql, int qr, int l, int r, int p, ll val)
{
    if (ql <= l && r <= qr)
        return (void)(nodes[p] += val, tag[p] += val);
    pushdown(p, l, r);
    if (ql <= mid)
        update(ql, qr, l, mid, lson, val);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, val);
    pushup(p);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &pi[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    for (int i = 1; i <= n; i++)
        update(pi[i], n, 0, n, 1, ai[i]);
    ll ans = 0x3f3f3f3f3f3f3f3f;
    for (int i = 1; i < n; i++)
    {
        // split : i;
        update(pi[i], n, 0, n, 1, -ai[i]);
        update(0, pi[i] - 1, 0, n, 1, ai[i]);
        ans = min(ans, nodes[1]);
    }
    printf("%lld\n", ans);
    return 0;
}