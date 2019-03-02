// A.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 55, MAX_M = 1200;
int n, m, tmpx, tmpy, tmpz, f[MAX_N][MAX_N][MAX_M], dist[MAX_N][MAX_N], q;
int main()
{
    scanf("%d%d", &n, &m);
    memset(f, 0x3f, sizeof(f)), memset(dist, 0x3f, sizeof(dist));
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &tmpx, &tmpy, &tmpz), dist[tmpx][tmpy] = min(dist[tmpx][tmpy], tmpz);
    for (int i = 1; i <= n; i++)
        f[i][i][0] = 0;
    for (int s = 1; s <= n; s++)
        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    if (f[i][j][s] > f[i][k][s - 1] + dist[k][j])
                        f[i][j][s] = f[i][k][s - 1] + dist[k][j];
    scanf("%d", &q);
    while (q--)
    {
        double ans = (double)0x3f3f3f3f;
        int i, j;
        bool flag = true;
        scanf("%d%d", &i, &j);
        for (int s = 1; s <= n; s++)
            if (1.0 * f[i][j][s] / (1.0 * s) < ans && f[i][j][s] != (double)0x3f3f3f3f)
                ans = min(ans, 1.0 * f[i][j][s] / (1.0 * s)), flag = false;
        if (flag)
            puts("OMG!");
        else
            printf("%.3lf\n", ans);
    }
    return 0;
}