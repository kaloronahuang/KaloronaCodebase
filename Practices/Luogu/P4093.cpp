// P4093.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, m, ai[MAX_N], mx[MAX_N], mn[MAX_N], dp[MAX_N], nodes[MAX_N], idx[MAX_N];

inline int lowbit(int x) { return x & (-x); }

void update(int x, int d)
{
    for (; x <= n; x += lowbit(x))
        nodes[x] = max(nodes[x], d);
}

void clear(int x)
{
    for (; x <= n; x += lowbit(x))
        nodes[x] = 0;
}

int query(int x, int ret = 0)
{
    for (; x; x -= lowbit(x))
        ret = max(ret, nodes[x]);
    return ret;
}

void solve(int l, int r)
{
    if (l == r)
        return (void)(dp[l] = max(dp[l], 1));
    int mid = (l + r) >> 1;
    solve(l, mid);
    for (int i = l; i <= r; i++)
        idx[i] = i;
    sort(idx + l, idx + mid + 1, [](const int &a, const int &b) { return mx[a] < mx[b]; });
    sort(idx + mid + 1, idx + r + 1, [](const int &a, const int &b) { return ai[a] < ai[b]; });
    for (int i = mid + 1, ptr = l; i <= r; i++)
    {
        while (ptr <= mid && mx[idx[ptr]] <= ai[idx[i]])
            update(ai[idx[ptr]], dp[idx[ptr]]), ptr++;
        dp[idx[i]] = max(dp[idx[i]], query(mn[idx[i]]) + 1);
    }
    for (int i = mid + 1, ptr = l; i <= r; i++)
        while (ptr <= mid && mx[idx[ptr]] <= ai[idx[i]])
            clear(ai[idx[ptr]]), ptr++;
    solve(mid + 1, r);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), mx[i] = mn[i] = ai[i];
    for (int i = 1, x, y; i <= n; i++)
        scanf("%d%d", &x, &y), mx[x] = max(mx[x], y), mn[x] = min(mn[x], y);
    solve(1, n);
    int ans = *max_element(dp + 1, dp + 1 + n);
    printf("%d\n", ans);
    return 0;
}