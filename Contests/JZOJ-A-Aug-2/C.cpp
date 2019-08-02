// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 101000;

int n, ans = 0x3f3f3f3f;

struct point
{
    int x, y;
    bool operator<(const point &pt) const { return y < pt.y || (y == pt.y && x < pt.x); }
} pts[MAX_N], tmp[MAX_N];

bool compareByY(const point &pt1, const point &pt2) { return pt1.x < pt2.x || (pt1.x == pt2.x && pt1.y < pt2.y); }
int get(point A, point B, point C) { return max(A.x, max(B.x, C.x)) - min(A.x, min(B.x, C.x)) + max(A.y, max(B.y, C.y)) - min(A.y, min(B.y, C.y)); }

void solve(int l, int r)
{
    if (r - l < 15)
    {
        // brute force;
        for (int i = l; i <= r; i++)
            for (int j = i + 1; j <= r; j++)
                for (int k = j + 1; k <= r; k++)
                    ans = min(ans, get(pts[i], pts[j], pts[k]));
        return;
    }
    int mid = (l + r) >> 1, tot = 0;
    solve(l, mid), solve(mid, r);
    for (int i = mid; i <= r; i++)
        if (ans > abs(pts[i].x - pts[mid].x))
            tmp[++tot] = pts[i];
        else
            break;
    for (int i = mid - 1; i >= l; i--)
        if (ans > abs(pts[i].x - pts[mid].x))
            tmp[++tot] = pts[i];
        else
            break;
    sort(tmp + 1, tmp + 1 + tot);
    for (int rig = 3, lft = 1; rig <= tot; rig++)
    {
        while (abs(tmp[rig].y - tmp[lft].y) >= ans)
            lft++;
        for (int i = lft; i < rig; i++)
            for (int j = i + 1; j < rig; j++)
                ans = min(ans, get(tmp[rig], tmp[i], tmp[j]));
    }
}

int main()
{
    scanf("%d", &n);
    // largest module;
    int xmin, ymin, xmax, ymax, xpymax, xpymin, xmymax, xmymin;
    xmin = ymin = xpymin = xmymin = 1 << 30;
    xmax = ymax = xpymax = xmymax = -(1 << 30);
    for (int i = 1, x, y; i <= n; i++)
    {
        scanf("%d%d", &x, &y), swap(x, y);
        pts[i].x = x, pts[i].y = y;
        xmin = min(xmin, x), xmax = max(xmax, x);
        ymax = max(ymax, y), ymin = min(ymin, y);
        xpymax = max(xpymax, x + y), xpymin = min(xpymin, x + y);
        xmymax = max(xmymax, (x - y)), xmymin = min(xmymin, (x - y));
    }
    printf("%d\n", 2 * max(max(xpymax - xmin - ymin, xmax + ymax - xpymin), max(xmymax - xmin + ymax, xmax - xmymin - ymin)));
    // using the CDQ Division And Conquerence;
    sort(pts + 1, pts + 1 + n, compareByY);
    solve(1, n);
    printf("%d", 2 * ans);
    return 0;
}