// space.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1000001, INF = 0x3f3f3f3f;

int n;
struct point
{
    double x, y;
    bool operator<(const point &pt) { return x < pt.x || (x == pt.x && y < pt.y); }
} pts[MAX_N], tmp[MAX_N];

bool compareByY(const point &a, const point &b) { return a.y < b.y || (a.y == b.y && a.x < b.x); }

double pow2(double bas) { return bas * bas; }

double getDist(point a, point b) { return sqrt(pow2(a.x - b.x) + pow2(a.y - b.y)); }

double solve(int l, int r)
{
    if (l == r)
        return INF;
    else if (l + 1 == r)
        return getDist(pts[l], pts[r]);
    int mid = (l + r) >> 1;
    double current_ans = min(solve(l, mid), solve(mid + 1, r));
    int tot = 0;
    for (int i = l; i <= r; i++)
        if (fabs(pts[i].x - pts[mid].x) <= current_ans)
            tmp[++tot] = pts[i];
    sort(tmp + 1, tmp + 1 + tot, compareByY);
    for (int i = 1; i <= tot; i++)
        for (int j = i + 1; j <= tot && fabs(tmp[i].y - tmp[j].y) < current_ans; j++)
            current_ans = min(current_ans, getDist(tmp[i], tmp[j]));
    return current_ans;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lf%lf", &pts[i].x, &pts[i].y);
    sort(pts + 1, pts + 1 + n);
    printf("%.4lf", solve(1, n));
    return 0;
}
