// meteorology.cpp
#include <bits/stdc++.h>

using namespace std;

const double pi = acos(-1.0);

int T;
double x_1, y_1, z_1, x_2, y_2, z_2, r, a, b, c, d;

void fileIO(string str)
{
    freopen((str + ".in").c_str(), "r", stdin);
    freopen((str + ".out").c_str(), "w", stdout);
}

int main()
{
    // fileIO("meteorology");
    scanf("%d", &T);
    while (T--)
    {
        scanf("%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf", &x_1, &y_1, &z_1, &x_2, &y_2, &z_2, &r, &a, &b, &c, &d);
        if (c != 0)
        {
            d /= c;
            z_1 += d, z_2 += d;
        }
        if (z_1 >= z_2 + r)
        {
            double L = z_1 - z_2, cosTheta = r / L, sinTheta = sqrt(1.0 - cosTheta);
            double little_part = cosTheta * r;
            double cDist = L - little_part, cr = sqrt(r * r - little_part * little_part);
            double ansR = cr / cDist * z_1;
            printf("%.10lf\n", 1LL * pi * ansR * ansR);
        }
        else
            puts("0");
    }
    return 0;
}