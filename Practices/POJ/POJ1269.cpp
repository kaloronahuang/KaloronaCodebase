// POJ1269.cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

using namespace std;

const double eps = 1e-8;

int n;

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

vec intersect(vec a, vec b, vec c, vec d)
{
    vec v = b - a, w = d - c, u = a - c;
    return a + v * double((w ^ u) / (v ^ w));
}

int main()
{
    scanf("%d", &n), puts("INTERSECTING LINES OUTPUT");
    for (int i = 1; i <= n; i++)
    {
        vec s1, t1, s2, t2;
        scanf("%lf%lf%lf%lf%lf%lf%lf%lf", &s1.x, &s1.y, &t1.x, &t1.y, &s2.x, &s2.y, &t2.x, &t2.y);
        if (((t1 - s1) ^ (t2 - s2)) == 0)
        {
            // same line or none intersections;
            if (((s2 - s1) ^ (t2 - s1)) == 0)
                puts("LINE");
            else
                puts("NONE");
        }
        else
        {
            vec pt = intersect(s1, t1, s2, t2);
            printf("POINT %.2lf %.2lf\n", pt.x, pt.y);
        }
    }
    puts("END OF OUTPUT");
    return 0;
}