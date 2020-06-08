// P1337.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010;

typedef long double ld;

int n;
ld xi[MAX_N], yi[MAX_N], wi[MAX_N];
ld ansx, ansy, dist;

ld pow2(ld x) { return x * x; }

ld getDist(ld ax, ld ay, ld bx, ld by) { return sqrt(pow2(ax - bx) + pow2(ay - by)); }

ld randf() { return 1.0 * rand() / RAND_MAX; }

ld calc(ld cx, ld cy)
{
    ld ret = 0;
    for (int i = 1; i <= n; i++)
        ret += getDist(cx, cy, xi[i], yi[i]) * wi[i];
    if (ret < dist)
        dist = ret, ansx = cx, ansy = cy;
    return ret;
}

const ld T_Coeff = 0.97;

void simulateAnneal()
{
    ld T = 1e5, cx = ansx, cy = ansy;
    while (T > 1e-3)
    {
        ld nxtx = cx + T * (randf() * 2 - 1);
        ld nxty = cy + T * (randf() * 2 - 1);
        ld delta = calc(nxtx, nxty) - calc(cx, cy);
        if (exp(-delta / T) > randf())
            cx = nxtx, cy = nxty;
        T *= T_Coeff;
    }
    for (int i = 1; i <= 1000; i++)
    {
        ld nxtx = ansx + T * (randf() * 2 - 1);
        ld nxty = ansy + T * (randf() * 2 - 1);
        calc(nxtx, nxty);
    }
}

int main()
{
    scanf("%d", &n), srand(time(NULL));
    for (int i = 1; i <= n; i++)
        scanf("%Lf%Lf%Lf", &xi[i], &yi[i], &wi[i]), ansx += xi[i], ansy = yi[i];
    ansx /= n, ansy /= n, dist = calc(ansx, ansy);
    simulateAnneal(), printf("%.3Lf %.3Lf\n", ansx, ansy);
    return 0;
}