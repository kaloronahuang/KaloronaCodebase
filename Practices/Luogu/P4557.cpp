// P4557.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;
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

double len2(vec c) { return c.x * c.x + c.y * c.y; }

typedef vec point;

int n, m, q, stk[MAX_N], ptot;
point c1[MAX_N], c2[MAX_N], sum[MAX_N], base, s1[MAX_N], s2[MAX_N];

bool cmp(const vec &rhs1, const vec &rhs2) { return (rhs1 ^ rhs2) > 0 || ((rhs1 ^ rhs2) == 0 && len2(rhs1) < len2(rhs2)); }

int convexHull(point *seq, int siz)
{
    sort(seq + 1, seq + 1 + siz, [](const point &rhs1, const point &rhs2) { return rhs1.y < rhs2.y || (rhs1.y == rhs2.y && rhs1.x < rhs2.x); });
    int tail = 0;
    base = seq[1], stk[++tail] = 1;
    for (int i = 1; i <= siz; i++)
        seq[i] = seq[i] - base;
    sort(seq + 2, seq + 1 + siz, cmp);
    for (int i = 2; i <= siz; stk[++tail] = i, i++)
        while (tail > 1 && ((seq[i] - seq[stk[tail - 1]]) ^ (seq[stk[tail]] - seq[stk[tail - 1]])) >= 0)
            tail--;
    for (int i = 1; i <= tail; i++)
        seq[i] = seq[stk[i]] + base;
    seq[tail + 1] = seq[1];
    return tail;
}

int minskySum()
{
    for (int i = 1; i <= n; i++)
        s1[i] = c1[i + 1] - c1[i];
    for (int i = 1; i <= m; i++)
        s2[i] = c2[i + 1] - c2[i];
    sum[++ptot] = c1[1] + c2[1];
    int lptr = 1, rptr = 1;
    while (lptr <= n && rptr <= m)
        if ((s1[lptr] ^ s2[rptr]) >= 0)
            ptot++, sum[ptot] = sum[ptot - 1] + s1[lptr++];
        else
            ptot++, sum[ptot] = sum[ptot - 1] + s2[rptr++];
    while (lptr <= n)
        ptot++, sum[ptot] = sum[ptot - 1] + s1[lptr++];
    while (rptr <= m)
        ptot++, sum[ptot] = sum[ptot - 1] + s2[rptr++];
    return ptot;
}

bool check(vec x)
{
    if ((x ^ sum[1]) > 0 || (sum[ptot] ^ x) > 0)
        return false;
    int pos = lower_bound(sum + 1, sum + 1 + ptot, x, cmp) - sum - 1;
    return ((x - sum[pos]) ^ (sum[pos % ptot + 1] - sum[pos])) <= 0;
}

int main()
{
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; i++)
        scanf("%lf%lf", &c1[i].x, &c1[i].y);
    n = convexHull(c1, n);
    for (int i = 1; i <= m; i++)
        scanf("%lf%lf", &c2[i].x, &c2[i].y), c2[i].x = -c2[i].x, c2[i].y = -c2[i].y;
    m = convexHull(c2, m), minskySum(), ptot = convexHull(sum, ptot);
    base = sum[1];
    for (int i = 1; i <= ptot; i++)
        sum[i] = sum[i] - base;
    while (q--)
    {
        scanf("%lf%lf", &sum[0].x, &sum[0].y);
        putchar('0' + check(sum[0] - base)), putchar('\n');
    }
    return 0;
}