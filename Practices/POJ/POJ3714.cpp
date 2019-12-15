// POJ3714.cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>

using namespace std;

const int MAX_N = 201000, INF = 0x3f3f3f3f;

int T, n;

int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x * f;
}

struct point
{
    double x, y;
    int isBase;
    bool operator<(const point &rhs) const { return x < rhs.x || (x == rhs.x && y < rhs.y); }
} pts[MAX_N], tmp0[MAX_N], tmp1[MAX_N];

double pow2(long long x) { return 1LL * x * x; }

double compareByY(const point &rhs1, const point &rhs2) { return rhs1.y < rhs2.y || (rhs1.y == rhs2.y && rhs1.x < rhs2.x); }

double getDist(point x, point y) { return sqrt(pow2(x.x - y.x) + pow2(x.y - y.y)); }

double solve(int l, int r)
{
    if (l == r)
        return INF;
    if (l == r - 1)
        return (pts[l].isBase ^ pts[r].isBase) ? getDist(pts[l], pts[r]) : INF;
    int mid = (l + r) >> 1, tot0 = 0, tot1 = 0;
    double curt_ans = min(solve(l, mid), solve(mid + 1, r));
    // first situation;
    // lft 0 rig 1;
    for (int i = l; i <= mid; i++)
        if (fabs(pts[i].x - pts[mid].x) < curt_ans && pts[i].isBase == 0)
            tmp0[++tot0] = pts[i];
    for (int i = mid + 1; i <= r; i++)
        if (fabs(pts[i].x - pts[mid].x) < curt_ans && pts[i].isBase == 1)
            tmp1[++tot1] = pts[i];
    sort(tmp0 + 1, tmp0 + 1 + tot0, compareByY), sort(tmp1 + 1, tmp1 + 1 + tot1, compareByY);

    for (int i = 1; i <= tot0; i++)
        for (int j = 1; j <= tot1 && fabs(tmp0[i].y - tmp1[j].y) < curt_ans; j++)
            curt_ans = min(curt_ans, getDist(tmp0[i], tmp1[j]));

    tot0 = 0, tot1 = 0;
    for (int i = l; i <= mid; i++)
        if (fabs(pts[i].x - pts[mid].x) < curt_ans && pts[i].isBase == 1)
            tmp1[++tot1] = pts[i];
    for (int i = mid + 1; i <= r; i++)
        if (fabs(pts[i].x - pts[mid].x) < curt_ans && pts[i].isBase == 0)
            tmp0[++tot0] = pts[i];
    sort(tmp0 + 1, tmp0 + 1 + tot0, compareByY), sort(tmp1 + 1, tmp1 + 1 + tot1, compareByY);

    for (int i = 1; i <= tot0; i++)
        for (int j = 1; j <= tot1 && fabs(tmp0[i].y - tmp1[j].y) < curt_ans; j++)
            curt_ans = min(curt_ans, getDist(tmp0[i], tmp1[j]));
    return curt_ans;
}

int main()
{
    T = read();
    while (T--)
    {
        n = read();
        for (int i = 1; i <= (n << 1); i++)
            pts[i].x = read(), pts[i].y = read(), pts[i].isBase = (i > n);
        sort(pts + 1, pts + 1 + (n << 1));
        printf("%.3f\n", solve(1, n << 1));
    }
    return 0;
}