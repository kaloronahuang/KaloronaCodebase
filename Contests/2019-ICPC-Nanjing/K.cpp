#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
int t, n;
const double eps = 1e-8;
typedef pair<double, double> pdd;
int sign(double x)
{
    if (abs(x) < eps)
        return 0;
    else if (x < 0)
        return -1;
    else
        return 1;
}
pdd operator-(pdd &a, pdd &b)
{
    return {a.x - b.x, a.y - b.y};
}
pdd operator+(pdd &a, pdd &b)
{
    return {a.x + b.x, a.y + b.y};
}
pdd operator/(pdd a, int b)
{
    return {a.x / b, a.y / b};
}
bool operator==(pdd a, pdd b)
{
    return sign(a.x - b.x) == 0 && sign(a.y - b.y) == 0;
}
double cross(pdd a, pdd b)
{
    return a.x * b.y - a.y * b.x;
}
double area(pdd a, pdd b, pdd c)
{
    return abs(cross(b - a, c - a));
}
double dist(pdd a) { return a.x * a.x + a.y * a.y; }
pdd a, b, c, p;
void solve(pdd a, pdd b, pdd c, pdd p)
{
    double t = area(a, b, c), t1 = area(a, p, c);
    if (sign(2 * t1 - t) < 0)
        swap(a, b);
    pdd l = a, r = c;
    while (dist(r - l) > eps)
    {
        pdd mid = (r + l) / 2;
        if (sign(2 * area(a, p, mid) - t) > 0)
            r = mid;
        else
            l = mid;
    }
    printf("%.11lf %.11lf\n", r.x, r.y);
}
int main()
{
    cin >> t;
    while (t--)
    {
        scanf("%lf %lf %lf %lf %lf %lf %lf %lf", &a.x, &a.y, &b.x, &b.y, &c.x, &c.y, &p.x, &p.y);
        if (p == a)
        {
            pdd ans = (c + b) / 2;
            printf("%.11lf %.11lf\n", ans.x, ans.y);
            continue;
        }
        else if (p == b)
        {
            pdd ans = (a + c) / 2;
            printf("%.11lf %.11lf\n", ans.x, ans.y);
            continue;
        }
        else if (p == c)
        {
            pdd ans = (a + b) / 2;
            printf("%.11lf %.11lf\n", ans.x, ans.y);
            continue;
        }
        else if (sign(area(a, b, p)) == 0 && p.x >= min(a.x, b.x) && p.x <= max(a.x, b.x))
        {
            solve(a, b, c, p);
            continue;
        }
        else if (sign(area(a, c, p)) == 0 && p.x >= min(a.x, c.x) && p.x <= max(a.x, c.x))
        {
            solve(a, c, b, p);
            continue;
        }
        else if (sign(area(b, c, p)) == 0 && p.x >= min(c.x, b.x) && p.x <= max(c.x, b.x))
        {
            solve(b, c, a, p);
            continue;
        }
        puts("-1");
    }
}