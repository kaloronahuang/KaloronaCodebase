// meteorology.cpp
#include <bits/stdc++.h>

using namespace std;

const double pi = acos(-1.0);

typedef long double ld;

int T;
ld x_1, y_1, z_1, x_2, y_2, z_2, r, a, b, c, d;

void fileIO(string str)
{
    freopen((str + ".in").c_str(), "r", stdin);
    freopen((str + ".out").c_str(), "w", stdout);
}

ld pow2(ld x) { return x * x; }

ld getDist(ld x1, ld y1, ld z1, ld x2, ld y2, ld z2) { return sqrt(pow2(x1 - x2) + pow2(y1 - y2) + pow2(z1 - z2)); }

ld getPDist(ld x, ld y, ld z) { return abs(a * x + b * y + c * z + d) / sqrt(pow2(a) + pow2(b) + pow2(c)); }

int main()
{
    // fileIO("meteorology");
    scanf("%d", &T);
    while (T--)
    {
        scanf("%Lf%Lf%Lf%Lf%Lf%Lf%Lf%Lf%Lf%Lf%Lf", &x_1, &y_1, &z_1, &x_2, &y_2, &z_2, &r, &a, &b, &c, &d);
        ld d1 = getPDist(x_1, y_1, z_1), d2 = getPDist(x_2, y_2, z_2), d3 = getDist(x_1, y_1, z_1, x_2, y_2, z_2);
        ld theta = acos((d1 - d2) / d3), alpha = asin(r / d3), beta = asin(r / (d1 - d2));
        ld r1 = d1 * (tan(theta + alpha) - tan(theta - alpha)) / 2.0, r2 = d1 * tan(beta);
        printf("%.10Lf\n", pi * r1 * r2);
    }
    return 0;
}