// GuOJ1127.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, md;
double v[MAX_N];

struct vec
{
    double d[10];
    void clear() { memset(d, 0, sizeof(d)); }
    double &operator[](const int &rhs) { return d[rhs]; }
    vec operator+(const vec &rhs)
    {
        vec ret;
        ret.clear();
        for (int i = 0; i < md; i++)
            ret[i] = d[i] + rhs.d[i];
        return ret;
    }
    vec operator-(const vec &rhs)
    {
        vec ret;
        ret.clear();
        for (int i = 0; i < md; i++)
            ret[i] = d[i] - rhs.d[i];
        return ret;
    }
    vec operator*(const double &rhs)
    {
        vec ret;
        ret.clear();
        for (int i = 0; i < md; i++)
            ret[i] = d[i] * rhs;
        return ret;
    }
    vec operator/(const double &rhs)
    {
        vec ret;
        ret.clear();
        for (int i = 0; i < md; i++)
            ret[i] = d[i] / rhs;
        return ret;
    }
    vec operator-(void)
    {
        vec ret;
        ret.clear();
        for (int i = 0; i < md; i++)
            ret[i] = -d[i];
        return ret;
    }
    double len2()
    {
        double ret = 0;
        for (int i = 0; i < md; i++)
            ret += d[i] * d[i];
        return ret;
    }
    vec normalize()
    {
        double t = sqrt(len2());
        return (*this) / t;
    }
    void scan()
    {
        for (int i = 0; i < md; i++)
            scanf("%lf", &d[i]);
    }
    void print()
    {
        for (int i = 0; i < md; i++)
            printf("%lf", d[i]);
    }
} pts[MAX_N];

vec under(vec &rhs) { return -rhs * (1 / (1 - rhs.len2())); }

vec centralize(vec &rhs)
{
    vec ret;
    ret.clear();
    for (int i = 1; i <= n; i++)
    {
        double len2 = (pts[i] - rhs).len2();
        if (len2 != 0)
            ret = ret + (rhs - pts[i]) * (v[i] / len2);
    }
    return ret;
}

int main()
{
    scanf("%d%d", &n, &md);
    for (int i = 1; i <= n; i++)
        pts[i].scan();
    double step = 0.5, rot = 0.8;
    vec ret;
    ret.clear();
    for (int rd = 1; rd <= 50; rd++)
    {
        vec c = under(ret) + centralize(ret);
        vec roted = c.normalize() * step;
        if ((ret + roted).len2() < 1)
            ret = ret + roted;
        step *= rot;
    }
    ret.print();
    return 0;
}