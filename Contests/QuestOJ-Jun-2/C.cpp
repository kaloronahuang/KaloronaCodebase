// C.cpp
#pragma GCC optimize(2)
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010;

int n, m, mem[MAX_N];

const double eps = 1e-8;

struct vec
{
    double x, y;
    vec(double _x = 0, double _y = 0) : x(_x), y(_y) {}
    vec operator+(const vec &rhs) { return vec(x + rhs.x, y + rhs.y); }
    vec operator-(const vec &rhs) { return vec(x - rhs.x, y - rhs.y); }
    double operator*(const vec &rhs) const { return x * rhs.x + y * rhs.y; }
    vec operator*(const double &rhs) { return vec(x * rhs, y * rhs); }
    double operator^(const vec &rhs) const { return x * rhs.y - y * rhs.x; }
    vec operator/(const double &rhs) const { return vec(x / rhs, y / rhs); }
    double len2() { return x * x + y * y; }
    double len() { return sqrt(len2()); }
    vec normalize() { return (*this) / len(); }
} pts[MAX_N];

struct mountain
{
    vec pos;
    int r;
} mts[MAX_N];

typedef vec point;

int find(int x) { return mem[x] == x ? x : mem[x] = find(mem[x]); }

int sgn(double x) { return fabs(x) < eps ? 0 : (x < 0 ? -1 : 1); }

point intersect(point a, point b, point c, point d)
{
    vec v = b - a, w = d - c, u = a - c;
    return a + v * double((w ^ u) / (v ^ w));
}

double distToLine(point p, point a, point b)
{
    vec x = p - a, y = b - a;
    return fabs(x ^ y) / x.len();
}

double distToSegment(point p, point a, point b)
{
    if ((a - b).len() < eps)
        return (p - a).len();
    vec v1 = b - a, v2 = p - a, v3 = v3 = p - b;
    if (sgn(v1 * v2) < 0)
        return v2.len();
    else if (sgn(v1 * v3) > 0)
        return v3.len();
    return fabs(v1 ^ v2) / v1.len();
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        mem[i] = i;
    for (int i = 1; i <= n; i++)
        scanf("%lf%lf", &pts[i].x, &pts[i].y);
    for (int i = 1; i <= m; i++)
        scanf("%lf%lf%d", &mts[i].pos.x, &mts[i].pos.y, &mts[i].r);
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if (find(i) != find(j))
            {
                bool verdict = true;
                for (int k = 1; k <= m && verdict; k++)
                    if (distToSegment(mts[k].pos, pts[i], pts[j]) <= mts[k].r)
                        verdict = false;
                if (verdict)
                    mem[find(i)] = find(j);
            }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        if (find(i) == i)
            ans++;
    printf("%d\n", ans - 1);
    return 0;
}