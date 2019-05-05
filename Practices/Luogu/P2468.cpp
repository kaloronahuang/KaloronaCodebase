// P2468.cpp
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 220, RANGE = 1010;

// the first solution;
#pragma region First Solution

int heights[MAX_N][MAX_N], value[MAX_N][MAX_N][RANGE], cnt[MAX_N][MAX_N][RANGE], n, m, T;

int getVal(int x1, int y1, int x2, int y2, int k)
{
    return value[x2][y2][k] - value[x1 - 1][y2][k] - value[x2][y1 - 1][k] + value[x1 - 1][y1 - 1][k];
}

int getCnt(int x1, int y1, int x2, int y2, int k)
{
    return cnt[x2][y2][k] - cnt[x1 - 1][y2][k] - cnt[x2][y1 - 1][k] + cnt[x1 - 1][y1 - 1][k];
}

void solve1()
{
    int mxval = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &heights[i][j]), mxval = max(mxval, heights[i][j]);
    for (int v = 0; v <= mxval; v++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
            {
                value[i][j][v] = value[i - 1][j][v] + value[i][j - 1][v] - value[i - 1][j - 1][v] + ((heights[i][j] >= v) ? heights[i][j] : 0);
                cnt[i][j][v] = cnt[i - 1][j][v] + cnt[i][j - 1][v] - cnt[i - 1][j - 1][v] + ((heights[i][j] >= v) ? 1 : 0);
            }
    while (T--)
    {
        int x1, y1, x2, y2, hi;
        scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &hi);
        if (getVal(x1, y1, x2, y2, 0) < hi)
        {
            printf("Poor QLW\n");
            continue;
        }
        int l = 0, r = mxval + 1, ans = -1;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            if (getVal(x1, y1, x2, y2, mid) >= hi)
                ans = mid, l = mid + 1;
            else
                r = mid - 1;
        }
        if (ans == -1)
        {
            printf("Poor QLW\n");
            continue;
        }
        else
            printf("%d\n", getCnt(x1, y1, x2, y2, ans) - (getVal(x1, y1, x2, y2, ans) - hi) / ans);
    }
}

#pragma endregion

#pragma region Second Solution

const int MAX_S = 501000;
struct node
{
    int sum, lson, rson, siz;
} nodes[MAX_S << 4];
int roots[MAX_S], hgt[MAX_S], tot;

int update(int qx, int l, int r, int pre, int val)
{
    int p = ++tot;
    nodes[p].sum = nodes[pre].sum + val;
    nodes[p].lson = nodes[pre].lson, nodes[p].rson = nodes[pre].rson;
    nodes[p].siz = nodes[pre].siz + 1;
    if (l == r)
        return p;
    int mid = (l + r) >> 1;
    if (qx <= mid)
        nodes[p].lson = update(qx, l, mid, nodes[pre].lson, val);
    else
        nodes[p].rson = update(qx, mid + 1, r, nodes[p].rson, val);
    return p;
}

int query(int p1, int p2, int l, int r, int k)
{
    int ans = 0;
    while (l < r)
    {
        int mid = (l + r) >> 1, jud = nodes[nodes[p2].rson].sum - nodes[nodes[p1].rson].sum;
        if (jud < k)
        {
            ans += nodes[nodes[p2].rson].siz - nodes[nodes[p1].rson].siz, k -= jud;
            r = mid, p1 = nodes[p1].lson, p2 = nodes[p2].lson;
        }
        else
            l = mid + 1, p1 = nodes[p1].rson, p2 = nodes[p2].rson;
    }
    ans += (k + l - 1) / l;
    return ans;
}

void solve2()
{
    for (int i = 1; i <= m; i++)
        scanf("%d", &hgt[i]), roots[i] = update(hgt[i], 1, 1000, roots[i - 1], hgt[i]);
    while (T--)
    {
        int x1, y1, x2, y2, hi;
        scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &hi);
        if (nodes[roots[y2]].sum - nodes[roots[y1 - 1]].sum < hi)
        {
            printf("Poor QLW\n");
            continue;
        }
        printf("%d\n", query(roots[y1 - 1], roots[y2], 1, 1000, hi));
    }
}

#pragma endregion

signed main()
{
    scanf("%d%d%d", &n, &m, &T);
    if (n != 1)
        solve1();
    else
        solve2();
    return 0;
}