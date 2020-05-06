// geometry.cpp
#include <bits/stdc++.h>

using namespace std;

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
};

typedef vec point;

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

int raycast(point p, point *polygon, int len)
{
    int odd = 0;
    for (int i = 1; i <= len; i++)
    {
        if (sgn(distToLine(p, polygon[i], polygon[i % len + 1])) == 0)
            return -1;
        int k = sgn((polygon[i % len + 1] - polygon[i]) ^ (p - polygon[i]));
        int d1 = sgn(polygon[i].y - p.y), d2 = sgn(polygon[i % len + 1].y - p.y);
        if (k > 0 && d1 <= 0 && d2 > 0)
            odd++;
        if (k < 0 && d2 <= 0 && d1 > 0)
            odd--;
    }
    return odd ? 1 : 0;
}

double area(point *polygon, int len)
{
    double ret = 0;
    for (int i = 2; i < len; i++)
        ret += (polygon[i] - polygon[1]) ^ (polygon[i + 1] - polygon[1]);
    return ret / 2.0;
}
