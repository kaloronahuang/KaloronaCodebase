// P1742.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 2000;

int n;

struct vec
{
    double x, y;
    vec(double x_ = 0, double y_ = 0) { x = x_, y = y_; }
    vec operator+(const vec &rhs) { return vec(x + rhs.x, y + rhs.y); }
    vec operator-(const vec &rhs) { return vec(x - rhs.x, y - rhs.y); }
    vec operator*(const double &rhs) { return vec(x * rhs, y * rhs); }
    vec operator/(const double &rhs) { return vec(x / rhs, y / rhs); }
    double operator^(const vec &rhs) { return x * rhs.y - y * rhs.x; }
    double operator*(const vec &rhs) { return x * rhs.x + y * rhs.y; }
    double len2() { return x * x + y * y; }
    double len() { return sqrt(len2()); }
    vec normalize() { return *this / len(); }
    vec rotate90() { return vec(y, -x); }
} pts[MAX_N];

vec intersect(vec p0, vec v0, vec p1, vec v1)
{
    double t = ((p1 - p0) ^ v1) / (v0 ^ v1);
    return p0 + v0 * t;
}

vec getOrigin(vec a, vec b, vec c)
{
    return intersect((a + b) / 2, (b - a).rotate90(), (a + c) / 2, (c - a).rotate90());
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lf%lf", &pts[i].x, &pts[i].y);
    random_shuffle(pts + 1, pts + 1 + n);
    vec origin;
    double r2 = 0;
    for (int i = 1; i <= n; i++)
        if ((pts[i] - origin).len2() > r2)
        {
            origin = pts[i], r2 = 0;
            for (int j = 1; j < i; j++)
                if ((pts[j] - origin).len2() > r2)
                {
                    origin = (pts[i] + pts[j]) / 2, r2 = (pts[j] - origin).len2();
                    for (int k = 1; k < j; k++)
                        if ((pts[k] - origin).len2() > r2)
                            origin = getOrigin(pts[i], pts[j], pts[k]), r2 = (pts[k] - origin).len2();
                }
        }
    printf("%.10lf\n%.10lf %.10lf\n", sqrt(r2), origin.x, origin.y);
    return 0;
}