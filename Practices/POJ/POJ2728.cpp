// POJ2728.cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cmath>

using namespace std;

const int MAX_N = 1010;
const double eps = 1e-7, INF = 1e18;

struct point
{
    int x, y, altitude;
} pts[MAX_N];

int n;
double ans = INF, mp[MAX_N][MAX_N], dist[MAX_N];
bool vis[MAX_N];

inline double pow2(double bas) { return bas * bas; }

double getDist(int src, int dst) { return sqrt(1.0 * pow2(pts[src].x - pts[dst].x) + 1.0 * pow2(pts[src].y - pts[dst].y)); }

bool check(double db)
{
    memset(vis, false, sizeof(vis));
    for (int i = 1; i <= n; i++)
        dist[i] = abs(pts[i].altitude - pts[1].altitude) - db * mp[1][i];

    double ret = 0;
    vis[1] = 1;
    for (int i = 1; i <= n - 1; i++)
    {
        double min_val = INF;
        int pos = -1;

        for (int to = 1; to <= n; to++)
            if (!vis[to] && dist[to] < min_val)
                min_val = dist[to], pos = to;
        if (pos == -1)
            break;
        ret += min_val, vis[pos] = true;
        for (int to = 1; to <= n; to++)
        {
            double tmp = abs(pts[pos].altitude - pts[to].altitude) - db * mp[pos][to];
            if (dist[to] > tmp && !vis[to])
                dist[to] = tmp;
        }
    }
    return ret >= 0;
}

int main()
{
    while (scanf("%d", &n) && n != 0)
    {
        for (int i = 1; i <= n; i++)
            scanf("%d%d%d", &pts[i].x, &pts[i].y, &pts[i].altitude);
        double l = 0, r = 40.0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                mp[i][j] = getDist(i, j);
        // get binary search ready;
        while (fabs(l - r) > eps)
        {
            double mid = (l + r) / 2.0;
            if (check(mid))
                l = mid, ans = mid;
            else
                r = mid;
        }
        printf("%.3f\n", ans);
    }
    return 0;
}