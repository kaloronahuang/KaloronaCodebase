// B.cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>
using namespace std;
const int maxn = 50200;
int n;
struct point
{
    double x, y, z;
    bool operator<(const point &p) const
    {
        return z < p.z;
    }
} ps[maxn];

double getDist(point a, point b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%lf%lf%lf", &ps[i].x, &ps[i].y, &ps[i].z);
    sort(ps, ps + n);
    double ans = 0;
    for (int i = 1; i < n; i++)
        ans += getDist(ps[i], ps[i - 1]);
    cout << fixed << setprecision(3) << ans;
    return 0;
}
