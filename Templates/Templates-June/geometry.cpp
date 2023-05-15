// geometry.cpp
#include <bits/stdc++.h>

using namespace std;

struct vec
{
    double x, y;
    vec(double x_ = 0, double y_ = 0) { x = x_, y = y_; }
    vec operator+(const vec &rhs) { return vec(x + rhs.x, y + rhs.y); }
    vec operator-(const vec &rhs) { return vec(x - rhs.x, y - rhs.y); }
    double operator*(const vec &rhs) { return x * rhs.x + y * rhs.y; }
    vec operator*(const double &rhs) { return vec(x * rhs, y * rhs); }
    double operator^(const vec &rhs) { return x * rhs.y - y * rhs.x; }
    vec operator/(const double &rhs) { return vec(x / rhs, y / rhs); }
    double len2() { return x * x + y * y; }
    double len() { return sqrt(len2()); }
};

typedef vec point;

point intersect(point a, point a1, point b, point b1)
{
    vec u = a1 - a, v = b1 - b, w = a - b;
    double t = (v ^ w) / (u ^ v);
    return a + u * t;
}