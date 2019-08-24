// P3332.cpp
#include <bits/stdc++.h>
#define ll long long
#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

using namespace std;

const int MAX_N = 51000;

ll tree[MAX_N << 2], tag[MAX_N << 2], answers[MAX_N], n, m, qtot, cur[MAX_N];
struct query
{
    int opt, a, b, id;
    ll c;
} queries[MAX_N], q1[MAX_N], q2[MAX_N];

void pushdown(int l, int r, int p)
{
    if (tag[p])
    {
        tag[lson] += tag[p], tag[rson] += tag[p];
        tree[lson] += 1LL * (mid - l + 1) * tag[p], tree[rson] += 1LL * (r - mid) * tag[p];
        tag[p] = 0;
    }
}

void update(int ql, int qr, int l, int r, int p, ll val)
{
    if (ql <= l && r <= qr)
        return (void)(tree[p] += 1LL * (r - l + 1) * val, tag[p] += val);
    pushdown(l, r, p);
    if (ql <= mid)
        update(ql, qr, l, mid, lson, val);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, val);
    tree[p] = tree[lson] + tree[rson];
}

ll query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return tree[p];
    pushdown(l, r, p);
    ll ans = 0;
    if (ql <= mid)
        ans += query(ql, qr, l, mid, lson);
    if (mid < qr)
        ans += query(ql, qr, mid + 1, r, rson);
    return ans;
}

#undef mid

void solve(int a, int b, ll l, ll r)
{
    if (a > b || l > r)
        return;
    if (l == r)
    {
        for (int i = a; i <= b; i++)
            if (queries[i].opt == 2)
                answers[queries[i].id] = l;
        return;
    }
    ll mid = (l + r) >> 1;
    for (int i = a; i <= b; i++)
        if (queries[i].opt == 1 && queries[i].c > mid)
            update(queries[i].a, queries[i].b, 1, n, 1, 1);
        else if (queries[i].opt == 2)
            cur[i] = query(queries[i].a, queries[i].b, 1, n, 1);
    for (int i = a; i <= b; i++)
        if (queries[i].opt == 1 && queries[i].c > mid)
            update(queries[i].a, queries[i].b, 1, n, 1, -1);

    int tot1 = 0, tot2 = 0;
    for (int i = a; i <= b; i++)
        if (queries[i].opt == 2)
            if (cur[i] >= queries[i].c)
                q2[++tot2] = queries[i];
            else
                queries[i].c -= cur[i], q1[++tot1] = queries[i];
        else if (queries[i].c <= mid)
            q1[++tot1] = queries[i];
        else
            q2[++tot2] = queries[i];
    for (int i = 1; i <= tot1; i++)
        queries[i + a - 1] = q1[i];
    for (int i = 1; i <= tot2; i++)
        queries[i + a + tot1 - 1] = q2[i];
    solve(a, a + tot1 - 1, l, mid);
    solve(a + tot1, b, mid + 1, r);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d%lld", &queries[i].opt, &queries[i].a, &queries[i].b, &queries[i].c);
        if (queries[i].opt == 2)
            queries[i].id = ++qtot;
    }
    solve(1, m, -n, n);
    for (int i = 1; i <= qtot; i++)
        printf("%d\n", answers[i]);
    return 0;
}
// P3332.cpp