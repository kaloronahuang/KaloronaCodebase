// P2831.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#define pr pair<double, double>
using namespace std;
const double eps = 1e-8;
int T, n, dotset[19][19], dp[(1 << 19)], lbit[(1 << 19)], m;
pr prs[20];
void solve(double &x, double &y, double a1, double b1, double c1, double a2, double b2, double c2)
{
    y = (a1 * c2 - a2 * c1) / (a1 * b2 - a2 * b1);
    x = (c1 - b1 * y) / a1;
}
int main()
{
    for (int i = 0; i < (1 << 18); i++)
    {
        int bit = 0;
        for (; bit < 18 && (i & (1 << bit)) ; bit++)
            ;
        lbit[i] = bit;
    }
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &m);
        memset(dp, 0x3f, sizeof(dp)), memset(dotset, 0, sizeof(dotset));
        for (int i = 0; i < n; i++)
            scanf("%lf%lf", &prs[i].first, &prs[i].second);
        // process the curves;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                if (fabs(prs[i].first - prs[j].first) < eps)
                    continue;
                double a, b;
                solve(a, b, prs[i].first * prs[i].first, prs[i].first, prs[i].second,
                      prs[j].first * prs[j].first, prs[j].first, prs[j].second);
                if (a > -eps)
                    continue;
                for (int k = 0; k < n; k++)
                    if (fabs(a * prs[k].first * prs[k].first + b * prs[k].first - prs[k].second) < eps)
                        dotset[i][j] |= (1 << k);
            }
        dp[0] = 0;
        for (int stat = 0; stat < (1 << n); stat++)
        {
            int esspt = lbit[stat];
            dp[stat | (1 << esspt)] = min(dp[stat | (1 << esspt)], dp[stat] + 1);
            for (int k = 0; k < n; k++)
                dp[stat | dotset[esspt][k]] = min(dp[stat | dotset[esspt][k]], dp[stat] + 1);
        }
        printf("%d\n", dp[(1 << n) - 1]);
    }
    return 0;
}   