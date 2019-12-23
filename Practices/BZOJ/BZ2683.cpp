// BZ2683.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2001000;

struct query
{
    int opt, x1, upper, lower, val, id;
    bool operator<(const query &rhs) const { return x1 < rhs.x1 || (x1 == rhs.x1 && opt < rhs.opt); }
} queries[MAX_N], tmp[MAX_N];

int nodes[MAX_N], n, ans[MAX_N], qtot, ansTot;
bool mark[MAX_N];

inline int lowbit(int x) { return x & (-x); }

void update(int x, int d)
{
    for (; x <= n; x += lowbit(x))
        nodes[x] += d;
}

int querySum(int x, int ret = 0)
{
    for (; x; x -= lowbit(x))
        ret += nodes[x];
    return ret;
}

void solve(int l, int r)
{
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    solve(l, mid), solve(mid + 1, r);
    for (int i = l; i <= r; i++)
        tmp[i] = queries[i];
    sort(tmp + l, tmp + mid + 1), sort(tmp + mid + 1, tmp + r + 1);
    for (int i = mid + 1, lptr = l; i <= r; i++)
        if (tmp[i].opt == 2)
        {
            while (lptr <= mid && tmp[lptr].x1 <= tmp[i].x1)
            {
                if (tmp[lptr].opt == 1)
                    update(tmp[lptr].upper, tmp[lptr].val);
                lptr++;
            }
            ans[tmp[i].id] += tmp[i].val * (querySum(tmp[i].lower) - querySum(tmp[i].upper - 1));
        }
    for (int i = mid + 1, lptr = l; i <= r; i++)
        if (tmp[i].opt == 2)
            while (lptr <= mid && tmp[lptr].x1 <= tmp[i].x1)
            {
                if (tmp[lptr].opt == 1)
                    update(tmp[lptr].upper, -tmp[lptr].val);
                lptr++;
            }
}

int main()
{
    scanf("%d", &n);
    while (true)
    {
        int opt, x, y, xx, yy, A;
        scanf("%d", &opt);
        if (opt == 3)
            break;
        if (opt == 1)
        {
            scanf("%d%d%d", &x, &y, &A);
            queries[++qtot] = query{opt, x, y, 0, A, 0};
        }
        else if (opt == 2)
        {
            scanf("%d%d%d%d", &x, &y, &xx, &yy);
            queries[++qtot] = query{opt, x - 1, y, yy, -1, ++ansTot};
            queries[++qtot] = query{opt, xx, y, yy, 1, ansTot};
        }
    }
    solve(1, qtot);
    for (int i = 1; i <= ansTot; i++)
        printf("%d\n", ans[i]);
    return 0;
}