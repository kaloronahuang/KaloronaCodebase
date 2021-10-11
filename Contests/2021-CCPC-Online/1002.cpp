// 1002.cpp
#include <bits/stdc++.h>

using namespace std;

const double eps = 1e-8;

int a, b, c, x[2], y[3];

double calc(double x) { return 1.0 * a * x * x + 1.0 * b * x + 1.0 * c; }

int cmp(double x, double y)
{
    if (abs(x - y) < eps)
        return 0;
    if (x < y)
        return -1;
    return 1;
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%d", &a, &b, &c);
        double mid = -1.0 * b / (2.0 * a);
        scanf("%d%d%d%d%d", &x[0], &x[1], &y[1], &y[0], &y[2]);
        if (cmp(calc(mid), y[1]) == 1 && cmp(mid, x[1]) == -1 && cmp(calc(x[1]), y[2]) == -1 && cmp(calc(x[0]), y[1]) == 1)
        {
            if (cmp(calc(x[1]), y[1]) == 1)
            {
                double m = x[1];
                double a_ = a, b_ = -1.0 * (4.0 * m * a + 1.0 * b), c_ = 4.0 * m * m * a + 2.0 * b * m + c;
                a = a_, b = b_, c = c_;
                if (cmp(calc(x[0]), y[1]) == -1)
                    puts("Yes");
                else
                    puts("No");
            }
            else
                puts("Yes");
        }
        else
            puts("No");
    }
    return 0;
}