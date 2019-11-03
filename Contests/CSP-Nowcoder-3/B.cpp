// B.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e5 + 200;
const ll INF = 1e15;

int n, m, ai[MAX_N], stk1[MAX_N], tail1, stk2[MAX_N], tail2;
ll suffix[MAX_N], dp[MAX_N], prefix[MAX_N], nodes[MAX_N << 2], tag[MAX_N << 2];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void pushdown(int p)
{
    if (tag[p])
    {
        tag[lson] += tag[p], tag[rson] += tag[p];
        nodes[lson] += tag[p], nodes[rson] += tag[p];
        tag[p] = 0;
    }
}

void pushup(int p) { nodes[p] = min(nodes[lson], nodes[rson]); }

void update(int ql, int qr, int l, int r, int p, ll delta)
{
    if (ql <= l && r <= qr)
        return (void)(nodes[p] += delta, tag[p] += delta);
    pushdown(p);
    if (ql <= mid)
        update(ql, qr, l, mid, lson, delta);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, delta);
    pushup(p);
}

ll query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return nodes[p];
    pushdown(p);
    ll ret = INF;
    if (ql <= mid)
        ret = query(ql, qr, l, mid, lson);
    if (mid < qr)
        ret = min(ret, query(ql, qr, mid + 1, r, rson));
    return ret;
}

int main()
{
    scanf("%d%d", &n, &m);
    dp[0] = 0;
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), dp[i] = INF;
    for (int i = n; i >= 1; i--)
        suffix[i] = suffix[i + 1] + ai[i];
    for (int i = 1; i <= n; i++)
        prefix[i] = prefix[i - 1] + ai[i];
    int lcur = 1;
    for (int i = 1; i <= n; i++)
    {
        while (lcur <= i && prefix[i] - prefix[lcur - 1] > m)
            update(lcur, lcur, 1, n, 1, INF), lcur++;
        // stk1 stands for maximum points;
        while (tail1 > 0 && ai[i] >= ai[stk1[tail1]])
            update(stk1[tail1 - 1] + 1, stk1[tail1], 1, n, 1, ai[i] - ai[stk1[tail1]]), tail1--;
        stk1[++tail1] = i;
        // stk1 stands for minimum points;
        while (tail2 > 0 && ai[i] <= ai[stk2[tail2]])
            update(stk2[tail2 - 1] + 1, stk2[tail2], 1, n, 1, ai[stk2[tail2]] - ai[i]), tail2--;
        stk2[++tail2] = i;
        // all set!
        update(1, i, 1, n, 1, ai[i]);
        dp[i] = suffix[i + 1] + query(1, i, 1, n, 1);
        update(min(n, i + 1), min(n, i + 1), 1, n, 1, dp[i]);
    }
    printf("%lld", dp[n]);
    /*
    for (int i = n; i >= 1; i--)
    {
        int mx = ai[i], mi = ai[i];
        dp[i] = 0x3f3f3f3f3f3f3f3f;
        for (int j = i; j <= n; j++)
        {
            if (suffix[i] - suffix[j + 1] > m)
                break;
            mx = max(mx, ai[j]), mi = min(mi, ai[j]);
            dp[i] = min(dp[i], dp[j + 1] + suffix[i] + mx - mi);
        }
    }
    */
    return 0;
}