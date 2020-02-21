// P4196.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;
const double eps = 1e-8;

int n, m, stot, rtot;

struct Vector
{
    double x, y;

    Vector(double a = 0, double b = 0) { x = a, y = b; }
    Vector operator+(const Vector &rhs) { return Vector(x + rhs.x, y + rhs.y); }
    Vector operator-(const Vector &rhs) { return Vector(x - rhs.x, y - rhs.y); }
    Vector operator*(const double &rhs) { return Vector(x * rhs, y * rhs); }
    double operator^(const Vector &rhs) { return x * rhs.y - rhs.x * y; }
} ins[MAX_N], pts[MAX_N], res[MAX_N];

struct Segment
{
    Vector p, v;
    double angle;

    Segment() {}
    Segment(Vector src, Vector dst) { p = src, v = dst - src, angle = atan2(v.y, v.x); }
    bool operator<(const Segment &rhs) const { return angle < rhs.angle; }
    bool onRight(Vector &rhs) { return (v ^ (rhs - p)) < -eps; }
} segs[MAX_N], q[MAX_N];

Vector intersect(Segment &rhsA, Segment &rhsB) { return rhsA.p + rhsA.v * ((rhsB.v ^ (rhsB.p - rhsA.p)) / (rhsB.v ^ rhsA.v)); }

void getHalfIntersection()
{
    int head = 0, tail = 0;
    q[0] = segs[1];
    for (int i = 2; i <= stot; i++)
    {
        while (head < tail && segs[i].onRight(ins[tail - 1]))
            tail--;
        while (head < tail && segs[i].onRight(ins[head]))
            head++;
        if (segs[i].angle != q[tail].angle)
            q[++tail] = segs[i];
        else if (segs[i].onRight(q[tail].p))
            q[tail] = segs[i];
        if (head < tail)
            ins[tail - 1] = intersect(q[tail - 1], q[tail]);
    }
    while (head < tail && q[head].onRight(ins[tail - 1]))
        tail--;
    ins[tail] = intersect(q[head], q[tail]);
    for (int i = head; i <= tail; i++)
        res[++rtot] = ins[i];
}

double getArea()
{
    double ret = 0;
    res[rtot + 1] = res[1];
    for (int i = 1; i <= rtot; i++)
        ret += (res[i] ^ res[i + 1]);
    return ret / 2.0;
}

int main()
{
    scanf("%d", &n);
    while (n--)
    {
        scanf("%d", &m);
        for (int i = 0; i < m; i++)
            scanf("%lf%lf", &pts[i].x, &pts[i].y);
        pts[m] = pts[0];
        for (int i = 0; i < m; i++)
            segs[++stot] = Segment(pts[i], pts[i + 1]);
    }
    sort(segs + 1, segs + stot + 1);
    getHalfIntersection(), printf("%.3lf\n", getArea());
    return 0;
}