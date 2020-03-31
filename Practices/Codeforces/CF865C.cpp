// CF865C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 55, MAX_M = 5050;
const double eps = 1e-9;

int n, m, ai[MAX_N], bi[MAX_N], pi[MAX_N];
double dp[MAX_N][MAX_M];

bool check(double mid)
{
    for (int i = n; i >= 1; i--)
    {
        for (int j = m + 1; j < MAX_M; j++)
            dp[i + 1][j] = mid;
        for (int j = 0; j <= m; j++)
            dp[i][j] = min((dp[i + 1][j + ai[i]] + ai[i]) * double(1.0 * pi[i] / 100) + (dp[i + 1][j + bi[i]] + bi[i]) * double((100.0 - pi[i]) / 100), mid);
    }
    return dp[1][0] < mid;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d%d%d", &ai[i], &bi[i], &pi[i]);
    double l = 0, r = 1e9, res = 0;
    for (int rd = 1; rd <= 200; rd++)
    {
        double mid = (l + r) / 2;
        if (check(mid))
            r = mid, res = mid;
        else
            l = mid;
    }
    printf("%.10lf\n", res);
    return 0;
}