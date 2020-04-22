// P3246.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

typedef long long ll;

int n, q, ai[MAX_N], block, log2_[MAX_N], st[20][MAX_N], stk[MAX_N], tail;
ll ansBox[MAX_N], lft[MAX_N], rig[MAX_N];

struct queryInfo
{
    int l, r, aff, id;
    bool operator<(const queryInfo &qi) const { return aff < qi.aff || (aff == qi.aff && ((aff & 1) ? r > qi.r : r < qi.r)); }
} queries[MAX_N];

int gmin(int x, int y) { return ai[x] < ai[y] ? x : y; }

int query(int l, int r)
{
    int d = log2_[r - l + 1];
    return gmin(st[d][l], st[d][r - (1 << d) + 1]);
}

int main()
{
    scanf("%d%d", &n, &q), block = sqrt(n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), st[0][i] = i;
    log2_[2] = 1;
    for (int i = 3; i <= n; i++)
        log2_[i] = log2_[i >> 1] + 1;
    for (int i = 1; i < 20; i++)
        for (int j = 1; j + (1 << i) - 1 <= n; j++)
            st[i][j] = gmin(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
    for (int i = 1; i <= q; i++)
        scanf("%d%d", &queries[i].l, &queries[i].r), queries[i].id = i, queries[i].aff = queries[i].l / block;
    sort(queries + 1, queries + 1 + q);
    for (int i = 1; i <= n; i++)
    {
        while (tail > 0 && ai[i] <= ai[stk[tail]])
            tail--;
        rig[i] = 1LL * ai[i] * (i - stk[tail]) + rig[stk[tail]];
        stk[++tail] = i;
    }
    for (int i = n; i >= 1; i--)
    {
        while (tail > 0 && ai[i] <= ai[stk[tail]])
            tail--;
        lft[i] = 1LL * ai[i] * (stk[tail] - i) + lft[stk[tail]];
        stk[++tail] = i;
    }
    int lb = 1, rb = 0;
    ll ans = 0;
    for (int i = 1, id; i <= q; i++)
    {
        while (lb > queries[i].l)
            lb--, id = query(lb, rb), ans += lft[lb] - lft[id] + 1LL * ai[id] * (rb - id + 1);
        while (rb < queries[i].r)
            rb++, id = query(lb, rb), ans += rig[rb] - rig[id] + 1LL * ai[id] * (id - lb + 1);
        while (lb < queries[i].l)
            id = query(lb, rb), ans -= lft[lb] - lft[id] + 1LL * ai[id] * (rb - id + 1), lb++;
        while (rb > queries[i].r)
            id = query(lb, rb), ans -= rig[rb] - rig[id] + 1LL * ai[id] * (id - lb + 1), rb--;
        ansBox[queries[i].id] = ans;
    }
    for (int i = 1; i <= q; i++)
        printf("%lld\n", ansBox[i]);
    return 0;
}