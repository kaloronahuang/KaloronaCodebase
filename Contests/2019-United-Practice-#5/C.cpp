// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 200;

struct query
{
    int l, r, id;
    bool operator<(const query &target) const { return r > target.r; }
} queries[MAX_N];

int n, m, T, k, anses[MAX_N], arr[MAX_N], tree[MAX_N], pre[MAX_N], pos[MAX_N];

inline int lowbit(int x) { return x & (-x); }

void update(int x, int d)
{
    if (x == 0)
        return;
    for (; x <= n; x += lowbit(x))
        tree[x] += d;
}

int query(int x)
{
    int ans = 0;
    for (; x > 0; x -= lowbit(x))
        ans += tree[x];
    return ans;
}

int main()
{
    /*
    freopen("trip.in", "r", stdin);
    freopen("trip.out", "w", stdout);
    */
    scanf("%d%d%d%d", &n, &m, &k, &T);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &arr[i]);
        pre[i] = pos[arr[i]], pos[arr[i]] = i;
    }
    for (int i = 1; i <= m; i++)
        scanf("%d%d", &queries[i].l, &queries[i].r), queries[i].id = i;

    sort(queries + 1, queries + 1 + m);
    for (int i = 1; i <= k; i++)
    {
        int x = T - 1;
        while (x && pos[i] != 0)
            x--, pos[i] = pre[pos[i]];
        if (pos[i] != 0)
            update(pos[i], 1), update(pre[pos[i]], -1);
    }
    int x = n;
    for (int i = 1; i <= m; i++)
    {
        while (x > queries[i].r)
        {
            update(pos[arr[x]], -1), update(pre[pos[arr[x]]], 2), update(pre[pre[pos[arr[x]]]], -1);
            pos[arr[x]] = pre[pos[arr[x]]], x--;
        }
        anses[queries[i].id] = query(queries[i].r) - query(queries[i].l - 1);
    }
    for (int i = 1; i <= m; i++)
        printf("%d\n", anses[i]);
    return 0;
}