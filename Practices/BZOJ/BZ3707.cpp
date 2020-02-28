// BZ3707.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010;

struct point
{
    double x, y;
    bool operator<(const point &rhs) const { return x < rhs.x || (x == rhs.x && y < rhs.y); }
    point operator-(const point &rhs) { return point{x - rhs.x, y - rhs.y}; }
    double operator^(const point &rhs) { return x * rhs.y - y * rhs.x; }
} pts[MAX_N];

struct segment
{
    int uid, vid;
    double k;
    bool operator<(const segment &rhs) const { return k < rhs.k; }
} segs[MAX_N * MAX_N];

double ans = 0x7fffffffffffffff;
int n, pos[MAX_N], id[MAX_N], stot;

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lf%lf", &pts[i].x, &pts[i].y);
    sort(pts + 1, pts + 1 + n);
    for (int i = 1; i <= n; i++)
        pos[i] = id[i] = i;
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            segs[++stot] = segment{i, j, atan2(pts[j].y - pts[i].y, pts[j].x - pts[i].x)};
    sort(segs + 1, segs + 1 + stot);
    for (int i = 1; i <= stot; i++)
    {
        int a = segs[i].uid, b = segs[i].vid;
        if (id[a] > id[b])
            swap(a, b);
        if (id[a] > 1)
            ans = min(ans, fabs((pts[b] - pts[a]) ^ (pts[b] - pts[pos[id[a] - 1]])));
        if (id[b] < n)
            ans = min(ans, fabs((pts[b] - pts[a]) ^ (pts[b] - pts[pos[id[b] + 1]])));
        swap(id[a], id[b]), swap(pos[id[a]], pos[id[b]]);
    }
    printf("%.2lf\n", ans / 2.0);
    return 0;
}