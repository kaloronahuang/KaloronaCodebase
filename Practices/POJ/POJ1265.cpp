// POJ1265.cpp
#include <iostream>
#include <cstdio>
#include <cmath>

const int MAX_N = 330;

int T, n, x[MAX_N], y[MAX_N];

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

int main()
{
    int caseId = 0;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n), caseId++;
        int ptline = 0, area = 0;
        for (int i = 1; i <= n; i++)
        {
            scanf("%d%d", &x[i], &y[i]);
            int dx = x[i], dy = y[i];
            x[i] += x[i - 1], y[i] += y[i - 1];
            ptline += gcd(abs(dx), abs(dy));
            area += x[i - 1] * y[i] - y[i - 1] * x[i];
        }
        area = abs(area);
        printf("Scenario #%d:\n", caseId);
        printf("%d %d %.1f\n\n", (area - ptline + 2) >> 1, ptline, area * 0.5);
    }
    return 0;
}