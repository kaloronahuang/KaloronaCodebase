// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200;

int n, answer[MAX_N], xi[MAX_N], yi[MAX_N], xtot, ytot, tot;

struct tup
{
    int x, y, limit, val;
    bool operator<(const tup &tgt) const { return limit < tgt.limit || (limit == tgt.limit && abs(val) < abs(tgt.val)); }
} pool[MAX_N], tmp[MAX_N];

int tree1[MAX_N], tree2[MAX_N];

inline int lowbit(int x) { return x & -x; }

int query(int *arr, int x)
{
    int ans = 0;
    for (; x; x -= lowbit(x))
        ans += arr[x];
    return ans;
}

void update(int *arr, int x, int upper, int d)
{
    for (; x <= upper; x += lowbit(x))
        arr[x] += d;
}

void process(int cnt)
{
    sort(tmp + 1, tmp + 1 + cnt);
    int pt = 0;
    for (int i = 1; i <= cnt; i++)
        if (tmp[i].val != 0)
        {
            int val = abs(tmp[i].val), opt = val / tmp[i].val;
            answer[val] += opt * (pt - query(tree1, tmp[i].x) - query(tree2, tmp[i].y));
        }
        else
            pt++, update(tree1, tmp[i].x, xtot, 1), update(tree2, tmp[i].y, ytot, 1);
    for (int i = 1; i <= cnt; i++)
        if (tmp[i].val == 0)
            update(tree1, tmp[i].x, xtot, -1), update(tree2, tmp[i].y, ytot, -1);
}

void cdq(int l, int r)
{
    int mid = (l + r) >> 1, ptr1 = 0, ptr2 = 0;
    for (int i = l; i <= mid; i++)
        if (pool[i].val == 0)
            tmp[++ptr1] = pool[i];
    for (int i = mid + 1; i <= r; i++)
        if (pool[i].val != 0)
            tmp[ptr1 + (++ptr2)] = pool[i];
    if (ptr1 > 0 && ptr2 > 0)
        process(ptr1 + ptr2);
    if (ptr1 > 0 && ptr1 <= mid - l)
        cdq(l, mid);
    if (ptr2 > 0 && ptr2 < r - mid)
        cdq(mid + 1, r);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        int x, y, d;
        scanf("%d%d%d", &x, &y, &d);
        if (d == 0)
            xi[++xtot] = x, yi[++ytot] = y, pool[++tot] = {x, y, x + y, 0}, answer[i] = -1;
        else
        {
            xi[++xtot] = x - 1, yi[++ytot] = y - 1;
            pool[++tot] = {x - 1, y - 1, x + y - 1, -i};
            pool[++tot] = {x - 1, y - 1, x + y + d, i};
        }
    }
    sort(xi + 1, xi + 1 + xtot), xtot = unique(xi + 1, xi + 1 + xtot) - xi - 1;
    sort(yi + 1, yi + 1 + ytot), ytot = unique(yi + 1, yi + 1 + ytot) - yi - 1;
    for (int i = 1; i <= tot; i++)
    {
        pool[i].x = lower_bound(xi + 1, xi + 1 + xtot, pool[i].x) - xi;
        pool[i].y = lower_bound(yi + 1, yi + 1 + ytot, pool[i].y) - yi;
    }
    cdq(1, tot);
    for (int i = 1; i <= n; i++)
        if (answer[i] >= 0)
            printf("%d\n", answer[i]);
    return 0;
}