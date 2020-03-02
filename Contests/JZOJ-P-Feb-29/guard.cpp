// guard.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 550;
const double eps = 1e-8;

int n, m;
double xi[MAX_N], yi[MAX_N];

void fileIO()
{
    freopen("guard.in", "r", stdin);
    freopen("guard.out", "w", stdout);
}

double pow2(double x) { return x * x; }

double getDistSquare(int x, int y) { return pow2(xi[x] - xi[y]) + pow2(yi[x] - yi[y]); }

double getDist(int x, int y) { return sqrt(getDistSquare(x, y)); }

bool check(int posA, int posB, double ratio)
{
    double midx = (xi[posA] + xi[posB]) / 2.0;
    double midy = (yi[posA] + yi[posB]) / 2.0;
    for (int rd = 0, opt = 1; rd < 2; rd++, opt = 0 - opt)
    {
        double cx, cy;
        if (xi[posB] == xi[posA])
            cx = midx, cy = midy + ratio;
        else
        {
            double dis = sqrt(pow2(ratio) - 1.0 * getDistSquare(posA, posB) / 4.0);
            double segRatio = (xi[posA] - xi[posB]) / (yi[posB] - yi[posA]);
            double deltaX = dis / sqrt(pow2(segRatio) + 1);
            // deltaX = sqrt(((4.0 * pow2(ratio) - 1.0 * getDistSquare(posA, posB)) / 4.0) / (pow2(xi[posA] - xi[posB]) + 1));
            cx = midx + 1.0 * opt * deltaX, cy = midy + 1.0 * opt * deltaX * segRatio;
        }
        int cnt = 0;
        xi[n + 1] = cx, yi[n + 1] = cy;
        for (int i = 1; i <= n; i++)
            cnt += (getDist(n + 1, i) <= fabs(ratio));
        if (cnt >= m)
            return true;
        ratio = -ratio;
    }
    return false;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%lf%lf", &xi[i], &yi[i]);
    double max_len = 0, ans = double(0x7fffffffffffffff);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            max_len = max(max_len, getDist(i, j));
    // bool tmp = check(4, 7, 2.2360679775);
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
        {
            double l = getDist(i, j) / 2.0, r = max_len, res = 0x7fffffffffffffff;
            while (r - l > eps)
            {
                double mid = (l + r) / 2.0;
                if (check(i, j, mid))
                    res = mid, r = mid;
                else
                    l = mid;
            }
            ans = min(ans, res);
        }
    printf("%.10lf\n", ans);
    return 0;
}