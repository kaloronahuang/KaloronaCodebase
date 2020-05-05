// POJ3340.cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

using namespace std;

const int MAX_N = 110;
const double eps = 1e-8;

int T, n;

struct vec
{
    double x, y;
    vec(double _x = 0, double _y = 0) : x(_x), y(_y) {}
    vec operator+(const vec &rhs) { return vec(x + rhs.x, y + rhs.y); }
    vec operator-(const vec &rhs) { return vec(x - rhs.x, y - rhs.y); }
    double operator*(const vec &rhs) const { return x * rhs.x + y * rhs.y; }
    double operator^(const vec &rhs) const { return x * rhs.y - y * rhs.x; }
    vec operator/(const double &rhs) const { return vec(x / rhs, y / rhs); }
    double len2() { return x * x + y * y; }
    double len() { return sqrt(len2()); }
};

struct segment
{
    vec beg, fin;
} segs[MAX_N];

int sgn(double x) { return fabs(x) < eps ? 0 : (x < 0 ? -1 : 1); }

bool intersect(segment a, segment b)
{
    return sgn((a.beg - b.beg) ^ (a.fin - b.beg)) * sgn((a.beg - b.fin) ^ (a.fin - b.fin)) <= 0;
}

bool check(segment curt)
{
    if (sqrt((curt.beg - curt.fin) * (curt.beg - curt.fin)) < eps)
        return false;
    for (int i = 1; i <= n; i++)
        if (!intersect(curt, segs[i]))
            return false;
    return true;
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%lf%lf%lf%lf", &segs[i].beg.x, &segs[i].beg.y, &segs[i].fin.x, &segs[i].fin.y);
        bool verdict = false;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                verdict |= check(segment{segs[i].beg, segs[j].beg}) || check(segment{segs[i].beg, segs[i].fin}) ||
                           check(segment{segs[i].fin, segs[j].beg}) || check(segment{segs[i].fin, segs[j].fin});
        puts(verdict ? "Yes!" : "No!");
    }
    return 0;
}