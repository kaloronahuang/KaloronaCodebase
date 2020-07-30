// P6299.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef double ld;

ll ans;

struct cl
{
    ll x, y;

    cl operator+(const cl &rhs) { return cl{x + rhs.x, y + rhs.y}; }
    cl operator-(const cl &rhs) { return cl{x - rhs.x, y - rhs.y}; }
    cl operator*(const cl &rhs) { return cl{x * rhs.x - y * rhs.y, x * rhs.y + y * rhs.x}; }
    cl operator/(const cl &rhs)
    {
        ld A = x, B = y, C = rhs.x, D = rhs.y;
        return cl{(ll)round(ld(A * C + B * D) / ld(C * C + D * D)), (ll)round(ld(B * C - A * D) / ld(C * C + D * D))};
    }
    cl operator%(const cl &rhs)
    {
        cl ret = ((*this) / rhs) * rhs;
        return cl{x - ret.x, y - ret.y};
    }
};

void exgcd(cl a, cl b, cl &x, cl &y)
{
    if (b.x == 0 && b.y == 0)
    {
        ans = a.x * a.x + a.y * a.y;
        x.x = 1, x.y = 0;
        return;
    }
    exgcd(b, a % b, x, y);
    cl t = x;
    x = y, y = t - a / b * y;
}

int main()
{
    ll a, b, c, d;
    scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
    cl x, y;
    exgcd(cl{a, b}, cl{c, d}, x, y);
    printf("%lld %lld %lld %lld %lld\n", x.x, -x.y, y.x, y.y, ans);
    return 0;
}