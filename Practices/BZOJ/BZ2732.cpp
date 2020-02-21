// BZ2732.cpp
#include <bits/stdc++.h>

using namespace std;

#define double long double

const int MAX_N = 401000;
const double eps = 1e-11, inf = 1e11;

int n, stot;

struct Vector
{
    double x, y;

    Vector(double a = 0, double b = 0) : x(a), y(b) {}
    Vector operator+(const Vector &rhs) { return Vector(x + rhs.x, y + rhs.y); }
    Vector operator-(const Vector &rhs) { return Vector(x - rhs.x, y - rhs.y); }
    Vector operator*(const double &rhs) { return Vector(x * rhs, y * rhs); }
    double operator^(const Vector &rhs) { return x * rhs.y - y * rhs.x; }
} ins[MAX_N];

struct Segment
{
    Vector p, v;
    double angle;
    int id;

    Segment() {}
    Segment(Vector src, Vector dst, int idx) { p = src, v = dst - src, angle = atan2(v.y, v.x), id = idx; }
    bool operator<(const Segment &rhs) const { return angle < rhs.angle; }
    bool onRight(Vector &rhs) { return (v ^ (rhs - p)) < -eps; }
} segs[MAX_N], q[MAX_N];

Vector intersect(Segment &rhsA, Segment &rhsB) { return rhsA.p + rhsA.v * ((rhsB.v ^ (rhsB.p - rhsA.p)) / (rhsB.v ^ rhsA.v)); }

bool check(int mid)
{
    int head = 0, tail = 0, i = 1;
    while (segs[i].id > mid)
        i++;
    for (q[0] = segs[i++]; i <= stot; i++)
        if (segs[i].id <= mid)
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
    return tail - head > 1;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        double x, y1, y2;
        scanf("%Lf%Lf%Lf", &x, &y1, &y2);
        segs[++stot] = Segment(Vector(0, y1 / x), Vector(1, y1 / x - x), i);
        segs[++stot] = Segment(Vector(1, y2 / x - x), Vector(0, y2 / x), i);
    }
    segs[++stot] = Segment(Vector(-inf, eps), Vector(-eps, eps), 0);
    segs[++stot] = Segment(Vector(-eps, eps), Vector(-eps, inf), 0);
    segs[++stot] = Segment(Vector(-eps, inf), Vector(-inf, inf), 0);
    segs[++stot] = Segment(Vector(-inf, inf), Vector(-inf, eps), 0);
    sort(segs + 1, segs + stot + 1);
    int l = 1, r = n, res;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
            l = mid + 1, res = mid;
        else
            r = mid - 1;
    }
    printf("%d\n", res);
    return 0;
}