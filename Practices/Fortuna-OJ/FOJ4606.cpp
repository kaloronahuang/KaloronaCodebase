// FOJ4606.cpp
#include <bits/stdc++.h>
#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

using namespace std;

const int MAX_N = 1e5 + 200;

int tree[MAX_N << 2], n, m, low[MAX_N], up[MAX_N], dp[MAX_N], seq[MAX_N], idx[MAX_N];
int max_range;
bool tag[MAX_N << 2];

bool compareBySequenceVal(int a, int b) { return seq[a] < seq[b]; }
bool compareByMinimalVal(int a, int b) { return low[a] < low[b]; }

inline void pushup(int p) { tree[p] = max(tree[lson], tree[rson]); }

inline void pushdown(int p)
{
    if (tag[p])
    {
        tree[lson] = tree[rson] = 0;
        tag[lson] = tag[rson] = tag[p];
        tag[p] = false;
    }
}

void update(int qx, int l, int r, int p, int val)
{
    if (l == r)
    {
        tree[p] = max(tree[p], val);
        return;
    }
    pushdown(p);
    if (qx <= mid)
        update(qx, l, mid, lson, val);
    else
        update(qx, mid + 1, r, rson, val);
    pushup(p);
}

int query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return tree[p];
    pushdown(p);
    int ans = 0;
    if (ql <= mid)
        ans = query(ql, qr, l, mid, lson);
    if (mid < qr)
        ans = max(ans, query(ql, qr, mid + 1, r, rson));
    return ans;
}

void solve(int l, int r)
{
    if (l == r)
        return (void)(dp[l] = max(dp[l], 1));
    solve(l, mid);
    for (int i = l; i <= r; i++)
        idx[i] = i;
    sort(idx + l, idx + mid + 1, compareBySequenceVal);
    sort(idx + mid + 1, idx + 1 + r, compareByMinimalVal);
    tag[1] = true, tree[1] = 0;

    int lft = l;
    for (int rgt = mid + 1; rgt <= r; rgt++)
    {
        while (lft <= mid && seq[idx[lft]] <= low[idx[rgt]])
            update(up[idx[lft]], 1, max_range, 1, dp[idx[lft]]), lft++;
        dp[idx[rgt]] = max(dp[idx[rgt]], query(1, seq[idx[rgt]], 1, max_range, 1) + 1);
    }
    solve(mid + 1, r);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i]), up[i] = low[i] = seq[i];
    for (int i = 1, tmpx, tmpy; i <= m; i++)
    {
        scanf("%d%d", &tmpx, &tmpy);
        low[tmpx] = min(low[tmpx], tmpy), up[tmpx] = max(up[tmpx], tmpy);
        max_range = max(up[tmpx], max_range);
    }
    solve(1, n);
    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans = max(ans, dp[i]);
    printf("%d", ans);
    return 0;
}
