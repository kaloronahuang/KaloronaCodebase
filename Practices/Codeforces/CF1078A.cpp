// CF1078A.cpp
#include <bits/stdc++.h>

using namespace std;

double a, b, c, x[3], y[3];

double calcByX(double x) { return (-1.0 * a * x - c) / b; }

double calcByY(double y) { return (-1.0 * b * y - c) / a; }

int main()
{
    scanf("%lf%lf%lf%lf%lf%lf%lf", &a, &b, &c, &x[1], &y[1], &x[2], &y[2]);
    double ans = fabs(x[1] - x[2]) + fabs(y[1] - y[2]);
    if (a != 0 && b != 0)
        for (int i = 0; i <= 1; i++)
            for (int j = 0; j <= 1; j++)
            {
                double pos1X, pos1Y, pos2X, pos2Y;
                double pans = 0;
                if (i == 0)
                    pos1X = calcByY(y[1]), pos1Y = y[1], pans += fabs(pos1X - x[1]);
                else
                    pos1X = x[1], pos1Y = calcByX(x[1]), pans += fabs(pos1Y - y[1]);

                if (j == 0)
                    pos2X = calcByY(y[2]), pos2Y = y[2], pans += fabs(pos2X - x[2]);
                else
                    pos2X = x[2], pos2Y = calcByX(x[2]), pans += fabs(pos2Y - y[2]);

                pans += sqrt((pos1X - pos2X) * (pos1X - pos2X) + (pos1Y - pos2Y) * (pos1Y - pos2Y));
                ans = min(ans, pans);
            }
    printf("%.10lf\n", ans);
    return 0;
}