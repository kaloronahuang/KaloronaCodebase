// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 330;

int n, m, q, typ, mat[MAX_N][MAX_N], pre[MAX_N][MAX_N][MAX_N], ptot, lft[MAX_N], rig[MAX_N], lans;

struct node
{
    int x, y, val;
    bool operator<(const node &rhs) const { return val < rhs.val; }
} nodes[MAX_N * MAX_N];

int main()
{
    scanf("%d%d%d%d", &n, &m, &q, &typ);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &mat[i][j]), nodes[(i - 1) * m + j] = node{i, j, mat[i][j]};
    sort(nodes + 1, nodes + 1 + n * m);
    int block = sqrt(n * m);
    for (int i = 1; i <= n * m; i += block)
    {
        int p = ++ptot;
        lft[p] = nodes[i].val, rig[p] = nodes[min(n * m, i + block)].val;
        for (int j = i; j <= min(n * m, i + block - 1); j++)
            pre[ptot][nodes[j].x][nodes[j].y]++;
    }
    for (int d = 1; d <= ptot; d++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                pre[d][i][j] += pre[d][i][j - 1] + pre[d][i - 1][j] - pre[d][i - 1][j - 1];
    while (q--)
    {
        int xl, yl, xr, yr, s, t;
        scanf("%d%d%d%d%d%d", &xl, &yl, &xr, &yr, &s, &t);
        if (typ)
            xl ^= lans, yl ^= lans, xr ^= lans, yr ^= lans, s ^= lans, t ^= lans;
        xl = (xl - 1 + n) % n + 1, yl = (yl - 1 + m) % m + 1;
        xr = (xr - 1 + n) % n + 1, yr = (yr - 1 + m) % m + 1;
        if (xl > xr)
            swap(xl, xr);
        if (yl > yr)
            swap(yl, yr);
        if (s > t)
            swap(s, t);
        lans = 0;
        for (int i = 1, id = 1; id <= ptot; i += block, id++)
        {
            if (s <= lft[id] && rig[id] <= t)
                lans += pre[id][xr][yr] - pre[id][xl - 1][yr] - pre[id][xr][yl - 1] + pre[id][xl - 1][yl - 1];
            else if (!((rig[id] <= s) || (t <= lft[id])))
            {
                for (int j = i; j <= i + block - 1; j++)
                    if (s <= nodes[j].val && nodes[j].val <= t && xl <= nodes[j].x && yl <= nodes[j].y && nodes[j].x <= xr && nodes[j].y <= yr)
                        lans++;
            }
        }
        printf("%d\n", lans);
    }
    return 0;
}