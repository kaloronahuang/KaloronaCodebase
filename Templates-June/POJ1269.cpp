// POJ1269.cpp
#include <cstdio>
#include <cmath>
#include <iostream>

using namespace std;

int n;

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

vec intersect(vec a, vec a1, vec b, vec b1)
{
    vec u = a1 - a, v = b1 - b, w = a - b;
    return a + u * ((v ^ w) / (u ^ v));
}

int main()
{
    puts("INTERSECTING LINES OUTPUT"), scanf("%d", &n);
    for (int cs = 1; cs <= n; cs++)
    {
        vec p[4];
        for (int i = 0; i < 4; i++)
            scanf("%lf%lf", &p[i].x, &p[i].y);
        if (((p[1] - p[0]) ^ (p[3] - p[2])) == 0)
            if (((p[2] - p[0]) ^ (p[3] - p[0])) == 0)
                puts("LINE");
            else
                puts("NONE");
        else
        {
            vec pt = intersect(p[0], p[1], p[2], p[3]);
            printf("POINT %.2lf %.2lf\n", pt.x, pt.y);
        }
    }
    puts("END OF OUTPUT");
    return 0;
}