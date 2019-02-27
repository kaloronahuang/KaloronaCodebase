// CF3B13.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_K = 2020, MAX_N = 220;
double pi[MAX_N], dp[MAX_N][MAX_N][MAX_N << 1];
int opt[MAX_N], n, l, pack, tmpx;
void change(int i, int j, int k, double target)
{
    k = min(k, n);
    dp[i][j][200 + k] += target;
}
int main()
{
    scanf("%d%d%d", &n, &l, &pack);
    for (int i = 1; i <= n; i++)
        scanf("%d", &tmpx), pi[i] = tmpx / 100.0;
    for (int i = 1; i <= n; i++)
        scanf("%d", &opt[i]);
    pack = min(pack, n);
    dp[0][0][pack + 200] = 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= i; j++)
            for (int k = -i; k <= n; k++)
            {
                change(i + 1, j + 1, k + opt[i + 1], dp[i][j][k + 200] * pi[i + 1]);
                change(i + 1, j, k, dp[i][j][k + 200] * (1 - pi[i + 1]));
            }
    double ans = 0;
    for (int i = 0; i <= n; i++)
        for (int j = l; j <= n; j++)
            ans += dp[n][j][i + 200];
    printf("%.6lf", ans);
    return 0;
}